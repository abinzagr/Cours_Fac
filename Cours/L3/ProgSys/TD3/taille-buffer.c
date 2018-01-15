#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	int tube[2];
	pipe(tube);
	int pid=fork();
	int i=0;
	if(pid==0){
		while(1){
			i++;
			write(tube[1],"a",1);
			printf("printf: %d\n",i);
			
			}
			close(tube[0]);	
			close(tube[1]);	
		}
		close(tube[0]);	
		close(tube[1]);	
	wait(NULL);		
	

	
	return EXIT_SUCCESS;
	
	
	}
