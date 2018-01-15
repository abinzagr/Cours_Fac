#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


int main(int argc, char *argv[])
{ 		for(int i=1;i <=31;i++)
			printf("num_signal: %d\t signal: %s\n", i, strsignal(i));
		return EXIT_SUCCESS;
	}
	
  

