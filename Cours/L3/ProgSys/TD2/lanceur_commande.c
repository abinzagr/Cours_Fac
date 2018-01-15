#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{ 		
	
	int pid;
		pid=fork();
		if(pid ==0){
		execvp(argv[1],argv+1); //argv+1 commence a prendre a partir de argv[2] 
		
		}else{
			wait(NULL);
			printf("le process de mon fils est achevé!!")	;
		
		}
		return EXIT_SUCCESS;
	}
	
  

