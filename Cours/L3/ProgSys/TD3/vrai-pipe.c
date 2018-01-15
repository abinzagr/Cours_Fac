#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int tube[2];
	pipe(tube);
	int pid=fork();
	if(pid==0){
		close(tube[0]);
		dup2(tube[1],1); //on lie l'entree du tube a la sortie standard
		execlp(argv[1],argv[1],NULL);
		}
	int pidf=fork();
	if(pidf==0){
		close(tube[1]);
		dup2(tube[0],0); //on lie la sortie du tube a l'entree standard
		execvp(argv[2],argv+2);
		}
	close(tube[0]);	
	close(tube[1]);	
	wait(NULL);
	wait(NULL);			
	
	return EXIT_SUCCESS;
	
	
	}
