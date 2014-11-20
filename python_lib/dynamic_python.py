#/usr/bin/python

import time
import os
import subprocess

def read_con():
    echo_test = subprocess.Popen(['/usr/bin/bash','echo_con.sh'])
    return echo_test

if __name__ == '__main__':
    while True:
        read_con()

        stat = raw_input("stat : ")

        if stat == 'q':
            break
        if stat == 'e':
            read_con()
            print 'Sleeping....'
            time.sleep(6)
            print 'Awaking...'

