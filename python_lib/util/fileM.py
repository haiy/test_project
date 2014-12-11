import sys

def read_lines(fileName, mode='r', failResult=[]):
    try:
        f = open(fileName, mode)
        n = f.readlines()
        f.close()
        n = [ l.strip('\n') for l in n ]
        return n
    except Exception, e:
        #print "read lines error : " + trace_info()
        return failResult
