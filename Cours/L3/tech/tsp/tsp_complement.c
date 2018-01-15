/* ==== Programmation dynamique ====*/

static void drawPath(point *V, int n, int *path, int len);

static int NextSet(int S, int n){
/*
  Renvoie le plus petit entier immÃ©diatement supÃ©rieur Ã  S>0 et qui a
  soit le mÃªme poids que S, c'est-Ã -dire le mÃªme nombre de 1 dans son
  Ã©criture binaire que S, soit le poids de S plus 1 s'il n'y en a pas
  de mÃªme poids. La fonction renvoie 0 si S est le plus grand entier
  sur n bits, soit S=2^n-1.

  L'algorithme est le suivant: dans S on dÃ©cale complÃ¨tement Ã  droite
  le premier bloc de 1 (celui contenant le bit de poids faible) sauf
  le bit le plus Ã  gauche de ce bloc qui lui est dÃ©calÃ© d'une position
  Ã  gauche. Si on ne peut pas dÃ©caler ce bit plus Ã  gauche c'est que
  ou bien on est arrivÃ© Ã  2^n-1 (et on renvoie 0) ou bien on doit
  passer Ã  un poids plus Ã©levÃ©. Dans ce cas on renvoie 2^p-1 oÃ¹ p est
  le nouveau nombre de 1 de S plus 1.

  RÃ©sultats obtenus en itÃ©rant S -> NextSet(S,4) Ã  partir de S=1:
   (taille 1) S = 0001 -> 0010 -> 0100 -> 1000 ->
   (taille 2)     0011 -> 0101 -> 0110 -> 1001 -> 1010 -> 1100 ->
   (taille 3)     0111 -> 1011 -> 1101 -> 1110
   (taille 4)     1111 ->
   (taille 0)     0000

  Ainsi, les 16 entiers sur n=4 bits sont parcourus dans l'ordre: 1 ->
  2 -> 4 -> 8 -> 3 -> 5 -> 6 -> 9 -> 10 -> 12 -> 7 -> 11 -> 13 -> 14
  -> 15 -> 0

  L'algorithme prend un temps O(1) car les opÃ©rations de shifts (<<)
  et la fonction ffs() sur des int correspondent Ã  des instructions
  machines sur des registres.
*/
  int p1 = ffs(S); // position du bit le plus Ã  droit (commence Ã  1)
  int p2 = ffs(~(S >> p1)) + p1 - 1; // position du bit le plus gauche du 1er bloc de 1
  if (p2 - p1 + 1 == n) return 0; // cas S=2^n-1
  if (p2 == n) return (1 << (p2 - p1 + 2)) - 1; // cas: poids(S)+1
  return (S & ((-1) << p2)) | (1 << p2) | ((1 << (p2 - p1)) - 1); // cas: poids(S)
}

#define IN_SET(S,i)  ((S) & (1 << (i))) // est-ce que i est dans S ?
#define ADD_SET(S,i) (S | (1 << (i)))   // ajoute i Ã  S
#define DEL_SET(S,i) (S & ~(1 << (i)))  // supprimer i de S

/* une cellule de la table */
typedef struct{
  double cost; // coÃ»t du chemin minimum D[t][S]
  int pred;    // point prÃ©cÃ©dant t dans la solution D[t][S]
} cell;

