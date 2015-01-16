package haiy.localTest

import org.apache.spark.graphx.PartitionStrategy._
import org.apache.spark.graphx._
import org.apache.spark.{SparkConf, SparkContext}

/**
 * Created by haiy on 1/13/15.
 */
object GraphxLocal {

  def main(args: Array[String])  {
    val conf = new SparkConf()
    val sc = new SparkContext(conf)
    val ring = (0L to 100L).zip((1L to 99L) :+ 0L)
    val doubleRing = ring ++ ring
    //Graph.fromEdgeTuples(sc.parallelize((1 to n).map(x => (0: VertexId, x: VertexId)), 3), "v")

    val graph = Graph.fromEdgeTuples(sc.parallelize(doubleRing), 1)
    println(graph.edges.count())
    println(graph.edges.collect.forall(e => e.attr == 1))

    // uniqueEdges option should uniquify edges and store duplicate count in edge attributes
    val uniqueGraph = Graph.fromEdgeTuples(sc.parallelize(doubleRing), 1, Some(RandomVertexCut))
    //assert(uniqueGraph.edges.count() === ring.size)
    assert(uniqueGraph.edges.collect.forall(e => e.attr == 2))
    println(uniqueGraph.edges.count())
    assert(uniqueGraph.edges.collect.forall(e => e.attr == 2))
  }


}
