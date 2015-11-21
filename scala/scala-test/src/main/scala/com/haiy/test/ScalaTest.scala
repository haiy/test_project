package com.haiy.test

import java.util.ArrayList

import com.duozhun.zerone.IndirectMap
import com.duozhun.zerone.hbase.HbaseConnector
import com.duozhun.zerone.utils._
import org.apache.spark.SparkContext._
import org.apache.spark._
import org.apache.spark.graphx._

import scala.collection.JavaConversions._
import scala.collection.JavaConverters._
import scala.collection.mutable


object ScalaTest{
  def main(args:Array[String]){
    val conf = new SparkConf().setAppName("ScalaTest")
    val spark = new SparkContext(conf)
    //val tableData = HbaseConnector.getAllRows("IdTableTest", spark).mapToPair(t -> (t._2._2, t._1)).groupByKey().flatMapToPair(l => l.grouped(2))
    val testData = spark.parallelize(Array(
      (1L,("col1","z")),
      (1L, ("col2","k")),
      (2L, ("col3", "k")),
      (2L,("col1","zk")),
      (3L, ("col2","a")),
      (3L, ("col3", "zk")),
      (4L,("col1","zk")),
      (4L, ("col2","d")),
      (5L, ("col3", "c")),
      (5L, ("fuckt","f")),
      (6L, ("col3", "e")),
      (6L, ("fuckt","f"))
    ))
    //生成边的二元组RDD
    val tableData = testData.map(t => (t._2._2, t._1)).groupByKey().flatMap(
      l => l._2.map(i => (l._2.head, i))
    )
    //val tableData2 = HbaseConnector.getAllRows("IDTableTest", spark).mapToPair(t -> (t._2._2+t._2._1, t._1))
    //val totoalData = tableData.join(tableData2).count()
    //println(totoalData);
    //val graph = GraphLoader.edgeListFile(spark, "/graphx/data/test_followers.txt")
    val edgeRdd = spark.parallelize(Array((1L,3L), (2L,3L), (4L,5L),
      (5L,7L), (6L,8L), (4L,8L)))

    val graph = Graph.fromEdgeTuples(tableData, 0)
    val cc = graph.connectedComponents().vertices.map{
      case (id, target) => (target, id)
      }.groupByKey().map{
        var userIdInfo = new mutable.HashMap[String, String]()
        l => l._2.map{
          vertexId => {
            // 这个地方需要替换成从Hbase读取user为map
            val userId: String = vertexId.toString
            val currentUser:mutable.Map[String, String] = new ArrayList(HbaseConnector.getRow("IDTableTest", userId).values()).get(0).asScala
            //val currentUser = new HashMap[String, String](("1","v1"), ("2","v2"))
            userIdInfo ++= currentUser.map{case (k, v) => (v, k) }
            // HbaseConnector.delRow("IDTableTest", userId)
            }
          }
          var conflict: Boolean = false
          userIdInfo.foreach{
            case (idValue, idType) => {
              userIdInfo.get(idType) match {
                case None => {
                  userIdInfo -= (idValue)
                  userIdInfo += (idType->idValue)
                }
                case Some(value) => {
                  val oldNick: String = KeyFetcher.get(IndirectMap.idToSite.get(idType), idValue)
                  val newNick: String = KeyFetcher.get(IndirectMap.idToSite.get(idType), value)
                  if ( ! oldNick.equals(newNick)){
                    conflict = true
                  }
                }
              }
            }
          }
          if ( ! conflict ){
            HbaseConnector.addRow("IDTableTest", mapAsJavaMap(Map((l._1.toString->userIdInfo))).asInstanceOf[java.util.Map[String,java.util.Map[String,String]]] )
          }
      }
          /*
          val users = spark.textFile("/graphx/data/test_users.txt").map { line =>
            val fields = line.split(",")
            (fields(0).toLong, fields(1))
      }
      val ccByUsername = users.join(cc).map {
        case (id, (username, cc)) => (username, cc)
          }
      // Print the result
      println(ccByUsername.collect().mkString("\n"))
           */
          println(cc.collect().mkString("\n"))
      }
  }
