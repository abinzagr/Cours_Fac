#include "Shell.h"
#include "Evaluation.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
void
verifier(int cond, char *s)
{
  if (!cond)
    {
      perror(s);
      exit(1);
    }
}

void execute_simple(Expression *e)
{
	int pid;
		pid=fork();
		if(pid ==0){
		execvp(e->arguments[0],e->arguments);
		
	}
	else{
		wait(NULL);
		printf("le process de mon fils est achevé!!")	;
		
	}
	
}
void execute_out(Expression *e){	
  int fich=open(e->arguments[0],O_WRONLY|O_CREAT,0666);
  int tmp=dup(1);
  dup2(fich,1);
  execute_simple(e->gauche);
  dup2(tmp,1);
  close(fich);	
	
	}

int
evaluer_expr(Expression *e)
{   
	
	if(e==NULL)
	return -1;
	
	if(e->type==VIDE)
	return 0;
	
	if(e->type==SIMPLE)
	execute_simple(e);
	
	if(e->type==BG){
		execute_simple(e);
		;	
		}
	if(e->type==REDIRECTION_O)
	execute_out(e);
	
	
/*	switch(e->type){

  case VIDE :
    
    break ;
    
  case SIMPLE :
    execute_simple(e);
    break;

  case REDIRECTION_O: 
  execute_out(e);
  break;
  case REDIRECTION_I: 	
  case REDIRECTION_A: 	
  case REDIRECTION_E: 	
  case REDIRECTION_EO :
    
    break;
  case BG:
   
    break;
  default :
 break;
  }*/
	
	
	
	
	
  return 1;
}
