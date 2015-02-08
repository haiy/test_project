#!/bin/python
#Given a string containing only digits, restore it by returning all possible valid IP address combinations.
#For example:
#Given "25525511135",
#return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

class Solution:
    # @param s, a string
    # @return a list of strings
    def restoreIpAddresses(self, s):
        l = len(s)
        tail1 = l
        print s
        pass

s = Solution()

l = "25525511135"

def partCheck(s):
    int (s) < 255

#part(n) = [start:startPos + sz] sz
#total_len left_len
#left_len > left_part
#left_len < 3*left_part

#start=0 n=1
resultIp = []
def getPartIp(l, start, raw_len, n, ip):
    if start == raw_len and n == 4:
        ip = ip[:-1]
        resultIp.append(ip)
        return

    left_len = raw_len - start
    left_part = 4 - n
    if left_len > 3*left_part:
        print ip, "bigger 3 break"
        return
    if left_len < left_part :
        print ip, "break"
        return

    part = ""
    for i in l[start:start+3]:
        part += i
        if int(part) <= 255  :
            ip += i
            print "part",n, ":", part, "ip",ip
            getPartIp(l, start + len(part), raw_len, n+1, ip + ".")

print l
getPartIp(l, 0, len(l), 0, "")
print resultIp
