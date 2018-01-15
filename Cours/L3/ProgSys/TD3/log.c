#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int tube[2];
	pipe(tube);
	int fich=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);
	int pid=fork();
	if(pid==0){
		close(tube[0]);
		dup2(tube[1],1);
		execvp(argv[2],argv+2);
		}
	else{
		dup2(1,tube[1]);
		char c='i';
		while(read(tube[0],&c,1)){
		write(fich,&c,1);
		write(1,&c,1);
		}
		
	}	
		
	close(tube[0]);		
	wait(NULL);
	return EXIT_SUCCESS;
	
	
	}
