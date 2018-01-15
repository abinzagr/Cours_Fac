#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void hand(int s)
{  
  printf("\nSignal %d recu\n", s);
}

int main(int argc, char *argv[])
{	
	printf("pid:%d\n",getpid());
	struct sigaction action;
	action.sa_handler = hand;
	for(int i=1;i < NSIG;i++){
		sigaction (i, &action, NULL);
		}
	while(1);	
		return EXIT_SUCCESS;
	}
	
  

