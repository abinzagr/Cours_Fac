//
//  TSP - APPROXIMATION / HEURISTIQUES
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "variables.h"
#include "utils.h"
#include "misc.c"

static void drawTour(point *V, int n, int *P){

  // saute le dessin si le précédent a été fait il y a moins de 20ms
  static unsigned int last_tick = 0;
  if(n<0) { last_tick = 0; n=-n; }  // force le dessin si n<0
  if(last_tick + 20 > SDL_GetTicks()) return;
  last_tick = SDL_GetTicks();

  // gestion de la file d'event
  handleEvent(false);

  // efface la fenêtre
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  // dessine le cycle
  if(P && V){
    selectColor(1,1,1); // couleur blanche
    for (int i = 0 ; i < n ; i++)
      drawLine(V[P[i]], V[P[(i+1) % n]]);
  }
  // dessine les points
  if(V){
    selectColor(1,0,0); // couleur rouge
    for (int i = 0 ; i < n ; i++)
      drawPoint(V[i]);
  }

  // affiche le dessin
  SDL_GL_SwapWindow(window);
}

// Génère n points aléatoires du rectangle entier [0,X] × [0,Y] et
// renvoie le tableau des n points ainsi générés et met à jour la
// variable globale vertices[].
static point* generatePoints(int n, int X, int Y) {
  vertices = malloc(n * sizeof(point));
  const double rx = (double) X / RAND_MAX;
  const double ry = (double) Y / RAND_MAX;
  for (int i = 0 ; i < n ; i++){
    vertices[i].x = random() * rx;
    vertices[i].y = random() * ry;
  }
  return vertices;
}

// Ajoute p points au tableau V qui en comporte déjà n. Les p nouveaux
// points sont placés aléatoirement sur le cercle de centre c et de
// rayon r et insérés aléatoirement parmi les p points déjà présents
// de V. Le tableau V doit être de longueur au moins n+p.
static void generateCircle(point V[], int n, int p, point c, double r){
  const double K=2.0*M_PI/RAND_MAX;
  double a;
  int i;
  for(i=0; i<p; i++){ // p point sur le cercle
    a=K*random();
    V[n+i].x = c.x + r*cos(a);
    V[n+i].y = c.y + r*sin(a);
  }
  Permute(V,n+p); // permute aléatoirement tous les points de V
}

static double dist(point A, point B){
double x= pow( (A.x - B.x), 2);
	double y=pow( (A.y - B.y), 2);
	return sqrt(x+y);
}

static double value(point *V, int n, int *P){
  double val=0;
	for(int i=0;i<n;i++)
	val+=dist(V[P[i]],V[P[i+1]%n]);
	return val;
}

/* =============== TSP FLIP ================ */
void reverse(int *T, int p, int q){
  // renverse la partie T[p]...T[q] du tableau T avec p<q
  // si T={0,1,2,3,4,5,6} et p=2 et q=4, alors le nouveau
  // tableau sera {0,1, 4,3,2, 5,6}
  int tmp=0;
  while(p<q){
	  tmp = T[p];
	  T[p] = T[q];
	  T[q] = tmp;
	  p++;
	  q--;
	  }
}

double first_flip(point *V, int n, int *P){
 double di,dij,dr;
 for(int i=0;i<n-2;i++){
	di=dist(V[P[i]],V[P[i+1]]);
	for(int j=i+2;j<n;j++){
		dij=di + dist(V[P[j]],V[P[(j+1)%n]]);
		dr = dist(V[P[i]],V[P[j]]) + dist(V[P[i+1]],V[P[(j+1)%n]]);
		if(dr<dij){
			reverse(P,i+1,j);
			return (dij-dr);
		}
		
	}
	
 }
	return 0; 
}


static double tsp_flip(point *V, int n, int *P){
  // la fonction doit renvoyer la valeur de la tournée obtenu
  // suppose une tournée valide P en entrée
  // pensez à faire drawTour() pour visualiser chaque flips
  
  while(first_flip(V,n,P)){
	  drawTour(V,n,P);
	  
	  }
  return value(V,n,P);
  
  
}

/* =============== TSP GREEDY ================ */
static double tsp_greedy(point *V, int n, int *P){
  int tmp;
  double min = DBL_MAX, dij;
  
  for(int i=0 ; i<n-1 ; i++){
    for(int j=i+1 ; j<n ; j++){
      dij = dist(V[P[i]], V[P[(i+1)%n]]);
      if((min = dist(V[P[i]], V[P[j]])) < dij){
    tmp = P[i+1];
    P[i+1] = P[j];
    P[j] = tmp;
    drawTour(V, n, P);
      }
    }
  } 
  return value(V,n,P);
}

// taille initiale de la fenêtre
int width = 640;
int height = 480;

