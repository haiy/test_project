import socket
import sys

def socket_test():
    s = socket.socket(AF_INET,SOCK_STREAM)
    host = 'localhost'
    local_ip = socket.gethostbyname( host )
    print "Local host ip address is :" + local_ip

    host = local_ip
    port = 5525

    try :
        s.bind( (host, port) )
    except Exception err:
        print "Bind error " + err

    s.listen( 10 )
