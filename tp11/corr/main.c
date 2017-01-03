#include <stdio.h>
#include <stdlib.h>
#include "cdll.h"

cdll* mat_to_vec (int** adj, int n) {
  cdll *vec = (cdll*) malloc(sizeof(cdll)*n);
  for(int i = 0; i < n; i++) {
    vec[i] = cdll_empty();
    for(int j = 0; j < n; j++)
      if (adj[i][j]) vec[i] = cdll_add(j,vec[i]);
  }

  return vec;
}

cdll cycle_from (int i, int n, cdll* unused, cdll* rvertex) {
  cdll cycle = cdll_create(i);

  int j = i;
  do {
    int t = cdll_get(unused[j]);
    cycle = cdll_add(t,cycle);
    unused[j] = cdll_chop(unused[j]);
    if (!unused[j]) *rvertex = cdll_rem(j,*rvertex);
    j = t;
  } while (j != i);

  return cycle;
}

int main (int argc, char **argv) {

  cdll list = cdll_add(7,cdll_create(6));

  cdll_print (list);
  list = cdll_add(8,list);
  cdll_print (list);
  list = cdll_add(9,list);
  cdll_print (list);
  list = cdll_add(10,list);
  cdll_print (list);
  list = cdll_rem(10,list);
  cdll_print (list);
  list = cdll_rem(19,list);
  cdll_print (list);

  int n=4;
  int** graph = (int**) malloc(sizeof(int*)*n);
  for(int i=0; i<n; i++){
    graph[i] = (int*) malloc(sizeof(int)*n);
    for(int j=0; j<n; j++) graph[i][j] = 0;
  }
  graph[0][1] = 1;
  graph[0][2] = 1;
  graph[0][3] = 1;

  graph[1][2] = 1;
  graph[1][3] = 1;
  
  graph[1][0] = 1;
  graph[2][0] = 1;
  graph[3][0] = 1;

  graph[2][1] = 1;
  graph[3][1] = 1;

  cdll *vec = mat_to_vec (graph,n);
  for(int i=0; i<n; i++) {
    printf("Neighbour of %d: ",i);
    cdll_print(vec[i]);
  }
  
  return EXIT_SUCCESS;
}
