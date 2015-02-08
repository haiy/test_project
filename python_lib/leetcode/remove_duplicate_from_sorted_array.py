#!/usr/bin/python
#Gven a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
#Do not allocate extra space for another array, you must do this in place with constant mem- ory.
#For example, Given input array A = [1,1,2],
#Your function should return length = 2, and A is now [1,2].

def remove (l):
    idx = 0
    for i in l[1:]:
        if i != l[idx]:
            idx += 1
            l[idx] = i
    return idx + 1
l=[1,2,2,3,4, 4]
print l[:remove(l)]
l=[1,1,2,3]
print l[:remove(l)]
