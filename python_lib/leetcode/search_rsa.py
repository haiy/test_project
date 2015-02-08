#!/usr/bin/python
#Suppose a sorted array is rotated at some pivot unknown to you beforehand.
#(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
#You are given a target value to search. If found in the array return its index, otherwise return -1.
#You may assume no duplicate exists in the array.

class Solution:
    # @param A, a list of integers
    # @param target, an integer to be searched
    # @return an integer
    def search(self, A, target):
        pass

def search(l, num):
    start = 0
    end = len(l) - 1
    if end == -1:
        return -1
    resPos = 0
    resPos = binSearch(l, 0, end, num, resPos)
    return resPos

## start, end is index, mid is the
def binSearch(l, start, end, target, resPos):
    halflen = (end - start + 1)/2
    mid = start + halflen - 1
    print "current mid :", mid, l[mid]
    if l[mid] == target:
        resPos = mid
        return resPos
    if l[start] == target:
        return start
    if l[end] == target:
        return end

    if l[end] < l[start]:
        if target > l[start]:
            if target < l[mid]:
                end = mid - 1
            elif target > l[mid]:
                if l[mid] >= l[start]:
                    start = mid + 1
                elif l[mid] < l[start]:
                    end = mid - 1
        elif target < l[end]:
            if target > l[mid]:
                start = mid + 1
            elif target < l[mid]:
                if l[mid] >= l[end]:
                    start = mid + 1
                elif l[mid] < l[end]:
                    end = mid - 1
    else:
        if target > l[mid]:
            start = mid + 1
        elif target < l[mid]:
            end = mid - 1

    halflen = (end - start + 1)/2
    new_mid = start + halflen - 1
    print "here new mid ",new_mid
    if new_mid == mid: return -1

    print "left searh area: ", l[start:end+1], "start :", start, "end :",end
    return binSearch(l, start, end, target, resPos)

l = []
print "1 found : ",search(l, 1)
l = [3, 5, 1]
print "input : ",l
print "3 found 3: ",search(l, 5)

l = [4,5,6,7,8,1,2,3]
print "input : ",l
print "2 found 1 : ",search(l, 5)
l = [1,2,3]
print "input : ",l
print "3 found 3: ",search(l, 3)
l = [4,5,6,7,0,1,2]
print "input : ",l
print "4 found 6: ",search(l, 6)
l = [1,2,3,4,5,6]
print "input : ",l
print "5 found 4: ",search(l, 4)
l = [ 7,8,1,2,3,4,5,6]
print "input : ",l
print "6 found : ",search(l, 2)
l =  [9,0,2,7,8]
print "input : ",l
print "7 found : ",search(l, 3)
l = [284,287,289,293,295,298,0,3,8,9,10,11,12,15,17,19,20,22,26,29,30,31,35,36,37,38,42,43,45,50,51,54,56,58,59,60,62,63,68,70,73,74,81,83,84,87,92,95,99,101,102,105,108,109,112,114,115,116,122,125,126,127,129,132,134,136,137,138,139,147,149,152,153,154,155,159,160,161,163,164,165,166,168,169,171,172,174,176,177,180,187,188,190,191,192,198,200,203,204,206,207,209,210,212,214,216,221,224,227,228,229,230,233,235,237,241,242,243,244,246,248,252,253,255,257,259,260,261,262,265,266,268,269,270,271,272,273,277,279,281]
print "8 len :", len(l)
i = 0
s = ""
for n in l:
    s += str(n) + "\t"
    i += 1
    if i%5 == 0:
        s += "\n"
print s
print "8 found : ",search(l, 235)
#l =  [1,3,5]
#print "input : ",l
#print "8 found : ",search(l, 2)
