#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int memoized_lcs(char* v, char* w, int i, int j, int **computed);
int lcs (char* v, char* w);

int main (int argc, char** argv) {

  /* ***** TEST: bst library ***** */
  
  bst_t a = bst_add(bst_add(bst_sing(10),3),12);
  bst_t b = bst_sing(5);

  b = bst_add(bst_add(bst_add(bst_add(bst_add(bst_add(bst_add(b,2),9),1),3),15),7),12);
  if (bst_mem(a,8)) printf("Ok\n");
  else printf("Fail\n");

  printf("a: "); bst_print(a); printf("\n");
  printf("b: "); bst_print(b); printf("\n");

  printf("\n --- \n");
  bst_print_tree(a);
  
  printf("\n --- \n");
  bst_print_tree(b);

  printf("\n --- \n");
  bst_t c = bst_rem(bst_copy(b),9);
  bst_print_tree(c);

  bst_destruct(a); bst_destruct(b); bst_destruct(c);
  
  /* ***************************** */

  /* **** TEST : LCS **** */

  /* char v[] = "paramilitaire", w[] = "parachute"; */

  /* printf ("%d\n", lcs(v,w)); */

  /* ******************** */
  
  return EXIT_SUCCESS;
}



int memoized_lcs(char* v, char* w, int i, int j, int **computed) {
  if (computed[i][j] != -1) return computed[i][j];
  else if (i == 0 || j == 0) {
    computed[i][j] = 0; return 0;
  }
  else if (v[i] == w[j]) {
    int r = memoized_lcs(v,w,i-1,j-1,computed) + 1;
    computed[i][j] = r; return r;
  }
  else {
    int up = memoized_lcs(v,w,i,j-1,computed);
    int left = memoized_lcs(v,w,i-1,j,computed);
    int r = up > left ? up : left;
    computed[i][j] = r; return r;
  }
}

int lcs (char* v, char* w) {
  int n = 0, m = 0;
  for (; v[n] != '\0'; n++);
  for (; v[m] != '\0'; m++);
  int **computed = (int**) malloc(sizeof(int*)*(n+1));
  for (int i = 0; i <= n; i++) {
    computed[i] = (int*) malloc(sizeof(int)*(m+1));
    for (int j = 0; j <= m; j++) computed[i][j] = -1;
  }
  int res =  memoized_lcs(v,w,n,m,computed);
  /* for (int i = 0; i <= n; i++) { */
  /*   for (int j = 0; j <= m ; j++) */
  /*     printf("%d\t", computed[i][j]); */
  /*   printf ("\n"); */
  /* } */
  return res;
}
