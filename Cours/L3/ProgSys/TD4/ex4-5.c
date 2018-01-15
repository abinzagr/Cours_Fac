#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void hand_fils(int s)
{  	if(s==SIGUSR1)
		printf("\nacquittement %d recu\n"); 
}

void hand(int s)
{	printf("\nSignal %d recu\n", s);
	
}

int main(int argc, char *argv[])
{
	int pid;
	pid =fork();
	if(pid==0){
		struct sigaction actionant;
		actionant.sa_handler = hand_fils;
		sigset_t my_set, vide;
		sigemptyset( &my_set);
		//sigemptyset( &my_set);
		sigaddset(&my_set,SIGUSR1);
		sigprocmask(SIG_BLOCK, &my_set,NULL);
		sigaction (SIGUSR1, &actionant, NULL);
		for(int i=0;i<atoi(argv[1]);i++){
			for(int j=2;j <argc;j++){
			kill(getppid(),atoi(argv[j]));
			sigsuspend(&(my_set));
			//pause();
			}
		}
		kill(getppid(), SIGKILL);
	}
	struct sigaction action;
	action.sa_handler = hand;
	sigemptyset(&(action.sa_mask));
	while(1){
	for(int i=1;i < NSIG;i++){
		sigaction (i, &action, NULL);
		pause();
		kill(pid, SIGUSR1);
		}
	}
		return EXIT_SUCCESS;
	}
