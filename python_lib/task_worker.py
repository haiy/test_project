#!/usr/bin/python2.7
#-*- coding:utf8 -*-
#author : haiyangfu512@gmail.com
#date:Sat Mar 15 13:43:14 CST 2014

import re, sys, os, time, datetime, traceback, operator, random
import Queue, urllib2
from threading import Thread,Lock
from data_operation import file_operation, trace_info

reload(sys)
sys.setdefaultencoding('utf8')

DBG = True & False #debug stat

def dynamic_print(msg, last_length):
    sys.stdout.write('\b' * last_length)
    sys.stdout.write(' ' * last_length)
    sys.stdout.write('\b' * last_length)
    con = str(datetime.datetime.now()) + '\t' + str(msg)
    sys.stdout.write(con)
    sys.stdout.flush()
    last_length = len(con)
    return last_length

class worker_thread(Thread):
    def __init__(self, myName, taskQueue, succFp, failedFp, taskFunctionPointer):
        super(worker_thread, self).__init__()
        self.name = myName
        self.taskQ = taskQueue
        self.failedFp = failedFp
        self.succFp = succFp
        self.taskFuncFp = taskFunctionPointer
        self.lock = Lock()
        self.taskSize = self.taskQ.qsize()

    def run(self):
        while True:
            try :
                self.currentTask = self.taskQ.get(False)
            except Exception, e:
                break

            try:
                success, msg = self.taskFuncFp(self.currentTask)
                self.lock.acquire()
                if success is True:
                    res_str = str(datetime.datetime.now()) + '\t' + str(self.currentTask) + '\t' + str(msg)
                    self.succFp.write( res_str + '\n')
                    self.succFp.flush()

                else:
                    self.failedFp.write(str(self.currentTask) + '\t' + str(msg) +'\n')
                    self.failedFp.flush()


                global count
                count += 1
                print_count = int(0.25 * self.taskSize)
                if print_count < 1:
                    print_count = 1
                if count % (print_count) == 0:
                    global last_length
                    #last_length = dynamic_print( "%s items handled.\n" % count, last_length )
                    print datetime.datetime.now(), "%s items handled." % count
                self.lock.release()
            except :
                exc_type, exc_value, exc_traceback = sys.exc_info()
                exc_lines = traceback.format_exc()
                exc_lines = exc_lines.replace('\n',',')
                print exc_lines

            self.taskQ.task_done()

def singe_round_task(taskFile, successFile, failedFile,  taskFunctionFunc, threadNum ):
    '''Total work flowchart'''
    fileO = file_operation()
    taskItemList = fileO.get_list(taskFile)
    print "%s, Get %s tasks . " % (datetime.datetime.now(), len(taskItemList))

    succFp = failedFp = None
    if os.path.exists(successFile):
        succFp = open(successFile, 'a')
    else:
        succFp = open(successFile, 'w')
    failedFp = open(failedFile, 'w')

    taskQueue = Queue.Queue()
    for task in taskItemList:
        taskQueue.put(task)

    workers = []
    #thread has its own retry times
    for i in range(threadNum):
        workers.append( worker_thread('worker'+str(i), taskQueue, succFp, failedFp, taskFunctionFunc) )

    for worker in workers:
        worker.start()

    #wait till all threads exited
    existAliveThread = True
    while existAliveThread:
        existAliveThread = False
        for worker in workers:
            if worker.isAlive():
                existAliveThread = True
                worker.join()

    succFp.close()
    failedFp.close()

    return fileO(successFile).count_lines(), fileO(failedFile).count_lines()

#多线程的重试函数
def task(taskListFile, successFile, failedFile,  taskFunctionFunction, stopPercent = 0.05, retryTimes = 30, threadNum = 500):
    fpO = file_operation()
    #failedFile = 'failed_items.ids' #failed tasks and relative message
    #timeStamp = datetime.datetime.now().strftime('%Y%m%d%H%M')
    #successFile = '%s_success_items.info' % timeStamp

    fpO.clean_file(failedFile)
    fpO.clean_file(successFile)

    global count
    global last_length
    count = 0
    last_length = 0

    totalTaskSize = fpO.count_lines(taskListFile)
    if totalTaskSize < threadNum:
        threadNum = totalTaskSize

    succ, failure = singe_round_task(taskListFile, successFile, failedFile, taskFunctionFunction, threadNum)
    if DBG : print "Success file contain %s, failed: %s" % (succ, failure)

    failurePercent = float(failure)/totalTaskSize
    totalTimes = retryTimes
    if DBG : print failure, totalTaskSize, failurePercent, retryTimes
    failed_record = []
    failed_record.append(failure)

    def equal_failed(fr):
        if len(fr) < 3:
            return False
        return fr[-1]==fr[-2]==fr[-3]

    while retryTimes > 0 and failurePercent > stopPercent and not equal_failed(failed_record):
        if DBG : print "stat:",equal_failed(failed_record)
        print "content",failed_record
        print "Current failure %s, stopPercent %s." % (failurePercent,stopPercent)
        count = 0
        retryTimes -= 1
        fpO.add_list('tmpTask', fpO.get_list(failedFile, '\t'), 'w')
        currentTaskSize = fpO.count_lines(failedFile)
        if currentTaskSize < threadNum:
            threadNum = currentTaskSize

        succ, failure = singe_round_task('tmpTask', successFile, failedFile, taskFunctionFunction, threadNum)
        failed_record.append(failure)
        failurePercent = float(failure)/totalTaskSize
        print( "%s of %s. success:%s, failed: %s.\n" % (retryTimes, totalTimes, succ, failure))
        fpO.del_file('tmpTask')

    return fpO.count_lines(successFile), fpO.count_lines(failedFile)

#单个函数流程的重试函数
def retry_worker(function, **arguments):
    retry = 3
    success = False
    msg = ''

    while retry > 0 and not success:
        retry -= 1
        success, msg = function(**arguments)
        if success:
            return True, msg
    return False, msg
