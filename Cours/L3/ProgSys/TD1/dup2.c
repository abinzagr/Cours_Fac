#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <unistd.h>


int main(int argc,char *argv[])
{	
	char *c=NULL;
	c= malloc(sizeof(char)*N);
	int readok=1;int writeok=1;
	while(readok !=0){
		readok=read(0,&c,sizeof(char));
		writeok=write(1,&c,sizeof(char));		
		
		}
		
	return EXIT_SUCCESS;

}