// pour la fenêtre graphique
bool running = true;
bool mouse_down = false;
double scale = 1;

/* ==== Approximation MST ====*/

// -> Ã  insÃ©rer avant main() dans tsp_approx.c
// -> complÃ©ter tsp_mst() en fin de fichier

// vous pourrez changer la boucle principale Ã  la fin du main() par
// quelque chose comme ceci:
//
// bool has_changed = true;
// graph M = createGraph(n);
// ;;;
// while(running){
//  wait_event = true;
//  if (has_changed) tsp_mst(V,n,P,M);
//  if (flipFirst(V,n,P)) wait_event = false;
//  drawGraph(V,n,P,M);
//  has_changed = handleEvent(wait_event);
// }
// freeGraph(M);


typedef struct{ // un graphe
  int n;        // n=nombre de sommets
  int *deg;     // deg[u]=nombre de voisins du sommets u
  int **list;   // list[u][i]=i-Ã¨me voisin de u
} graph;


// CrÃ©e un graphe Ã  n sommets avec des listes de tailles n.
// Attention !  G.deg[u] n'est pas initialisÃ©
graph createGraph(int n){
  graph G;
  G.n = n;
  G.deg = malloc(n*sizeof(int));
  G.list = malloc(n*sizeof(int*));
  for (int u=0; u<n; u++)
    G.list[u] = malloc(n*sizeof(int)); // taille n par dÃ©faut
  return G;
}


// LibÃ¨re les listes de G
void freeGraph(graph G){
  for(int u=0; u<G.n; u++) free(G.list[u]);
  free(G.list);
  free(G.deg);
}


// Ajoute l'arÃªte u-v au graphe G de maniÃ¨re symÃ©trique
void addEdge(graph G, int u, int v){
  G.list[u][G.deg[u]++] = v;
  G.list[v][G.deg[v]++] = u;
}


// Dessine le graphe G, les points V et la tournÃ©e dÃ©finie par Q
static void drawGraph(point *V, int n, int *Q, graph G) {

  // Saute le dessin si le prÃ©cÃ©dent a Ã©tÃ© fait il y a moins de 20ms
  static unsigned int last_tick = 0;
  if (last_tick + 20 > SDL_GetTicks()) return;
  last_tick = SDL_GetTicks();


  // Gestion de la file d'event// 
  handleEvent(false);

  // Efface la fenÃªtre
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  // Dessin
  glLineWidth(3.0);
  selectColor(0,0.4,0);
  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < G.deg[i] ; j++)
      if(i < G.list[i][j])
	drawLine(V[i], V[G.list[i][j]]);
  glLineWidth(1.0);
  selectColor(1,1,1);
  for(int i = 0 ; i < n ; i++)
    drawLine(V[Q[i]], V[Q[(i+1) % n]]);

  // Rouge
  selectColor(1,0,0);
  for(int i = 0 ; i < n ; i++) drawPoint(V[i]);

  // Affiche le dessin
  SDL_GL_SwapWindow(window);
}


typedef struct{  // une arÃªte u-v avec un poids
  int u,v;       // extrÃ©mitÃ©s de l'arÃªte u-v
  double weight; // poids de l'arÃªte u-v
} edge;


// Comparaison du poids de deux arÃªtes pour qsort()
int compEdge(const void *p1, const void *p2){
  const edge *e1 = p1;
  const edge *e2 = p2;
  return (int)(e1->weight - e2->weight);
}


// Fusionne les arbres de racines x et y// 
// (avec l'heuristique basÃ©e sur la hauteur)
void Union(int x, int y, int *parent, int *height){
  if(height[x]>height[y]) parent[y]=x;
  else{
    parent[x]=y;
    if(height[x]==height[y]) height[y]++;
  }
}


// Renvoie la racine de l'arbre de x
// (avec l'heuristique de la compression de chemin)
int Find(int x, int *parent){
  if(x!=parent[x]) parent[x]=Find(parent[x],parent);
  return parent[x];
}


// Calcule dans le tableau Q l'ordre de premiÃ¨re visite des sommets du
// graphe G selon un parcours de profondeur d'abord Ã  partir du sommet
// u. Le paramÃ¨tre p est le sommet parent de u. On doit avoir p<0 si u
// est l'origine du parcours (premier appel).

void dfs(graph G, int u, int *Q, int p) {
  static int t; // t = temps ou indice (variable globale) du tableau Q
  if(p<0) t=0;
  Q[t++] = u;
  for(int i=0; i<G.deg[u]; i++)
    if(G.list[u][i] != p) dfs(G, G.list[u][i], Q, u);
}


// Cette fonction (Ã  complÃ©ter) doit calculer deux choses (Ã  partir de
// V et n):
//
// 1. Le graphe T, soit l'arbre couvrant V de poids minimum
// 2. La tournÃ©e Q, soit l'ordre de visite selon le DFS de T
//
// NB: Q et T doivent crÃ©es et libÃ©rÃ©s par l'appelant

