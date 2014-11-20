#!/usr/bin/python
#-*- coding:utf8 -*-

import socket
import sys

def simple_con_remote_host():
    try:
        s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
        print "Socket created successed!"
    except Exception, msg:
        print "Socket creation failed!",msg

    host = "www.goolge.com"
    port = 8044 
#host = "localhost"

    try :
        remote_ip = socket.gethostbyname( host )
    except socket.gaierror:
        print "Could not reslove the host name"
        sys.exit()
    print "Ip addr of remote host:%s is %s "%( host, remote_ip )

    s.connect( (remote_ip, port) )
    message = 'GET /HTTP/1.1\r\n\r\n'

    try:
        s.sendall( message )
    except socket.error:
        print "Send failed!"
        sys.exit()

    reply = s.recv()
    s.close
    print reply

def socket_bind_test():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = 'localhost'
    port = 5525

    remote_ip = socket.gethostbyname( host )

    try :
        s.bind( (remote_ip, port) )
    except socket.error, msg:
        print 'Bind failed! Error code: ',msg
        sys.exit()

    #Begin to listen on the port
    print 'Listening on port :'+ str(port)
    s.listen( 10 )

    #wait for the connection
    con, addr = s.accept()

    print "Connection established with " + str(addr[0]) + ':' + str(addr[1])

    data = con.recv( 1024 )
    print "Received : " + str( data )
    msg_snd = " You have said " + str( data )
    
    con.sendall( msg_snd )

    con.close()
    s.close

if __name__ == '__main__':
    socket_bind_test()

