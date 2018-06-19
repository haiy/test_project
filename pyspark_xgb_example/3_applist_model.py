import pandas as pd
import sys
import numpy as np
from pyspark.ml.classification import LogisticRegression, LogisticRegressionModel
from pyspark.ml.evaluation import BinaryClassificationEvaluator
from pyspark.ml.linalg import Vectors
from pyspark.ml.pipeline import Pipeline, PipelineModel
from pyspark.ml.tuning import ParamGridBuilder, CrossValidator, TrainValidationSplit
from pyspark.ml.evaluation import MulticlassClassificationEvaluator

from pyspark.sql.session import SparkSession
from pyspark.sql.types import Row

"""
task desc: 根据用户的applist来预测用户是否会贷款,label为1代表贷款,label为0表示未贷款
data input: data/input/100_line_test.csv
pyspark ml guide: https://spark.apache.org/docs/latest/ml-guide.html
pyspark api doc: https://spark.apache.org/docs/latest/api/python/pyspark.ml.html
"""


def single_line_transform(single_line):
    """
    单行维度的数据处理

    :param single_line: 输入是一行原始的数据spark row格式的数据
    :return: spark row格式的数据

    """

    global APP_DICT
    applist_feature = [0] * len(APP_DICT)
    my_apps = single_line.applist.split(";")
    for app in my_apps:
        applist_feature[APP_DICT[app]] = 1
    return (single_line.uid, Row(label=single_line.label, feats=applist_feature))


def single_instance_hanler(user_features_1, user_features_2):
    """
    合并计算单个用户的每个app的出现次数
    :param user_features_1: 用户单条记录中app列表 [0,1,1,0]
    :param user_features_2: 用户单条记录中app列表 [1,1,0,0]
    :return: app出现在记录中的次数加和, [0,2,1,0]
    """

    a = np.array([user_features_1.feats, user_features_2.feats])
    applist_feature = np.sum(a, axis=0).tolist()
    return Row(label=user_features_1.label, feats=applist_feature)


def simple_train_model(input_df):
    lr_model = LogisticRegression(regParam=0.01)
    pipeline = Pipeline(stages=[lr_model])
    return pipeline.fit(input_df)


def train_with_tune(input_df):
    # https://spark.apache.org/docs/latest/ml-tuning.html
    # 构建模型训练流程
    lr = LogisticRegression()
    pipeline = Pipeline(stages=[lr])

    # 构建超参空间
    paramGrid = ParamGridBuilder() \
        .addGrid(lr.regParam, [0.1, 0.01]) \
        .build()

    # 只做一次切分
    # tvs = TrainValidationSplit(estimator=pipeline,
    #                            estimatorParamMaps=paramGrid,
    #                            evaluator=BinaryClassificationEvaluator(),
    #                            # 80% of the data will be used for training, 20% for validation.
    #                            trainRatio=0.8)

    # k-fold cross validation
    cross_val = CrossValidator(estimator=pipeline,
                               estimatorParamMaps=paramGrid,
                               evaluator=BinaryClassificationEvaluator(),
                               numFolds=3)

    # train and find the best
    cvModel = cross_val.fit(input_df)
    return cvModel.bestModel


if __name__ == "__main__":
    input_data = sys.argv[1] if len(sys.argv) > 1 else "data/input/100_line_test.csv"
    model_save_path = sys.argv[2] if len(sys.argv) > 2 else "data/output/appmodel"
    total_applist = sys.argv[3] if len(sys.argv) > 3 else "data/input/total_app_list.csv"

    total_app_dict = pd.read_csv(total_applist)

    # 读进所有用户的APP词典列表构建，app的索引
    # 形如 {"密钥链":1,"联系人存储":2,"相机":3,"浏览器":4}
    global APP_DICT
    APP_DICT = {v: k for k, v in total_app_dict.app.to_dict().items()}

    spark = SparkSession.builder.appName("SimpleApp").getOrCreate()

    # 读入csv格式数据
    input_df = spark.read.option("header", True).csv(input_data)

    # 对训练数据进行单行转换(transform)
    tmp_df = input_df.rdd \
        .map(single_line_transform)

    # 合并单个用户的训练数据,构建训练特征,需要注意的是需要明确指定label，features.
    # features是所有特征, 用Vectors.dense来构建特征的数据结构
    train_df = tmp_df.reduceByKey(single_instance_hanler) \
        .map(lambda r: Row(label=int(r[1].label), features=Vectors.dense(r[1].feats))) \
        .toDF()

    # 简单版本的训练模型, 保存模型
    # 关于模型超参调整和cv请参照,https://spark.apache.org/docs/latest/ml-tuning.html
    pipe_lr_model = simple_train_model(train_df)
    print(pipe_lr_model)
    pipe_lr_model.write().overwrite().save(model_save_path)

    # 重新加载模型
    loaded_model = PipelineModel.load(model_save_path)
    result = loaded_model.transform(train_df)

    print(result.take(3))

    # 带有超参调整的cv模型
    # train,test数据切分
    bst_model_path = model_save_path + "_bst_model"
    train_df, test_df = train_df.randomSplit([0.8, 0.2], seed=12345)
    bst_model = train_with_tune(train_df)
    bst_model.write().overwrite().save(bst_model_path)

    # 用训练得到最佳模型来对测试数据进行预测
    # 预测结果的数据结构是类似下面的结构:
    #      features = Vectors.dense(...)
    #      label=0,
    #      rawPrediction=DenseVector([0.048, -0.048]),
    #      probability=DenseVector([0.512, 0.488]),
    #      prediction=0.0
    loaded_bst_model = PipelineModel.load(bst_model_path)
    result = loaded_model.transform(train_df)
    predict_result = loaded_bst_model.transform(test_df)
    print("predicted sample :", predict_result.take(3))

    # 对训练出来的二分类模型进行评估
    bin_eval = BinaryClassificationEvaluator()
    predict_metric = bin_eval.evaluate(predict_result, {bin_eval.metricName: "areaUnderROC"})
    print("trained model test auc metric", predict_metric)

    # 查看具体分类混淆矩阵信息，默认会计算f1
    mm = MulticlassClassificationEvaluator()
    f1 = mm.evaluate(predict_result)
    accuracy = mm.evaluate(predict_result, {mm.metricName: "accuracy"})
    precision = mm.evaluate(predict_result, {mm.metricName: "weightedPrecision"})
    recall = mm.evaluate(predict_result, {mm.metricName: "weightedRecall"})
    print("predict trained model precision: %f, recall: %f, acc: %s, f1: %f " \
          % (precision, recall, accuracy, f1))
