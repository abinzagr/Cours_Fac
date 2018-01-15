#include <stdlib.h>
#include "heap.h"

heap heap_create(int n, int (*f)(const void *, const void *)){
	/*if(n>0)*/
	heap tas = malloc(sizeof(*tas));
	tas->nmax = n;
	tas->size = 0;
	tas->f = f;
	tas->array = malloc(sizeof(void*)*(n+1));
	return tas;
}

void heap_destroy(heap h){
	free(h->array);
	free(h);	

}


int heap_empty(heap h){
	if(h->size == 0)
		return 1;
		
	return 0;
}





int heap_add(heap h, void *object){
	if(h->size == h->nmax)
		return 1;
	else{
		h->size++;
		h->array[h->size] = object;
		int i=h->size;
		while(i !=1 && h->f(h->array[i/2],object)>0){
			void* tmp = h->array[i/2];
			h->array[i/2] = object;
			h->array[i] = tmp;
			i = i/2;
			
		}
		return 0;
	}
}




void *heap_top(heap h){
	if(heap_empty(h) != 0)
		return h->array[1] ;	
	
	return NULL;
}


void *heap_pop(heap h){
  int i=1;
  void* racine=h->array[1];
  h->array[1]=h->array[h->size];
  h->size --;
  int min = i;
  while(1){
	  if(2*i <= h->size && h->f(h->array[i], h->array[2*i])>0)
	  min = 2*i;
	  if( ((2*i)+1) <= h->size && h->f(h->array[min], h->array[(2*i)+1])>0)
	  min = (2*i +1);
	  if( i== min)
	  break;
	  void* tmp = h->array[i];
			h->array[i] = h->array[min];
			h->array[min] = tmp;
	  i=min;
	  }
  return racine;

}
