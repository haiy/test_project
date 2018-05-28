import zmq
import sys
import time

def produce_tasks(port):
    server = "tcp://127.0.0.1:%s" % port
    ctx = zmq.Context()
    skt = ctx.socket(zmq.PUSH)
    skt.bind(server)
    for i in range(10):
        skt.send_json({"numb":i})
        time.sleep(1)

if __name__ == '__main__':
    produce_tasks(sys.argv[1])
