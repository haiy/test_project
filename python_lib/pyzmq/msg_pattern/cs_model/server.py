import zmq
import time
import sys


build_host = lambda port : "tcp://127.0.0.1:%s" % port

def start_server(port):
    server_host = build_host(port)
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(server_host)
    while True:
        msg = socket.recv_string()
        print("Received msg : %s" % msg)
        time.sleep(1)
        socket.send_string("World from %s" % server_host)

if __name__ == '__main__':
    start_server(sys.argv[1])