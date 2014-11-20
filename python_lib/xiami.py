#!/usr/bin/python2.7
#-*- coding:utf8 -*-
#author : haiyangfu512@gmail.com
#date: 2014年 5月20日 星期二 09时31分34秒 CST
import re
import sys
from data_operation import content_fetcher

url_fetcher = content_fetcher()

def collect_page():
    url = "http://www.xiami.com/collect"
    content, failed = url_fetcher.request_url(url)
    if failed:
        print content
        sys.exit()

    styles = re.findall(r'http://www.xiami.com/search/collect\?.*?key=.*?"', content)
    print styles
    content, failed = url_fetcher.request_url(styles[0])

    collect = re.findall(r'http://www.xiami.com/song/showcollect/id/\d+', content)
    print collect

def test():
    collect_page()


if __name__ == '__main__':
    test()
