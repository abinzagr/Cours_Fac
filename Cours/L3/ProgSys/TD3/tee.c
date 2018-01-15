#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

	int fich=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);
	char c='i';
	while(read(0,&c,1)){
		write(fich,&c,1);
		write(1,&c,1);
	}
			
	return EXIT_SUCCESS;
	
	}