static double tsp_prog_dyn(point *V, int n, int *Q){
/*
  Version programmation dynamique du TSP. Le rÃ©sultat doit Ãªtre Ã©crit
  dans la permutation Q. On renvoie la valeur de la tournÃ©e minimum ou
  -1 s'il y a eut une erreur (pression de 'q' pour sortir de
  l'affichage).  Une fois que votre programme arrivera Ã  calculer une
  tournÃ©e optimale (Ã  comparer avec tsp_brute_force()), il sera
  intÃ©ressant de dessiner Ã  chaque fois que possible le chemin courant
  avec drawPath().

  Attention ! Par rapport au cours, il est plus malin de commencer la
  tournÃ©e Ã  partir du point d'indice n-1 (au lieu de 0). Pourquoi ?

  Pour rÃ©sumer:

  - D[t][S].cost = coÃ»t minimum d'un chemin allant de V[n-1] Ã  V[t]
    qui visite tous les points d'indice dans S

  - D[t][S].pred = l'indice du point prÃ©cÃ©dant V[t] dans le chemin
    ci-dessus de coÃ»t D[t][S].cost
*/

  int t,S;
  
  // dÃ©claration de la table D[t][S] qui comportent (n-1)*2^(n-1) cellules
  cell **D = malloc((n-1)*sizeof(cell*)); // n-1 lignes
  for(t=0; t<n-1; t++) D[t] = malloc((1<<(n-1))*sizeof(cell)); // 2^{n-1} colonnes

  // si Q n'est pas allouÃ©, c'est peut-Ãªtre le bon moment pour le
  // faire ici ...
  if(Q==NULL)
	Q=malloc(n*sizeof(int));
  //;;;
  
  // cas de base, lorsque S={t}, pour t=0..n-2: D[t][S]=d(V[n-1],V[t])
  S=1;
  for(int t=0;t<n-2;t++){  
	D[t][S]=d(V[n-1],V[t]);
  }  
  NextSet(S,n-1);
  // S=...0001 et pour l'incrÃ©menter utiliser NextSet(S,n-1)
  //;;;
  //;;;D[x][S\{t}] + d(V[x],V[t])

  // cas |S|>1: D[t][S] = min_x { D[x][S\{t}] + d(V[x],V[t]) }
  // avec t dans S et x dans S\{t}
  do{
	 for(int t=0;t<n-1;t++){ 
		if(IN_SET(S,t))
		for(int x=0;x<n-2;x++){
				D[t][S] = D[x][] + d(V[x],V[t])
		 } 
	 }	 
    
    // ici D[t][S].cost et D[t][S].pred viennent d'Ãªtre calculÃ©s
    // dÃ©commenter la suite pour dessiner le chemin partiel qui
    // est construit en partant de V[t] et en remontant jusqu'Ã  V[n-1]
    //
    int St;
    St=S;
    Q[0]=t;  // Ã©crit le dernier point connu
    int k=1; // k=taille de Q=nombre de points Ã©crits dans Q
    while(Q[k-1]!=n-1){
      Q[k] = D[Q[k-1]][St].pred;
      St=DEL_SET(St,Q[k-1]);
      k++;
     }
    drawPath(V, n, Q, k);
    
  }while ((S = NextSet(S, n-1)) && running);

  double w=-1; // valeur de la tournÃ©e optimale, -1 par dÃ©faut
  
  if(running){
    // on a terminÃ© correctement le calcul complet de la table D. Il
    // faut alors calculer le coÃ»t w de la tournÃ©e optimale et
    // Ã©ventuellement construire la tournÃ©e pour la mettre dans Q. NB:
    // si le calcul a Ã©tÃ© interrompu (pression de 'q' pendant
    // l'affichage) alors ne rien faire et renvoyer -1
    ;;;
    ;;;
  }

  ;;; // pensez Ã  libÃ©rer la table D
  return w; 
}


static void drawPath(point *V, int n, int *path, int len){

  // saute le dessin si le prÃ©cÃ©dent a Ã©tÃ© fait il y a moins de 20ms
  static unsigned int last_tick = 0;
  if (last_tick + 20 > SDL_GetTicks()) return;
  last_tick = SDL_GetTicks();
  
  // gestion de la file d'event
  handleEvent(false);
  
  // efface la fenÃªtre
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);
  
  // dessine le chemin
  selectColor(0,1,0); // vert
  for (int i = 0 ; i < len-1 ; i++)
    drawLine(V[path[i]], V[path[i+1]]);
  
  // dessine les points
  selectColor(1,0,0); // rouge
  for (int i = 0 ; i < n ; i++)
    drawPoint(V[i]);
  
  // affiche le dessin
  SDL_GL_SwapWindow(window);
}