double tsp_mst(point *V, int n, int *Q, graph T) {
  // Algorithme:
  // 1. remplir puis trier le tableau d'arÃªtes
  // 2. rÃ©pÃ©ter pour chaque arÃªte u-v, mais pas plus de n-1 fois:
  //    si u-v ne forme pas un cycle dans T (<=> u,v dans des composantes diffÃ©rentes)
  //    alors ajouter u-v Ã  T
  // 3. calculer dans Q le DFS de T

  // E = tableau de toutes les arÃªtes dÃ©finies Ã  partir des n points de V
  edge *E = malloc(n*(n-1)/2*sizeof(edge));
  int k=0;
  for(int i=0;i<n-1;i++){
	  for(int j=i+1;j<n;j++){
		  E[k].u=i;
		  E[k].v=j;
		  E[k].weight=dist(V[i],V[j]);
		  k++;
		  }
	  }
  qsort(E,n*(n-1)/2,sizeof(edge),compEdge);		
	  
  
  // initialisation pour Union-and-Find
  int *parent = malloc(n*sizeof(int)); // parent[x]=parent de x (=x si racine)
  int *height = malloc(n*sizeof(int)); // height[x]=hauteur de l'arbre de racine x
  for(int x=0; x<n; x++){
    parent[x]=x; // chacun est racine de son propre arbre
    height[x]=0; // hauteur nulle
  
	T.deg[x] = 0;
  }
  int l=0;
  for(int i=0;i<n*(n-1)/2;i++){
	  if(Find(E[i].v,parent) != Find(E[i].u,parent) && l<n-1 ){
		  Union(Find(E[i].v,parent),Find(E[i].u,parent),parent,height);
		  addEdge(T, E[i].u, E[i].v);
		  l++;
		  }
	  }

 
 
  // libÃ¨re les tableaux
  free(parent);
  free(height);
  free(E);

  dfs(T,0,Q,-1); // calcule Q grÃ¢ce au DFS Ã  partir du sommet 0 de T
  return value(V,n,Q); // renvoie la valeur de la tournÃ©e
}


int main(int argc, char *argv[]) {

  initSDLOpenGL();
  srandom(time(NULL));
  TopChrono(0); // initialise tous les chronos
  bool has_changed = true;
  bool wait_event = true;
  int n = (argv[1] && atoi(argv[1])) ? atoi(argv[1]) : 400;
  graph M = createGraph(n);
  point *V = generatePoints(n, width, height);
  int *P = malloc(n * sizeof(int));
  for(int i=0; i<n; i++) P[i]=i; // tournée de départ
  {
    drawTour(V, n, NULL); // dessine les points
    TopChrono(1); // départ du chrono 1
    double w = tsp_flip(V,n,P);
    char *s = TopChrono(1); // s=durée
    printf("value flip: %g\n",w);
    printf("runing time flip: %s\n",s);
    drawTour(V, -n, P); // force le dessin de la tournée
  }

  sleep(1); // attend 1 seconde

   {
    drawTour(V, n, NULL); // dessine les points
    TopChrono(1); // départ du chrono 1
    double w = tsp_greedy(V,n,P);
    char *s = TopChrono(1); // s=durée
    printf("value greedy: %g\n",w);
    printf("runing time greedy: %s\n",s);
    drawTour(V, -n, P); // force le dessin de la tournée
  }

  double r=(width+height)/4.0;
  int p=n/2;
  point c;
  c.x=width/2.0, c.y=height/2.0;
  generateCircle(V,0,p,c,r); // ajoute un grand cercle
  generateCircle(V,p,n-p,c,r/2.0); // ajoute un petit cercle

  {
    drawTour(V, n, NULL); // dessine les points
    TopChrono(1); // départ du chrono 1
    double w = tsp_mst(V, n, P,M);
    char *s = TopChrono(1); // s=durée
    printf("value mst: %g\n",w);
    printf("runing time mst: %s\n",s);
    drawTour(V, -n, P); // force le dessin de la tournée
  }

  // Affiche le résultat et attend (q pour sortir)
 
 /* while(running){
    wait_event = true;

    if (first_flip(V,n,P) > 0)
      wait_event = false;

    drawTour(V, n, P);
    has_changed = handleEvent(wait_event);
  }
*/
while(running){
  wait_event = true;
  if (has_changed) tsp_mst(V,n,P,M);
  if (first_flip(V,n,P)) wait_event = false;
  drawGraph(V,n,P,M);
  has_changed = handleEvent(wait_event);
 }
 freeGraph(M);
 
  // Libération de la mémoire
  TopChrono(-1);
  free(V);
  free(P);

  cleaning();
  return 0;
}
