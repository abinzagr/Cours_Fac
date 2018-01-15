#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/*int generer-entier()*/




int main(int argc,char *argv[])
{	
	unsigned int n =atoi(argv[1]);
	int fichier=open("test.txt",O_WRONLY|O_CREAT,0666);
		for(int i=0;i<n-1;i++)
				write(fichier,&i,sizeof(int));
		
	close(fichier);	
	return EXIT_SUCCESS;

}
