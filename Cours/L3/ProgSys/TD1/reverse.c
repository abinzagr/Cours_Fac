#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{	
	int c=1;
	int input_file=open(argv[1],O_RDONLY,0666);
	int output_file=open(argv[2],O_WRONLY,0666);
	int readok=1;int writeok=1;
	int taille=lseek(input_file,0,SEEK_END);
	if(taille==-1){
		printf("erreur positionnement du curseur");
		return EXIT_FAILURE;
		}
	else{
		for(int i=taille-1;i>=0;i--){
			/*printf("%d\n",*/lseek(input_file,i,SEEK_SET); 
			/*printf("%d\n",*/read(input_file,&c,sizeof(char));
			write(output_file,&c,sizeof(char));
		}
		close(output_file);
		close(input_file);	
	}
	return EXIT_SUCCESS;

}
