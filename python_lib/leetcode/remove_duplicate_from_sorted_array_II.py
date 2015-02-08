#!/usr/bin/python
#Follow up for "Remove Duplicates":
#What if duplicates are allowed at most twice?
#For example,
#Given sorted array A = [1,1,1,2,2,3],
#Your function should return length = 5, and A is now [1,1,2,2,3].
A = [1,1,1,2,2,3]
#A = [1,1]
#A = [1,2,3,4]

def remove(l):
    idx = 0
    ct = 1
    for i in l[1:]:
        if l[idx] == i:
            ct += 1
            if ct < 3:
                idx += 1
                l[idx] = i
        else:
            ct = 1
            idx += 1
            l[idx] = i
    return idx + 1


print A[:remove(A)]
print A

