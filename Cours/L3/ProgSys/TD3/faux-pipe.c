#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{	int pid1,pid2;
	int fich=open("file.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
	pid1=fork();
		if(pid1 ==0){
		dup2(fich,1);
		execlp(argv[1],argv[1],NULL);
		
	}
	else{
		wait(NULL);
		//printf("le process1 achevé!!")	;
		
	}
	close(fich);
	int fich1=open("file.txt",O_RDONLY,0666);
	pid2=fork();
		if(pid2 ==0){
		dup2(fich1,0);
		execvp(argv[2],argv+2);
		
	}
	else{
		wait(NULL);
		//printf("le process2 achevé!!")	;
		
	}
	close(fich1);	
 

  return EXIT_SUCCESS;
}
  
