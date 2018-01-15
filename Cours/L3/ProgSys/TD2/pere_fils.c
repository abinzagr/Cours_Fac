
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int pid;
	pid=fork();
	if(pid !=0){
		wait(NULL);
		printf("je m'appelle %d et je suis le pere de %d\n",getpid(),pid);
	}
	else{
		printf("je m'appelle %d et je suis le fils de %d\n",getpid(),getppid());
		
		}
	
 
  return EXIT_SUCCESS;
}
