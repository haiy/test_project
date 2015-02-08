#!/usr/bin/python
import bisect
S = [-1, 0, 1, 2, -1, -4]
def binsearch(a, x):
    'Locate the leftmost value exactly equal to x'
    i = bisect.bisect_left(a, x)
    if i != len(a) and a[i] == x:
        return i
    return -1

def sum3(l):
    l.sort()
    target = 0
    l_size = len(l)
    res = []
    for i in range(0, l_size - 3):
        for j in range(i+1, l_size - 2):
            left = target - l[i] - l[j]
            start = j+1
            idx = binsearch(l[start:], left)
            if idx != -1:
                res.append((l[i],l[j], l[start + idx]))
    return res
print sum3(S)

class Solution:
    # @return a list of lists of length 3, [[val1,val2,val3]]
    def threeSum(self, num):
        num_len  = len(num)
        if num_len < 3:
            return []
        num.sort()
        res = []
        #for i in range(0, num_len - 2):
        #    for j in range(i+1, num_len - 1):

        i = 0
        while i<num_len-2:
            j = i+1
            while j<num_len-1:
                #print i, j
                left_val = 0 - num[i] - num[j]
                start = j + 1
                idx = bisect.bisect_left(num[start:], left_val)
                if idx != num_len - start and num[start+idx] == left_val:
                    res.append([num[i],num[j],num[start+idx]])
                while j < num_len -1 and num[j+1] == num[j]:
                    j += 1
                j += 1
            while i < num_len -2 and num[i+1] == num[i]:
                i += 1
            i += 1
        return res

tmpS = Solution()
#S=[0,0,0]
print tmpS.threeSum(S)

