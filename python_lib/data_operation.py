#!/usr/bin/python2.7
#-*- coding:utf8 -*-
#author : haiyangfu512@gmail.com
#date:Sat Mar 15 13:43:14 CST 2014

#这个文件下的类主要是数据的工具类
#包含数据的获取，抽取，保存的方法
#不负责数据的流程


import os, sys, re, urllib2, traceback, errno
import shutil
import random
import StringIO
import pickle

import glob
import copy
from threading import Lock
import subprocess
from subprocess import PIPE
import shlex
import cookielib
import MySQLdb as mdb

#from PIL import Image
#import HTMLParser

DBG = True & False
LOCAL_TEST = True & False
DBG_SINGLE = True & False

def trace_info():
    exc_type, exc_value, exc_traceback = sys.exc_info()
    exc_lines = traceback.format_exc()
    exc_lines = exc_lines.replace('\n',',')
    return exc_lines

def exe_sys_cmd(cmd_str):
    args = shlex.split(cmd_str)
    try:
        msg1, msg2 = subprocess.Popen(args, stdout=PIPE, stderr=PIPE).communicate()
    except Exception, e:
        print "cmd error: ", cmd_str, str(e), trace_info()
        return False, msg1 + msg2 + trace_info()

    msg = msg1 + msg2
    return True, msg

class file_operation:
    def __init__(self, fileName = None):
        self.fileName = fileName

    def read(self, fileName):
        try:
            f = open(fileName)
            content = f.read()
            f.close()
            return content
        except Exception, e:
            print str(e), trace_info()
            sys.exit()

    def save(self, fileName, content, mod='w'):
        try:
            f = open(fileName, mod)
            f.write(content)
            f.close()
        except Exception, e:
            print str(e), trace_info()
            sys.exit()

    def count_lines(self, fileName = None):
        if not fileName:
             fileName = self.fileName
        try:
            f = open(fileName, 'r')
            n = len(f.readlines())
            f.close()
            return n
        except Exception, e:
            print "count lines failed:" + trace_info()
            return None

    def read_lines(self, fileName = None):
        try:
            if not fileName:
                fileName = self.fileName
            f = open(fileName, 'r')
            n = f.readlines()
            f.close()
            n = [ l.strip('\n') for l in n ]
            return n
        except Exception, e:
            print "read lines error : " + trace_info()
            return None

    def add_list(self, fileName = None, listContent = [], mod = 'w'):
        if not fileName:
             fileName = self.fileName
        f = open(fileName, mod, 0)
        f.write('\n'.join(listContent))
        f.close()
        return len(listContent)

    def get_list(self, fileName = None, deli = ',', num = 0):
        if fileName == None:
            fileName = self.fileName
        try:
            f = open(fileName, 'r')
            con = f.readlines()
            f.close()
            con = [ i.split(deli)[num].strip('\n') for i in con ]
            return con
        except Exception, e:
            print "File get list error: ", trace_info()
            return None

    def clean_file(self, fileName = None ):
        if not fileName:
             fileName = self.fileName
        f = open(fileName, 'w', 0)
        f.close()

    def del_file(self, fileName = None):
        if not fileName:
            fileName = self.fileName
        try:
            os.remove(fileName)
        except Exception, e:
            print 'del file ', trace_info()

    def copy_file(self, src, dst):
        self.add_list( dst, self.read_lines(src) )

    def get_file_list(self, dst_dir, file_type_str = None):
        flst = []
        if file_type_str:
            ls_opt = dst_dir + file_type_str
            flst = glob.glob(ls_opt)
            return flst
        return [dst_dir + f for f in os.listdir(dst_dir)]

    def merge_files(self, file_list, dst):
        '''将多个文件合并在一起, 并写入对应的list文件'''
        pos_info = []
        self.clean_file(dst)
        try:
            fp = open(dst+'.list', 'a')
        except:
            fp = open(dst+'.list', 'w')

        start_pos = self.get_size(dst)
        #将合并过的文件以及其长度存入列表中
        pos_info = [[f, self.merge_file(f, dst)] for f in file_list]

        for f in pos_info:
            f_name = f[0]
            f_start = start_pos
            f_len = int(f[1])
            f_info = [f_name, f_start, f_len]
            fp.write(' '.join([str(i) for i in f_info]) + '\n')
            start_pos += int(f[1])
        fp.close()

        return pos_info

    def copy_part_file(self, src_file, dst_file, start, end):
        f = open(src_file, 'r')
        df = open(dst_file, 'w')
        f.seek(start)
        df.write( f.read(end-start+1) )
        df.close()
        f.close()
        return end-start+1

    def merge_file(self, src, dst):
        '''将两个文件合并在一起'''
        try:
            mf = open(dst, 'a', 0)
        except:
            mf = open(dst, 'w', 0)

        f = open(src, 'r')
        c = f.read()
        f.close()
        mf.write(c)
        mf.close()
        return len(c)

    def get_size(self, src):
        return os.path.getsize(src)

    def __call__(self, fileName):
        self.__init__(fileName)
        return self

