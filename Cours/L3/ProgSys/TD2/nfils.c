#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* j'affiche/j'attend
int main(int argc, char *argv[])
{
	int N=atoi(argv[1]);
	int pid;
	for(int i=0;i<N;i++){
		pid=fork();
		if(pid ==0){
		printf("mon numero de rang est le %d\n",i);	
		exit(0);
		}else{
		wait(NULL);	
		printf("j'ai listé tous mes fils\n");	
		
		}
		
	}
	
  return EXIT_SUCCESS;
}
*/

/*j'affiche tous/j'attends tous*/

int main(int argc, char *argv[])
{
	int N=atoi(argv[1]);
	int pid;
	for(int i=0;i<N;i++){
		pid=fork();
		if(pid ==0){
		printf("mon numero de rang est le %d\n",i);	
		exit(0);//si on quitte pas les fils relancent des forks!!
		}
	}
	for(int i=0;i<N;i++){
		wait(NULL);	
		printf("j'ai listé tous mes fils\n");	
		
		}
		
	return EXIT_SUCCESS;
}
