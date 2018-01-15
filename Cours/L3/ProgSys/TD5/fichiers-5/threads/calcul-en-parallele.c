#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX  10000000
double resultat[MAX];
int nb_threads;

void *calculcycle(void *p)
{   
	int c =(int)p; //2em solution int *c=(int*)p 
    for(int k=c; k < MAX; k+=nb_threads){
	resultat[k] = atan((double)k); 
  } 
  return NULL;
}

void *calculblock(void *p){
	int c =(int)p;
	int block=MAX/nb_threads;
	for(int k=c*block; k <(c*block)+block; k++){
		resultat[k] = atan((double)k); 
	} 
	return NULL;
	
	}


int 
main(int argc, char *argv[])
{ nb_threads = atoi(argv[1]);
  pthread_t pid[nb_threads];
  //int tab[n];2em solution en cas de plusieurs threads  
  for(int i=0;i<nb_threads;i++){
	pthread_create(&pid[i],NULL,calculcycle,(void*)i); /*2em solution on passe &tab[i]*/
  }
  for(int i=0;i<nb_threads;i++){
	pthread_join(pid[i],NULL);
    
  }
  return EXIT_SUCCESS;
}
