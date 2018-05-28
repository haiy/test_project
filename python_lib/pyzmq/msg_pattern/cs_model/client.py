import zmq
import time
import sys

build_host = lambda port : "tcp://127.0.0.1:%s" % port

def start_client(port_list):
    server_hosts = [ build_host(p) for p in port_lst]
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    for sh in server_hosts:
        socket.connect(sh)

    for req in range(1,10):
        req_msg = "Hello"
        socket.send_string(req_msg)
        msg = socket.recv_string()
        print("Receivce reply from server, req: %s, reply %s" % (req_msg, msg))

if __name__ == '__main__':
    port_lst = sys.argv[1].split(",")
    start_client(port_lst)
