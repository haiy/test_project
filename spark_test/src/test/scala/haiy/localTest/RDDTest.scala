package haiy.localTest

import org.apache.spark.rdd.RDD
import org.scalatest.FunSuite

/**
 * Created by haiy on 1/16/15.
 */
class RDDTest extends FunSuite with LocalSparkContext{
  test("UpdateMap read data") {
    withSpark { sc =>
      val dataSource: RDD[(String, Map[String, String])] = sc.parallelize(List(
        //single site user
        ("1", Map(("idCol1", "idVal1"))),
        ("5", Map(("idCol1", "idVal1"))),
        ("2", Map(("idCol3", "idVal13"))),

        // multi site user
        ("3", Map(("idCol1", "idVal1"),
          ("idCol2", "idVal2"),
          ("idCol3", "idVal3"))),

        ("4", Map(("idCol4", "idVal21"),
          ("idCol2", "idVal2"),
          ("idCol5", "idVal13")))))
      println("input info" + dataSource.collect().mkString("\t"))
    }
  }
}
