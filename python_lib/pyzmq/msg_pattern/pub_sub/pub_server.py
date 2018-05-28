import zmq
import time
import sys
import random

build_host = lambda port : "tcp://127.0.0.1:%s" % port

def start_pub_server(port):
    server_host = build_host(port)
    context = zmq.Context()
    socket = context.socket(zmq.PUB)
    socket.bind(server_host)

    while True:
        print("server started at : %s" % server_host)
        topic = random.randrange(1000, 1001)
        socket.send_string("%d %s" % (topic, "server from" + server_host))
        time.sleep(1)

if __name__ == '__main__':
    start_pub_server(sys.argv[1])


