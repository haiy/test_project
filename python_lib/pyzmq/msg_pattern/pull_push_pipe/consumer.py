import zmq
import random
import sys

def start_consumers(producer_port, collector_port):
    pro_host = "tcp://127.0.0.1:%s"  % producer_port
    col_host = "tcp://127.0.0.1:%s"  % collector_port
    ctx = zmq.Context()

    consumer_receiver = ctx.socket(zmq.PULL)
    consumer_receiver.connect(pro_host)

    consumer_sender = ctx.socket(zmq.PUSH)
    consumer_sender.connect(col_host)

    consumer_id = random.randrange(1,10005)


    while True:
        msg = consumer_receiver.recv_json()
        print(consumer_id, " received msg : ", msg, int(msg["numb"]))
        res = int(msg["numb"]) * int(msg["numb"])
        print(consumer_id, "  calculated result: ", res)
        consumer_sender.send_json({"consumer":consumer_id,"input": msg["numb"], "output":res})


if __name__ == '__main__':
    start_consumers(sys.argv[1], sys.argv[2])


