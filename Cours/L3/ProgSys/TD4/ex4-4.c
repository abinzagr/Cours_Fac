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
	if(argc < 4) {
		fprintf(stderr, "Usage: nombre d'argument incomplet\n");
		exit(1);
	}
	for(int i=0;i<atoi(argv[2]);i++){
		
		for(int j=3;j <argc;j++){
			kill(atoi(argv[1]),atoi(argv[j]));
			sleep(1);
		}
	}
		return EXIT_SUCCESS;
	}
	
  
