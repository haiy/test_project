#!/usr/bin/python
# -*- coding=utf8 -*-
import socket
import sys

def send_signal():
    host = '192.168.1.2'
    port = 5525

    snd_sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    try:
        snd_sock.connect((host,port))
    except Exception,e:
        print "Socket connect error :",e
        sys.exit(1)

    while True:
        msg = raw_input("Send what? :")
        snd_sock.send( msg )
        res = snd_sock.recv(1024)
        print "Received :",res
        if res == 'OK':
            msg = 'kill u!'
            break

if __name__ == '__main__':
    send_signal()
