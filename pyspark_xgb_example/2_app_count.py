import sys
import pandas as pd

from pyspark.sql.session import SparkSession
from pyspark.sql.types import Row
from pyspark.sql.functions import *

# spark Row == named tuple a = (age=10, sex='male', weight=45)
row2series = lambda r: pd.Series(r)
series2row = lambda s: Row(**s.to_dict())

'''
task desc: 根据用户的applist来抽取所有用户安装的app列表,并统计用户安装频次最高的app
data input: data/input/100_line_test.csv
'''


def single_line_transform(single_line):
    '''
    单行维度的数据处理
    :param single_line: 输入是一行原始的数据spark row格式的数据
    :return: spark row格式的数据
    '''
    return (single_line.uid, single_line.applist)


def single_user_hanler(record_list_str_1, record_list_str_2):
    '''
    单用户维度的数据处理
    :param record_list_str + record_list_str
    :return: str
    '''
    return record_list_str_1 + ";" + record_list_str_2


def flat_applist(user_applist):
    '''
    将单行的applist记录变成每个app名字一行
    :param applist: 原始的一行数据
    :return: applist列表
    '''
    uid, applist = user_applist
    appset = set(applist.split(";"))
    return [(appname, 1) for appname in appset]


def sum_app(input_x, input_y):
    return input_x + input_y


if __name__ == "__main__":

    input_data = sys.argv[1] if len(sys.argv) > 1 else "data/input/100_line_test.csv"
    output_data = sys.argv[2] if len(sys.argv) > 2 else "data/output/appcount"

    spark = SparkSession.builder.appName("AppCount").getOrCreate()

    input_df = spark.read.option("header", True).csv(input_data)

    output_df = input_df.rdd \
        .map(single_line_transform) \
        .reduceByKey(single_user_hanler) \
        .flatMap(flat_applist)

    print(list(output_df.countByKey()))

    # 按用户维度计算每个app出现的次数
    app_count_df = output_df.reduceByKey(sum_app).toDF(["app", "count"])

    # .mode("overwrite")
    app_count_df.orderBy("count", ascending=False).coalesce(1)\
        .write.option("header", True).option("codec","none")\
        .csv(output_data)

    print("total app count : ", app_count_df.rdd.count())
