import zmq
import time
import sys

build_host = lambda port : "tcp://127.0.0.1:%s" % port

def start_sub(pub_port_lst):
    pub_servers = [build_host(p) for p in pub_port_lst]
    context = zmq.Context()
    socket = context.socket(zmq.SUB)
    for pub_serv in pub_servers:
        socket.connect(pub_serv)

    topic_filter = "1000"
    socket.setsockopt_string(zmq.SUBSCRIBE, topic_filter)

    for msg in range(5):
        msg = socket.recv_string()
        print(msg)

if __name__ == '__main__':
    start_sub(sys.argv[1].split(","))