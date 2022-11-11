#!/usr/bin/env python3.4

import socket, sys, getopt

def client(host, port):
    s = None
    for res in socket.getaddrinfo(host, port, 
                                  socket.AF_UNSPEC, socket.SOCK_STREAM):
        af, socktype, proto, canonname, sa = res
        try:
            s = socket.socket(af, socktype, proto)
        except socket.error as msg:
            s = None
            continue
        try:
            s.connect(sa)
        except socket.error as msg:
            s.close()
            s = None
            continue
        break
    if s is None:
        raise socket.error("unable to open and connect socket")
    r = s.makefile()                    # turn socket into file object
    print(r.read(), end = '')           # print the time from the server
    r.close()                           # close the file object and
    s.close()                           # close the socket object

if (len(sys.argv) != 3):
    print("usage: daytime host port")
    sys.exit(1)
try:
    client(sys.argv[1], int(sys.argv[2]))
except:
    print(sys.exc_info()[1])
