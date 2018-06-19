## pyspark start

通过具体的实例来演示如何使用pyspark完成数据加工和模型构建工作.

### How to begin

对pyspark的学习主要从三个大的方面来进行:

- 1 学习基本的数据结构和计算模型, [代码](1_basic_datatype.py).知识要点:
    
    - RDD = distribute list
    - DataFrame = RDD with schema
    - file io, 
    - map each, DataSet[Row] + `f(Row) =>Row` DataSet[Row]  
    
- 2 熟悉reduce操作, [代码](2_app_count.py).知识要点:
    
    - reduceByKey, RDD[(k,v)] + `f(v1:V, v2:V)=>V`= RDD[(k,v)]
    - groupByKey, RDD[(k,v)] =>  RDD[(k,[v1,v2,v3]]
    - flatMap, RDD[v] + `f(v) => List` = RDD[t]
    - sort

- 3  建模流程,数据加工,超参调整,模型保存.[代码](3_applist_model.py).知识要点:
    
    - `Row(label=1,features=Vectors.dense([...]))`
    - `Pipeline(stages=[lr_model])`
    - 超参调整, `ParamGridBuilder`
    - 模型交叉验证, `cvModel.bestModel`
    - 模型评估, `BinaryClassificationEvaluator`, `MulticlassClassificationEvaluator`   

#### dir structure

```
├── 1_basic_datatype.py 
├── 2_app_count.py      
├── 3_applist_model.py
├── README.md
├── data                      # 输入和输出数据
│   ├── README.md
│   ├── input
│   └── output
├── metastore_db
├── spark-warehouse
├── pyspark-demo.ipynb
├── ispark.sh                 # 启动本地的pyspark环境  
└── yarn_run.sh               # 将任务提交到yarn
```

**Note**: 
- 建议使用pyspark交互环境进行代码调试，这时候选取少量数据进行代码编写，
然后流程代码无误后使用yarn_run.sh将任务提交到集群。
- 在使用交互环境，文件保存csv时加上`.option("codec","none")`避免出错