class hdfs_operation:
    def copy_to_hdfs(self, src, dst):
        exit_code, msg = exe_sys_cmd("hadoop fs -copyFromLocal %s %s" % (src, dst))
        if exit_code is True:
            return True, msg
        else:
            return False, msg

    def copy_from_hdfs(self, src, dst):
        self.rm_hdfs_file(dst)
        exit_code, msg = exe_sys_cmd("hadoop fs -copyToLocal %s %s" % (src, dst))
        if exit_code is True:
            return True, msg
        else:
            return False, msg

    def rm_hdfs_file(self, dst):
        exit_code, msg = exe_sys_cmd("hadoop fs -rm %s" % (dst))
        if exit_code is True:
            return True, msg
        else:
            return False, msg

    def list_hdfs_dir(self, dst):
        exit_code, msg = exe_sys_cmd("hadoop fs -ls %s" % (dst))
        if exit_code is True:
            return True, msg
        else:
            return False, msg

    def make_hdfs_dir(self, dst):
        exit_code, msg = exe_sys_cmd("hadoop fs -mkdir %s" % (dst))
        if exit_code is True:
            return True, msg
        else:
            return False, msg

class dir_operation:
    def __init__(self, dir_path = None):
        if dir_path:
            self.mkdir(dir_path)

    def mkdir(self, dir_path):
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)

    def clean_dir(self, dir_path):
        try:
            shutil.rmtree(dir_path)
        except:
            if DBG : print trace_info()
            pass
        self.mkdir(dir_path)

class database_operation:
    def __init__(self, db_host, db_user, db_passwd, db_used = None):
        try:
            self.con =  mdb.connect(
                    host = db_host,
                    user = db_user,
                    passwd = db_passwd,
                    charset = 'utf8'
                    )
            self.host = db_host
            self.user = db_user
            self.passwd = db_passwd
            self.charset = 'utf8'
            self.cur = self.con.cursor()
            self.exe = self.cur.execute
            self.fetchone = self.cur.fetchone
            self.fetchall = self.cur.fetchall
            self.esc = mdb.escape_string("'")

        except Exception, e:
            print "Mysql connect error : ", trace_info()
            sys.exit()

        if db_used is not None:
            self.cur.execute("use %s" % db_used)

    def _connect(self):
            self.con =  mdb.connect(
                    host = self.host,
                    user = self.user,
                    passwd = self.passwd,
                    charset = 'utf8'
                    )
            self.cur = self.con.cursor()
            self.exe = self.cur.execute
            self.fetchone = self.cur.fetchone
            self.fetchall = self.cur.fetchall
            self.esc = mdb.escape_string("'")

    def qa(self, queryStr):
        retry = 5
        msg = ''
        while retry > 0:
            retry -= 1

            if 'MySQL server has gone away' in msg:
                self.close()
                self._connect()
            elif msg:
                print "MySQL query error : ", queryStr, trace_info()

            try:
                self.cur.execute(queryStr)
                res = self.fetchall()
                msg = ''
                retry = 0
                return res
            except Exception, e:
                msg = trace_info() + str(e)

    def close(self):
        self.__del__()

    def __del__(self):
        try:
            self.cur.close()
            self.con.close()
        except Exception, e:
            if DBG : print "MySQL close error :", trace_info()
            pass

