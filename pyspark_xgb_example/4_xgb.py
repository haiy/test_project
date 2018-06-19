import xgboost
import pandas as pd
import sys
import numpy as np
from pyspark.ml.evaluation import BinaryClassificationEvaluator
from pyspark.ml.linalg import Vectors
from pyspark.ml.pipeline import Pipeline, PipelineModel
from pyspark.ml.tuning import ParamGridBuilder, CrossValidator, TrainValidationSplit

from pyspark.sql.session import SparkSession
from pyspark.sql.types import Row

from ml.dmlc.xgboost4j.scala.spark import XGBoostClassifier



"""
task desc: predict if it's a target user based on applist
data input: data/input/100_line_test.csv
pyspark ml guide: https://spark.apache.org/docs/latest/ml-guide.html
pyspark api doc: https://spark.apache.org/docs/latest/api/python/pyspark.ml.html
"""


def single_line_transform(single_line):
    """
    transoform the raw single line to onehot based on the app dict

    :param single_line: a raw line info in spark `Row` format
    :return: k,v pair for group, and the `v` is a `Row`

    """

    global APP_DICT
    applist_feature = [0] * len(APP_DICT)
    my_apps = single_line.applist.split(";")
    for app in my_apps:
        applist_feature[APP_DICT[app]] = 1
    return (single_line.uid, Row(label=single_line.label, feats=applist_feature))


def single_instance_hanler(user_features_1, user_features_2):
    """
    reduce a single user's apps
    :param user_features_1: user's single applist recored[0,1,1,0]
    :param user_features_2: user's single applist recored [1,1,0,0]
    :return: sum the count of each app, [0,2,1,0]
    """

    a = np.array([user_features_1.feats, user_features_2.feats])
    applist_feature = np.sum(a, axis=0).tolist()
    return Row(label=user_features_1.label, feats=applist_feature)


def simple_train_model(input_df):
    xgboost_params = {
        "eta": 0.023,
        "max_depth": 10,
        "min_child_weight": 0.3,
        "subsample": 0.7,
        "colsample_bytree": 0.82,
        "colsample_bylevel": 0.9,
        "eval_metric": "auc",
        "seed": 49,
        "silent": 1,
        "objective": "binary:logistic",
        "round": 10,
        "nWorkers": 2
    }
    xgb_model = XGBoostClassifier(xgboost_params)
    pipeline = Pipeline(stages=[xgb_model])
    return pipeline.fit(input_df)


def train_with_tune(input_df):
    # https://spark.apache.org/docs/latest/ml-tuning.html
    # build a model with GridSearch
    xgboost_params = {
        "eta": 0.023,
        "max_depth": 10,
        "min_child_weight": 0.3,
        "subsample": 0.7,
        "colsample_bytree": 0.82,
        "colsample_bylevel": 0.9,
        "eval_metric": "auc",
        "seed": 49,
        "silent": 1,
        "objective": "binary:logistic",
        "round": 10,
        "nWorkers": 2
    }
    xgb_model = XGBoostClassifier(xgboost_params)
    pipeline = Pipeline(stages=[xgb_model])

    # build the hyperparameter space
    paramGrid = ParamGridBuilder() \
        .addGrid(xgb_model.max_depth, [3, 7]) \
        .addGrid(xgb_model.min_child_weight, [0.1, 0.2, 0.3]) \
        .build()


    # k-fold cross validation
    cross_val = CrossValidator(estimator=pipeline,
                               estimatorParamMaps=paramGrid,
                               evaluator=BinaryClassificationEvaluator(rawPredictionCol="probabilities"),
                               numFolds=3)

    # train and find the best
    cvModel = cross_val.fit(input_df)
    return cvModel.bestModel


if __name__ == "__main__":
    input_data = sys.argv[1] if len(sys.argv) > 1 else "data/input/100_line_test.csv"
    model_save_path = sys.argv[2] if len(sys.argv) > 2 else "data/output/xgb_model"
    total_applist = sys.argv[3] if len(sys.argv) > 3 else "data/input/total_app_list.csv"

    total_app_dict = pd.read_csv(total_applist)

    # load the total app into a dict，key is the app name.
    # like: {"密钥链":1,"联系人存储":2,"相机":3,"浏览器":4}
    global APP_DICT
    APP_DICT = {v: k for k, v in total_app_dict.app.to_dict().items()}

    spark = SparkSession.builder.appName("SimpleApp").getOrCreate()

    # load csv data with header
    input_df = spark.read.option("header", True).csv(input_data)

    # transform the train data
    tmp_df = input_df.rdd \
        .map(single_line_transform)

    # build the single user features,we should explict name the label，features.
    # features is the column with all features in a `Vectors.dense`
    train_df = tmp_df.reduceByKey(single_instance_hanler) \
        .map(lambda r: Row(label=int(r[1].label), features=Vectors.dense(r[1].feats))) \
        .toDF()

    # simple version, save and load
    # https://spark.apache.org/docs/latest/ml-tuning.html
    pipe_lr_model = simple_train_model(train_df)
    print(pipe_lr_model)
    pipe_lr_model.write().overwrite().save(model_save_path)

    xgb_model = pipe_lr_model.stages[0]
    xgb_model.saveBooster(model_save_path + "_booster")


    result = pipe_lr_model.transform(train_df)
    print(result.take(3))

    # reload the model with pipeline
    loaded_model = PipelineModel.load(model_save_path)
    result = loaded_model.transform(train_df)

    print(result.take(3))
