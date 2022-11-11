#!/usr/bin/env python3.4

import socket, sys, getopt

def client(host, port):
    s = socket.socket(socket.AF_INET,
                      socket.SOCK_STREAM)  # create a TCP socket
    s.connect((host, port))                # connect to server on the port
    r = s.makefile()                       # turn socket into file object
    print(r.read(), end='')                # print the time from the server
    r.close()                              # close the file object and
    s.close()                              # close the socket object

if (len(sys.argv) != 3):
    print("usage: daytime host port")
    sys.exit(1)
try:
    client(sys.argv[1], int(sys.argv[2]))
except:
    print(sys.exc_info()[1])
