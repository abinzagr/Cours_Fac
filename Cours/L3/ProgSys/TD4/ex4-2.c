#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void
termination_handler (int signum)
{
  printf("process kill\n");
 
}

int main(int argc, char *argv[])
{	
	struct sigaction action;
	action.sa_handler = termination_handler;
	sigemptyset (&(action.sa_mask));
	action.sa_flags = SA_RESETHAND;
    sigaction (SIGINT, &action, NULL);
	while(1);		
	return EXIT_SUCCESS;
	}
	
  

