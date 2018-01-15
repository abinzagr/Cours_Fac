#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct {
		int tube[2];
	} t_pipe;

void processus(int n, t_pipe tabPipe[3],int tmp){
	char c='i';
    for (int i=0; i < 3; i++){
         if ((i + 1) != n){
			  tmp=dup(tabPipe[i].tube[0]);
		  }
         if (i != n){
			  while(read(tmp,&c,1)){
				  write(tabPipe[i].tube[1],&c,1);}
			  if(i !=2){  
			  close(tabPipe[i].tube[0]);
              close(tabPipe[i].tube[1]);
			  }
        }
    }
}

int main(int argc, char *argv[]){
	t_pipe tab_pipe[3];
	int tmp=0;char c='i';
	for(int i=0;i<3;i++){
		pipe(tab_pipe[i].tube);
		}
		write(tab_pipe[0].tube[1],"bonjour",7);
		close(tab_pipe[0].tube[1]);
		//close(tab_pipe[0].tube[1]);
	for(int j=0;j<3;j++){
		if(fork()==0){
				processus(j,tab_pipe,tmp);
			}	
		}
	while(read(tab_pipe[0].tube[0],&c,1)) //dernier doit l'afficher!
		write(1,&c,1);	
	close(tab_pipe[0].tube[0]);
		wait(NULL);
		wait(NULL);
		wait(NULL);
	return EXIT_SUCCESS;
	//p=a=b=c
	
	}

/*Avec chaque processus "p" qui écrit sur son tube "p" et qui va lire le tube "p - 1" ce qui donne
- le père (processus 0) écrit sur le tube [0]
- le fils 1 lit le tube[0] et écrit sur le [1]
- le fils 2 lit le tube[1] et écrit sur le [2]
- le fils 3 lit le tube[2] et écrit sur l'écran
Bien sûr, chaque tube[n] possède lui-même un cote[0] et un cote[1]. Je serais d'ailleurs d'avis de créer le type "pipe" ce qui te permettrait de pas te mélanger les pinceaux entre "tableau de pipes" et "tableau des cotés"*/
