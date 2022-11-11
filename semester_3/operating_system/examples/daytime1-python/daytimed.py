#!/usr/bin/env python3.4

import socket, sys, getopt, time

def daytime():
    return time.strftime("%F %T\r\n")

def server(host, port):
    s = socket.socket(socket.AF_INET,
                      socket.SOCK_STREAM)  # create a TCP socket
    s.bind((host, port))                   # bind it to the server port
    s.listen(5)                            # allow up to 5 pending connections
    while 1:
        c, address = s.accept()            # connection c is a new socket
        msg = bytearray(daytime(),'utf-8') # obtain and convert local time
        c.send(msg)                        # send the message to the client
        c.close()                          # close socket

if (len(sys.argv) != 2):
    print("usage: daytimed port")
    sys.exit(1)
try:
    server('localhost', int(sys.argv[1]))
except:
    print(sys.exc_info()[1])

