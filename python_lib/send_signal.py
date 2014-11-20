#!/usr/bin/python
# -*- coding=utf8 -*-

import socket
import sys

def send_update_signal():
    snd_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = '192.168.3.17'
    port = 5525

    try :
        snd_sock.bind( (host,port) )
    except Exception,e:
        print "Socket bind error :",e

    while True:
        print "Waiting for input connection..."
        snd_sock.listen(10)
        con, addr = snd_sock.accept()
        print "Receive connection from :",addr

        while True:
            data = con.recv(1024)
            print "Received data :",data
            ans = rawiput("Your reply is : [OK] ?")
            con.send( ans )

    

if __name__ == '__main__':
    send_update_signal()


