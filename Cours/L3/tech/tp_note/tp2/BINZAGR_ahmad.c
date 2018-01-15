#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "tp2.h"
#include <math.h>

// fonction de comparaison (à completer ...) des abscisses de deux
// points A et B: renvoie -1 si "A<B", +1 si "A>B" et 0 sinon
int fcmp_x(point A, point B){
	if(A.x > B.x)
		return 1;
	else if (A.x < B.x)
		return -1;
	else
		return 0;
}


// fonction de comparaison (à completer ...) ordonnées de deux points
// A et B: renvoie -1 si "A<B", +1 si "A>B" et 0 sinon
int fcmp_y(point A, point B){ //const void*
  if(A.y > B.y)
		return 1;
	else if (A.y < B.y)
		return -1;
	else
		return 0;
}


// algorithme naïf en O(n^2)
// on suppose que P contient au moins n>=2 points
paire algo_naif(point *P, int n){
  paire resultat={{P[0].x,P[0].y},{P[1].x,P[1].y}};
  double val=0,dist_proche;
  /* trie tableau */
  qsort(P,n,sizeof(point),fcmp_x);
  /* double boucle recherche distance des deux points les plus proches*/
  dist_proche=dist(P[0],P[1]);
  for(int i=0;i<n;i++){
	for(int j=i+1;j<n;j++){
		val=dist(P[i],P[j]);
		if(val<dist_proche){
			dist_proche = val ;
			resultat.A.x =(P[i].x);
			resultat.A.y =(P[i].x);
			resultat.B.x =(P[j].x);
			resultat.B.y =(P[j].x);
		}
			
		}
  
	} 
 
  return resultat;
}


paire PPPP_rec(point *Px,point *Py,int n){
  /*si |Px| == 2 ou 3 */
  paire res={{Px[0].x,Px[0].y},{Px[1].x,Px[1].y}};
  if(n ==2 || n == 3){
	int val,dist_proche=dist(Px[0],Px[1]);
  for(int i=0;i<n;i++){
	for(int j=i+1;j<n;j++){
		val=dist(Px[i],Px[j]);
		if(val<dist_proche){
			dist_proche = val ;
			res.A.x =(P[i].x);
			res.A.y =(P[i].x);
			res.B.x =(P[j].x);
			res.B.y =(P[j].x);
		}
			
		}
  
	}
	//return dist_proche;
  }	
  /* extration du point median de px*/
  point pivot_x = Px[n/2];
  /*creation des tableaux Ax,Bx,Ay et By*/
  point *Ax = malloc(n/2 * sizeof(point));
  point *Bx = malloc(n/2 * sizeof(point));
  point *Ay = malloc(n/2 * sizeof(point));
  point *By = malloc(n/2 * sizeof(point));
  /* copie des n/2 premiers x*/
  for(int i=0;i<n/2;i++)
	Ax[i]=Px[i];
  /* copie des n/2 derniers x*/
  for(int j = n/2 + 1;j<n;j++)
	Bx[j]=Px[j];
  /* copie des n/2 premiers y*/
  for(int i=0;i<n/2;i++)
	Ay[i]=Py[i];
  /* copie des n/2 derniers x*/
  for(int j = n/2 + 1;j<n;j++)
	By[j]=Py[j];	
  
  /* calcule a,a' et b,b' */
	paire cal_a = PPPP_rec(Ax,Ay,n);
	paire cal_b = PPPP_rec(Bx,By,n);
  
  /* calcule min*/
	int dist_aa = dist(cal_a.A,cal_a.B);
	int dist_bb = dist(cal_b.A,cal_b.B);
	int min = 0;
	if(dist_aa < dist_bb)
		min = dist_aa;
	else 
		min = dist_bb;
  /* construction de Sy à partir de Py*/
  point *Sy = malloc(n * sizeof(point));
  for(int i=0;i<n;i++){
	  if(abs(pivot_x.x - Py[i].x)<min)
		Sy[i] = Py[i];
	  }		
  /* calcul min{dist(si,sj)} */	
	paire ss={{Sy[0].x,Sy[0].y},{Sy[1].x,Sy[1].y}};
	int tmp,min_sij = dist(Sy[0],Sy[1])
	for(int i=0;i<n;i++){
	for(int j=i+1;j<=7;j++){
		tmp=dist(Sy[i],Sy[j]);
		if(tmp<min_sij){
			min_sij = tmp;
			ss.A.x =(P[i].x);
			ss.A.y =(P[i].x);
			ss.B.x =(P[j].x);
			ss.B.y =(P[j].x);
		}
			
		}
  
	}
	
	/*revoie de la paire */
	//if() /* à finir */
	}


// algorithme récursif en O(nlogn)
// on suppose que P contient au moins n>=2 points
paire algo_rec(point *P, int n){
  paire resultat={{0,0},{0,0}};
  point *Px = malloc(n * sizeof(point));
  point *Py = malloc(n * sizeof(point));
  /* creation des deux tableaux*/
  memcpy(Px,P,n*sizeof(point));
  memcpy(Py,P,n*sizeof(point));
  /* trie selon x puis y*/
  qsort(Px,n,sizeof(point),fcmp_x);
  qsort(Py,n,sizeof(point),fcmp_y);
  paire PPPP_rec(Px,Py,n)
  
  
  return resultat;
}


int main(int argc, char *argv[]){
  
  srandom(time(NULL));

  if(argc==2){
    //
    // partie à ne pas modifier
    //
    if(!isdigit(argv[1][0])){ printf("Forgot \"naif\" or \"rec\"?.\n"); exit(1); }
    int n=atoi(argv[1]);
    point *P=point_random(n);
    if((P==NULL)||(n<1)){ printf("Empty point set.\n"); exit(1); }
    printf("%i\n",n);
    for(int i=0;i<n;i++)
      printf(FORM" "FORM"\n",P[i].x,P[i].y);
    return 0;
  }
    
  if(argc==3){
    //
    // partie à ne pas modifier
    //
    int n;
    paire res={{-1,0},{0,0}};
    point *P=read(argv[1],&n);
    if(!strcmp(argv[2],"naif")) res=algo_naif(P,n);
    if(!strcmp(argv[2],"rec")) res=algo_rec(P,n);
    if(res.A.x<0){ printf("Unknown algorithm.\n"); exit(1); }
    printf("point A: "FORM" "FORM"\n",res.A.x,res.A.y);
    printf("point B: "FORM" "FORM"\n",res.B.x,res.B.y);
    printf("distance: "FORM"\n",dist(res.A,res.B));
    return 0;
  }

  // pour vos tests personnels, si nécessaire, modifier le main()
  // seulement ci-dessous
  
  ;;;;
  ;;;;
  ;;;;
  
  return 0;
}
