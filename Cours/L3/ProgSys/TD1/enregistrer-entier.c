#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{	int position=atoi(argv[2]);
	unsigned int valeur=atoi(argv[3]);
	int c=1;
	int fichier=open(argv[1],O_RDONLY|O_WRONLY,0666);
	int readok=1;int writeok=1;
	lseek(fichier,position,SEEK_SET);
	writeok=write(fichier,&valeur,sizeof(int));
	close(fichier);	
	return EXIT_SUCCESS;

}
