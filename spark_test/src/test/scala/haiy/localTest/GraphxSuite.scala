package haiy.localTest

import org.apache.spark.SparkContext
import org.apache.spark.graphx.PartitionStrategy.RandomVertexCut
import org.apache.spark.graphx._

import org.scalatest.FunSuite

/**
 * Created by haiy on 1/16/15.
 */
class GraphxSuite extends FunSuite with LocalSparkContext {
  def starGraph(sc: SparkContext, n: Int): Graph[String, Int] = {
    Graph.fromEdgeTuples(sc.parallelize((1 to n).map(x => (0: VertexId, x: VertexId)), 3), "v")
  }

  test("Graph.fromEdgeTuples") {
    withSpark { sc =>
      println("Here is the resutl : ")
      val ring = (0L to 100L).zip((1L to 99L) :+ 0L)
      val doubleRing = ring ++ ring
      val graph = Graph.fromEdgeTuples(sc.parallelize(doubleRing), 1)
      assert(graph.edges.count() === doubleRing.size)
      assert(graph.edges.collect.forall(e => e.attr == 1))

      // uniqueEdges option should uniquify edges and store duplicate count in edge attributes
      val uniqueGraph = Graph.fromEdgeTuples(sc.parallelize(doubleRing), 1, Some(RandomVertexCut))
      assert(uniqueGraph.edges.count() === ring.size)
      assert(uniqueGraph.edges.collect.forall(e => e.attr == 2))
    }
  }
}
