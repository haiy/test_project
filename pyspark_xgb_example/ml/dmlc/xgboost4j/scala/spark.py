from pyspark.ml.classification import JavaClassificationModel, JavaMLWritable, JavaMLReadable, TypeConverters, Param, \
    Params, HasFeaturesCol, HasLabelCol, HasPredictionCol, HasRawPredictionCol, SparkContext
from pyspark.ml.wrapper import JavaModel, JavaWrapper, JavaEstimator


class XGBParams(Params):
    eta = Param(Params._dummy(), "eta",
                "step size shrinkage used in update to prevents overfitting. After each boosting step, "
                "we can directly get the weights of new features. and eta actually shrinks the feature "
                "weights to make the boosting process more conservative",
                typeConverter=TypeConverters.toFloat)
    max_depth = Param(Params._dummy(), "max_depth",
                      "maximum depth of a tree, increase this value will make the model more "
                      "complex / likely to be overfitting. 0 indicates no limit, limit is required "
                      "for depth-wise grow policy.range: [0,∞]",
                      typeConverter=TypeConverters.toInt)
    min_child_weight = Param(Params._dummy(), "min_child_weight",
                             "minimum sum of instance weight (hessian) needed in a child. If the tree "
                             "partition step results in a leaf node with the sum of instance weight less "
                             "than min_child_weight, then the building process will give up further partitioning."
                             " In linear regression mode, this simply corresponds to minimum number of instances "
                             "needed to be in each node. The larger, the more conservative the algorithm "
                             "will berange: [0,∞]",
                             typeConverter=TypeConverters.toFloat)
    max_delta_step = Param(Params._dummy(), "max_delta_step",
                           "Maximum delta step we allow each tree’s weight estimation to be. If the value is "
                           "set to 0, it means there is no constraint. If it is set to a positive value, "
                           "it can help making the update step more conservative. Usually this parameter is "
                           "not needed, but it might help in logistic regression when class is extremely imbalanced. "
                           "Set it to value of 1-10 might help control the update.",
                           typeConverter=TypeConverters.toInt)
    subsample = Param(Params._dummy(), "subsample",
                      "subsample ratio of the training instance. Setting it to 0.5 means that XGBoost randomly "
                      "collected half of the data instances to grow trees and this will prevent overfitting.",
                      typeConverter=TypeConverters.toFloat)
    colsample_bytree = Param(Params._dummy(), "colsample_bytree",
                             "subsample ratio of columns when constructing each tree",
                             typeConverter=TypeConverters.toFloat)
    colsample_bylevel = Param(Params._dummy(), "colsample_bylevel",
                              "subsample ratio of columns for each split, in each level.",
                              typeConverter=TypeConverters.toFloat)
    max_leaves = Param(Params._dummy(), "max_leaves",
                       "Maximum number of nodes to be added. Only relevant for the ‘lossguide’ grow policy.",
                       typeConverter=TypeConverters.toInt)

    def __init__(self):
        super(XGBParams, self).__init__()


class XGBoostClassifier(JavaEstimator, JavaMLWritable, JavaMLReadable, XGBParams,
                        HasFeaturesCol, HasLabelCol, HasPredictionCol, HasRawPredictionCol):
    def __init__(self, paramMap={}):
        super(XGBoostClassifier, self).__init__()
        scalaMap = SparkContext._active_spark_context._jvm.PythonUtils.toScalaMap(paramMap)
        self._java_obj = self._new_java_obj("ml.dmlc.xgboost4j.scala.spark.XGBoostEstimator", self.uid, scalaMap)
        self._defaultParamMap = paramMap
        self._paramMap = paramMap

    def setParams(self, paramMap={}):
        return self._set(paramMap)

    def _create_model(self, java_model):
        return XGBoostClassificationModel(java_model)


class XGBoostClassificationModel(JavaModel, JavaClassificationModel, JavaMLWritable, JavaMLReadable):
    def getBooster(self):
        return self._call_java("booster")

    def saveBooster(self, save_path):
        jxgb = JavaWrapper(self.getBooster())
        jxgb._call_java("saveModel", save_path)
