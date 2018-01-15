#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#define N 3





int main(int argc,char *argv[])
{	
	char *c=NULL;
	c= malloc(sizeof(char)*N);
	int nbread=1;int nbwrite=1;
	while(nbread !=0){
		nbread=fread(c,N*sizeof(char),1,stdin);
		nbwrite=fwrite(c,N*sizeof(char),1,stdout);		
		
		}
	free(c);	
	return EXIT_SUCCESS;

}
