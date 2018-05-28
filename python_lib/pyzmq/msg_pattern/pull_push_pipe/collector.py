import zmq
import sys

def collect_results(port):
    collector_host = "tcp://127.0.0.1:%s" % port
    ctx = zmq.Context()
    skt = ctx.socket(zmq.PULL)
    skt.bind(collector_host)

    while True:
        res_msg = skt.recv_json()
        print("receviced msg : ", res_msg)


if __name__ == '__main__':
    collect_results(sys.argv[1])
