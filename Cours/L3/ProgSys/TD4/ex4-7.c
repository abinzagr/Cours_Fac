#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

jmp_buf env;

/*impossible à ne pas faire sinon on perds notre pointeur sur notre point de sauvegarde initial un longjmp se fait d'une fonction fille vers notre pont de fixation!!
int g(){
	setjmp(env);
	}*/

void f(int r){
	longjmp(env,r);
	}
	
int main(int argc, char *argv[])
{	volatile int i=0;int r;
	r=setjmp(env);
	printf("%d\n",i);
	i++;
	if(i<10)
	f(r);
		return EXIT_SUCCESS;

}	

