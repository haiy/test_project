package com.haiy.file

import java.io.{File, PrintWriter}

import scala.io.Source

/**
 * Simple file io
 * Created by haiy on 4/16/15.
 */
object IO {
  def getListOfFiles(dir: String): List[File] = {
    val d = new File(dir)
    if (d.exists) {
      if (d.isDirectory) d.listFiles.filter(_.isFile).toList
      else List(d)
    } else {
      List[File]()
    }
  }

  def getLines(path: String): Seq[String] = {
      getListOfFiles(path).flatMap { f =>
        Source.fromFile(f).getLines()
      }
  }

  def writeLines(path: String, lines: Seq[String]) = {
    val f = new File(path)
    val pw = new PrintWriter(f)
    lines.foreach(l => pw.write(l+"\n"))
    pw.close()
  }

  def delFile(path: String): Boolean = {
    val fs = new File(path)
    fs.delete()
  }
}
