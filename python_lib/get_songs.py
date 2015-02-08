#!/usr/bin/python
import json
import sys
import urllib2
import cookielib

def writeFile(name, content):
    f = open(name, "w")
    f.write(content)
    f.close()

def readFile(name):
    fp = open(name)
    fileContent = fp.read()
    fp.close()
    return fileContent

def readHeader(name):
    headerStr = readFile(name)
    hLst = headerStr.split("\n")
    hLst.remove("")
    resL = []
    for i in hLst:
        print "current i",i
        i =  i.replace(" ", "")
        pos = i.index(":")
        iN = i[:pos]
        iC = i[pos:]
        resL.append((iN, iC))
    return resL

def fetchUrl(url, headers):
    print "Begin to download %s." % url
    req = urllib2.Request(url, headers)
    if DEBUG:
        print "Headers : ", req.header_items()
        pass
    urlFp = urllib2.urlopen(url, timeout=5)
    c = urlFp.read()
    if len(c) > 0 :
        return c
    return None

def readCookie(fcj, cookieFileLocation):
    fcj.load(cookieFileLocation)

def writeCookie(fcj, dstName):
    f = open(dstName, "w")
    f.close()
    fcj.save(dstName)

def fetchUrl(url, headerPos, cookiePos):
    headers = readHeader(headerPos)
    cj = cookielib.MozillaCookieJar()
    # readCookie(cj, cookiePos)
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    opener.add_headers = headers
    r = opener.open(url, timeout=3*60)
    print "downloading %s ." % r.geturl()
    print "response info  %s ." % r.info()
    print "response code %s ." % r.getcode()
    content = r.read()
    if len(content) > 0:
        writeCookie(cj)
        return content
    return None

def writeSongs(infoJsonStr):
   infoJson = json.loads(infoJsonStr)
   songInfo = infoJson['song']
   totalSize = len(songInfo)
   successSize = 0
   for song in songInfo:
       songUrl = song["url"]
       songTitle = song["title"].replace(" ", "_")
       # songContent = fetchUrl(songUrl)
       songContent = fetchUrl(songUrl, "header.txt", "cookie.txt")
       if songContent:
           writeFile(songTitle, songContent)
           successSize += 1
           print "Downloaded %s success! %d of %d", (songTitle, successSize, totalSize)

if __name__ == "__main__":
    fp = open(sys.argv[1])
    fileContent = fp.read()
    fp.close()
    writeSongs(fileContent)
    pass
