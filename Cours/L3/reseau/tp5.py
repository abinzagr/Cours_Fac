#!/usr/bin/python3
# coding: utf-8

import socket,select,threading

socket = socket.socket(socket.AF_INET6,socket.SOCK_DGRAM)
socket.bind (('', 7777)) 

while True:
	data_byte,adress=socket.recvfrom(1500)
	socket.sendto(data_byte,adress)
	
