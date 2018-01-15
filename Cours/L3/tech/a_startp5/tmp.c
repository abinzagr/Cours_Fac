	 /* heap q= heap_create(1,fminimum);
	  node *noeud =node_create(G.start.x,G.start.y,  NULL, h, G.end, G);
	  heap_add(q, (void*)noeud);
	  G.mark[G.start.x][G.start.y] = M_USED | M_PATH;

	  while(!heap_empty(q)){
	  // Pensez à dessiner la grille avec drawGrid(G) à chaque fois, par
	  // exemple, que vous ajouter un sommet à P.
		drawGrid(G);;
	  // Après avoir extrait un noeud de Q, il ne faut pas le détruire,
	  // sous peine de ne plus pouvoir reconstruire le chemin trouvé. Vous
	  // pouvez réfléchir à une solution simple pour libérer tous les
	  // noeuds devenus inutiles à la fin de la fonction. Une fonction
	  // createNode() peut simplifier votre code.
	  noeud = (node*)heap_pop(q);
	  //La fin a été atteinte, on marque les parents avec M_PATH
	  if((noeud->pos.x == G.end.x) && (noeud->pos.y == G.end.y)){
		 while((noeud->pos.x == G.start.x) && (noeud->pos.y == G.start.y)){
		G.mark[noeud->pos.x][noeud->pos.y] = G.mark[noeud->pos.x][noeud->pos.y] | M_PATH;
		noeud =(node*)noeud->parent;
		  }
		  return ;
		}
		for(int x = noeud->pos.x -1; x < noeud->pos.x+1; ++x)
			for(int y = noeud->pos.y-1; y < noeud->pos.y+1; y++){
		if(G.value[x][y] != V_WALL && G.mark[x][y] == M_NULL){
		  G.mark[x][y] = M_USED;
		  heap_add(q, node_create(x,y,noeud,h,G.end,G));
		}//Q->array[Q->nmax-1] = u;
		  }
	  }*/
