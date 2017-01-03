#include <stdio.h>
#include <stdlib.h>

int lcs_naive (char* u,char* v,int lu,int lv) {
  if(lu == 0 || lv == 0) return 0;
  else if (u[lu-1] == v[lv-1])
    return lcs(u,v,lu-1,lv-1) + 1;
  else {
    int r = lcs(u,v,lu,lv-1), rr = lcs(u,v,lu-1,lv);
    return r > rr ? r : rr;
  }
}

int memoized_lcs(char* u, char* v, int i, int j, int **computed){
  if (computed[i][j] != -1) return computed[i][j];
  else if (i == 0 || j == 0) {
    computed[i][j] = 0; return 0;
  }
  else if (u[i-1] == v[j-1]) {
    int r = memoized_lcs(u,v,i-1,j-1,computed) + 1;
    computed[i][j] = r; return r;
  }
  else {
    int r = memoized_lcs(u,v,i,j-1,computed), rr = memoized_lcs(u,v,i-1,j,computed);
    computed[i][j] = r > rr ? r : rr;
    return computed[i][j];
  }
}

int lcs(char* u, char* v){
  // caulculer longueurs de v et w: n et m
  int n = 0,m = 0;
  for(; u[n]; n++);
  for(; v[m]; m++);
  
  // initialiser une matrice d'entiers de taille (n+1)x(m+1) avec que des -1
  int **tab = (int**) malloc(sizeof(int*)*(n+1));
  for (int i = 0; i < (n+1) ; i++) {
    tab[i] = (int*) malloc(sizeof(int)*(m+1));
    for (int j = 0 ; j < (m+1) ; j++) tab[i][j] = -1;
  }
  
  // on appelle la fonction auxiliaire
  int r = memoized_lcs(u,v,n,m,tab);
  
  // retourner le resultat rendu
  return r;
}


int main (int argc, char** argv) {

  char u[] = "abcbbaacbaba", v[] = "bbaccabbbacbc";
  int n = 0,m = 0;
  for(; u[n]; n++);
  for(; v[m]; m++);

  printf("%d\n", lcs_naive(u,v,n,m));
  
  return EXIT_SUCCESS;
}
