#!/usr/bin/python3
# coding: utf-8

import socket,select,threading

list_client = []
#message envoyé par un client
def broadcast_to_client(sock,message) :
	 if socket != server_socket :
            try:
                print(message)
                socket.send(message.encode('UTF-8'))
            except:
                sock.close()
                list_client.remove(sock)

		
#notif connexion client	aux autres clients	
def notif_connet_client(sock,message) :
 if socket != server_socket and socket != sock:
            try:
                print(message)
                socket.send(message.encode('UTF-8'))
            except:
                sock.close()
                list_client.remove(sock)

server_socket = socket.socket(socket.AF_INET6,socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind (('', 7777)) 
server_socket.listen(1)
list_client.append(server_socket)

while 1:
    try:
        
        read_sockets, write_sockets, error_sockets = select.select(list_client, [], [])
        for sock in read_sockets:
            if sock == server_socket:
                sockfd, addr = server_socket.accept()
                list_client.append(sockfd)
                print("Client (" + addr[0] + ", " + str(addr[1]) + ") connected")
                # On envoie la notif a tous les clients sauf à celui qui vient de se connecter
                #notif_connet_client(sockfd, "[" + addr[0] + ":" + str(addr[1]) + "] entered network\n")
 
            # Sinon c'est qu'un message à été reçu d'un client.
            else:
                try:
                    data = sock.recv(1024)
                        # Le message est envoyer à tous les clients et à celui qui l'a envoyé
                    broadcast_to_client(sock, data )
 
                except:
                    #La ligne suivante est utile pour savoir quelle erreur a été émise
                    # print("Unexpected error: " + sys.exc_info()[0])
                    broadcast_to_client(sock, "Client [" + addr[0] + ":" + str(addr[1]) + "] is offline")
                    print("Client [" + addr[0] + ":" + str(addr[1]) + "] is offline")
                    sock.close()
                    list_client.remove(sock)
                    continue
    except KeyboardInterrupt:
        print("Stop.\n")
        break
 
server_socket.close()
/**/

	
#define _GNU_SOURCE
#include <SDL/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>
//static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
#include "timer.h"
void* param=NULL;
// Return number of elapsed µsec since... a long time ago
static unsigned long get_time (void)
{
  struct timeval tv;

  gettimeofday (&tv ,NULL);

  // Only count seconds since beginning of 2016 (not jan 1st, 1970)
  tv.tv_sec -= 3600UL * 24 * 365 * 46;
  
  return tv.tv_sec * 1000000UL + tv.tv_usec;
}

/*timer values */
typedef struct echeancier {
	long t_initial;
	struct itimerval timer;
	void* parametre;
	bool arme;
	} echeancier;

echeancier tab_echeancier[100];

/*traitant alarm*/
void hand(int sig)
{
 printf("\nSignal %d recu\n", sig);
 long t_actuel = get_time();
 int i = 0;
 while((t_actuel - (tab_echeancier[i].t_initial + tab_echeancier[i].timer.it_value.tv_sec * 1000000UL + tab_echeancier[i].timer.it_value.tv_usec)) > 100 || tab_echeancier[i].arme == false) {
    i++;
  }
  sdl_push_event(tab_echeancier[i].parametre);
  printf("sdl_push_event(%p) appelée au temps %ld\n", tab_echeancier[i].parametre, get_time());
  tab_echeancier[i].arme = false;
}

/*Demon fonction threads */
void *Demon(void *p)
{
  printf("%p: bonjour ! ", pthread_self()); 
  struct sigaction action;
  action.sa_handler = hand;
  sigset_t my_set;
  sigfillset(&my_set);
  sigdelset(&my_set,SIGALRM);
  sigprocmask(SIG_BLOCK, &my_set,NULL);
  sigaction (SIGALRM, &action, NULL);
  while(1){
    sigsuspend(&(my_set));
  }		
}



#ifdef PADAWAN

// timer_init returns 1 if timers are fully implemented, 0 otherwise
int timer_init (void)
{
  for(int i = 0; i < 100; i++){
    //initialiser echeance[i]
    tab_echeancier[i].t_initial = 0;
    tab_echeancier[i].timer.it_interval.tv_sec = 0;
    tab_echeancier[i].timer.it_interval.tv_usec = 0;
    tab_echeancier[i].timer.it_value.tv_sec = 0;
    tab_echeancier[i].timer.it_value.tv_usec = 0;
    tab_echeancier[i].parametre = NULL;
    tab_echeancier[i].arme = false;
  }	
  pthread_t pid;
  printf("pid:%d\n",getpid());
  //struct sigaction action;
  //action.sa_handler = hand;
  sigset_t pere; 
  sigfillset(&pere);
  sigdelset(&pere,SIGALRM);
  sigprocmask(SIG_BLOCK, &pere,NULL);
  pthread_create(&pid,NULL,Demon,NULL);
  //sigaction(SIGALRM, &action, NULL);
  return 1; 
 
}

void timer_set (Uint32 delay, void *parametre)
{ long sec = delay / 1000;
  long usec = (delay - sec*1000) * 1000;	 
  int i = 0;
  while(tab_echeancier[i].arme != false)
  i++;
  tab_echeancier[i].parametre= param;
  tab_echeancier[i].timer.it_interval.tv_sec=0;
  tab_echeancier[i].timer.it_interval.tv_usec=0;
  tab_echeancier[i].timer.it_value.tv_sec=sec;
  tab_echeancier[i].timer.it_value.tv_usec=usec;
  tab_echeancier[i].parametre = param;
  tab_echeancier[i].arme = true;
  tab_echeancier[i].t_initial = get_time();
  setitimer(ITIMER_REAL, &(tab_echeancier[i].timer), NULL); 
}
	
#endif
