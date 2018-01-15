#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{ 	
	int pid;
	
		pid=fork();
		if(pid ==0){
		execlp("/bin/sh","sh","-c",argv[1]);
		
		}else{
			wait(NULL);
			printf("le process de mon fils est achevé!!")	;
		
		}
		return EXIT_SUCCESS;
	}
	
  

