#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{	int c=1;
	int fichier=open("test.txt",O_RDONLY,0666);
	int readok=1;int writeok=1;
	while(readok !=0){
		readok=read(fichier,&c,sizeof(int));
		writeok=write(1,&c,sizeof(int));
	}
	close(fichier);	
	return EXIT_SUCCESS;

}
