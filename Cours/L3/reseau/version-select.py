#!/usr/bin/python3
# coding: utf-8

import socket,select,threading
sock = socket.socket(socket.AF_INET6,socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind (('', 7777)) 
sock.listen(1)
