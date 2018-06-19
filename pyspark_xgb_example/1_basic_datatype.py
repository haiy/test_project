import sys

from pyspark.sql.session import SparkSession
from pyspark.sql.types import Row


def select_cols(single_record):
    '''
    transform single line data
    :param a single spark Row
    :return: row selected with target columns
    '''
    data_dict = single_record.asDict()

    # filtered_dict = dict((k,data_dict[k] for k in ["uid","date"]))
    # return Row(**filtered_dict)

    #return Row(uid=data_dict["uid"], applist=data_dict["applist"])

    return Row(data_dict["uid"], data_dict["applist"])



if __name__ == "__main__":
    if (len(sys.argv)<3):
        print("Usage: 1_basic_datatype.py <input_data_path> <output_path>")

    input_data = sys.argv[1] if len(sys.argv) > 1 else "data/input/100_line_test.csv"
    output_data = sys.argv[2] if len(sys.argv) > 2 else "data/output/datatype"

    spark = SparkSession.builder.appName("AppCount").getOrCreate()

    input_df = spark.read.option("header", True).csv(input_data)

    # rdd,http://spark.apache.org/docs/2.1.0/api/python/pyspark.sql.html#pyspark.sql.DataFrame.toDF
    filtered_df = input_df.rdd.map(select_cols).toDF(["uid", "applist"])

    # http://spark.apache.org/docs/2.1.0/api/python/pyspark.sql.html#pyspark.sql.DataFrameWriter
    # https://stackoverflow.com/questions/35861099/overwriting-a-spark-output-using-pyspark
    # .mode("overwrite")
    filtered_df.write.option("codec","org.apache.hadoop.io.compress.GzipCodec")\
        .option("header", True).csv(output_data)


