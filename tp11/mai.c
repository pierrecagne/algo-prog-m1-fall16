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

int main (int argc, char **argv) {

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

