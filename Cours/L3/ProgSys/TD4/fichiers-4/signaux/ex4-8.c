#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>


sigjmp_buf env;

void f(int r){
	longjmp(env,r);
	}
	
void hand(int s)
{  	
	printf("\nSignal %d recu\n", s);
}	
	
	
int executer_avant_delai(void (*fun)(void*),void *parametre,int delai_en_seconde){
	int r;
	struct sigaction act;
	act.sa_handler = hand;
	sigemptyset(&(act.sa_mask));
	act.sa_flags = 0;
    sigaction (SIGALRM, &act, NULL);
	alarm(delai_en_seconde);
	r=sigsetjmp(env,1);
	if(r==0){
	fun(parametre);
    }
    else{
			siglongjmp(env,r);
		}
	



}	
	

