#!/bin/bash
spark-submit --driver-memory 4G --executor-memory 5G --class haiy.localTest.GraphxLocal --master local[4] target/learnGraph-0.0.1.jar --executor-cores 2 --num-executors 1 