class content_fetcher:
    # XXX Don't change any thing unless you know what you are doing!!
    # Commonly you do not need change any single word about this class.

    def __init__(self, proxy_list = [], headers = []):
        # type of a proxy should be dict like {'http':0.0.0.0:000}
        #the header should be key, value tuples
        self.proxies = proxy_list
        self.headers = headers
        if not self.headers:
            self.headers = self.get_header()

        self.enable_cookie = True

    def set_proxy(self, proxy = {}):
        self.proxies = [proxy]

    def set_header(self, header):
        self.headers = header

    def decode_page(self, res):
        '''
        根据响应头中的content-type中的编码格式来解码
        '''
        responseHeader = res.headers
        content = res.read()

        if responseHeader.has_key('Content-Encoding') \
                and responseHeader['Content-Encoding'] == 'gzip':
            import StringIO
            import gzip
            stream = StringIO.StringIO( content )
            gzipper = gzip.GzipFile(fileobj= stream)
            content = gzipper.read()

        if responseHeader.has_key('Content-Type') and 'charset' in responseHeader['Content-Type']:
            s = re.search('charset.*?(\w+)', responseHeader['Content-Type'])
            charset = s.group(1)
            if content != '':
                content = content.decode(charset,'ignore')
                content = content.encode('utf8', 'ignore')
                pass

        return content

    def request_url(self, url, retry_times = 20):
        pageContent = None
        msg = ''

        while not pageContent and retry_times > 0 :
            retry_times -= 1
            header = random.choice( self.headers )
            proxy = {}
            if len(self.proxies) > 1 : proxy = random.choice(self.proxies)
            proxyAdded = urllib2.ProxyHandler( proxy )
            cj = cookielib.CookieJar()
            ck_handler = urllib2.HTTPCookieProcessor(cj)
            if not self.enable_cookie :
                ck_handler = urllib2.UnknownHandler()

            proxyOpener = urllib2.build_opener(proxyAdded, ck_handler )

            proxyOpener.addheaders = header
            try :
                pageContent = self.decode_page( proxyOpener.open(url, timeout = 20.0) )
                #print pageContent
            except Exception,e:
                #print "error in request url :", trace_info(),proxy,url
                msg = "request url error: " + trace_info()
                pageContent = None
        return pageContent, msg


    def get_header(self):
        #XXX 这个headers很重要！！！如果不明白请不要动。
        headers = []

        headers.append({
            'Accept':  '*/*',\
            'Accept-Encoding': 'gzip, deflate',\
            'Accept-Language':'zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3',\
            'Cache-Control':'max-age=0',\
            'Connection':'keep-alive',\
            'Host':'mdskip.taobao.com',\
            'Referer':'http://detail.tmall.com/item.htm?id=25654640401&tbpm=3',\
            'User-Agent':'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:26.0) Gecko/20100101 Firefox/26.0'
            })
        headers.append({
            'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/33.0.1750.146 Safari/537.36',\
            'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',\
            'Accept-Language': 'zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3',\
            'Accept-Encoding': 'gzip, deflate, sdcn',\
            'Referer': 'http://detail.tmall.com/item.htm?id=37396557667',\
            'Host':    'mdskip.taobao.com',\
            'Connection':'keep-alive',\
        })

        for i in range(0, len(headers)):
            headers[i] = tuple([(k, v) for k, v in headers[i].iteritems()])
        return headers

# vim: set fdm=indent:
