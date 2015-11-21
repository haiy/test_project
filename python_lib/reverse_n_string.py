#!/usr/bin/python
#part string reverse
def reverse_func(begin, end, s):
    mid = (begin + end)/2
    i = 0
    list_s = list(s)
    while((begin + i) < mid):
        raw = list_s[begin + i]
        list_s[begin + i] = list_s[end - i -1]
        list_s[end - i - 1] = raw
        i += 1
    print list_s
    return "".join(list_s)

def reverse_main(i, s):
    n = 8
    s = reverse_func(0, i, s)
    s = reverse_func(i, n, s)
    s = reverse_func(0, n, s)
    return s

print "Raw String: abcdefgh"
res = reverse_main(3, 'abcdefgh')
print res
