#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void hand(int s)
{	printf("\nSignal %d recu\n", s);
	
}


int main(int argc, char *argv[])
{	
	int pid;
	pid =fork();
	if(pid==0){
		struct sigaction actionant;
	
	

return EXIT_SUCCESS;
}
