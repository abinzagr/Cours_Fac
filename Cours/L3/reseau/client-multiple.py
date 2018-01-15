#!/usr/bin/python3
# coding: utf-8

import socket,select,threading
sock = socket.socket(socket.AF_INET6,socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind (('', 7777)) 
sock.listen(1)

def clientthread(new_socket) :
	while True :
		data=new_socket.recv(1024)
		if not data: 
			new_socket.close()
			break
		new_socket.send(data)
while True :
	conn,addr =sock.accept()		
	threading.Thread(None,clientthread,None,(conn,)).start()
sock.close()       
