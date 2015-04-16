package com.haiy.file

import org.scalatest.FunSuite

/**
 * Test the file io object
 * Created by haiy on 4/16/15.
 */
class TestIO extends FunSuite{
  test("getLines") {
    val f = getClass.getResource("/testIO.txt").getPath
    val content = IO.getLines(f)
    assert(content == Seq("a","b","c"))
  }

  test("writeLines") {
    val f = "tmpIOWrite.txt"
    IO.writeLines(f, Seq("a","b","c"))
    val content = IO.getLines(f)
    assert(content == Seq("a","b","c"))
    IO.delFile(f)
  }
}
