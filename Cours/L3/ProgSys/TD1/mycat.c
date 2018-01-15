#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#define N 3
/* lit et ecrit caractere par caractere */

/*int main(int argc,char *argv[])
{
	char c='i';
	int readok=1;int writeok=1;
	while(readok !=0){
		readok=read(0,&c,sizeof(char));
		writeok=write(1,&c,sizeof(char));		
		
		}
		
	return EXIT_SUCCESS;
	
	
}*/


/* lit et ecrit N caractere a la fois */

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
