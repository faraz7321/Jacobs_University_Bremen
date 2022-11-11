#!/usr/bin/env python3.4

import socket, select, sys, getopt, time

def daytime():
    return time.strftime("%F %T\r\n")

def server(host, port):
    sockets = []
    for res in socket.getaddrinfo(host, port, 
                                  socket.AF_UNSPEC, socket.SOCK_STREAM):
        af, socktype, proto, canonname, sa = res
        try:
            s = socket.socket(af, socktype, proto)
        except socket.error as msg:
            continue
        try:
            s.bind(sa)
            s.listen(5)                    # allow up to 5 pending connections
        except socket.error as msg:
            s.close()
            continue
        sockets.append(s)
    if len(sockets) == 0:
        raise socket.error("unable to open and bind socket")
    return sockets;

def process(sockets):
    while 1:
        r, w, e = select.select(sockets, [], [])
        for s in r:
            c, address = s.accept()        # connection c is a new socket
            msg = bytearray(daytime(),'utf-8') # obtain and convert local time
            c.send(msg)                    # send the message to the client
            c.close()                      # close socket

if (len(sys.argv) != 2):
    print("usage: daytimed port")
    sys.exit(1)
try:
    sockets = server("localhost", int(sys.argv[1]))
    process(sockets)
except:
    print(sys.exc_info()[1])
