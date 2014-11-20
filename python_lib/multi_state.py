#!/usr/bin/python
# -*- coding=utf8 -*- 

def print_1(*numb):
    flag = len(numb)

    if flag == 1:
        print numb
        return
    if flag == 2:
        i = 0
        while i < numb[1]:
            print numb[0]
            i += 1
        return 

def main():
    print "I am the main\n"
    print "test 1"
    print_1(4)
    print "test 2"
    print_1(2,3)

if __name__ == '__main__':
    main()
