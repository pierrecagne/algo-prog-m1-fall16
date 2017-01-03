#include <stdlib.h>
#include <stdio.h>

int memoized_lcs(char* v, char* w, int i, int j,
		 int **computed, char **from);
char* lcs (char* v, char* w);

int main (int argc, char** argv) {

  char v[] = "parascolaire", w[] = "paramedical";

  printf ("%s\n", lcs(v,w));
  
  return EXIT_SUCCESS;
}

int memoized_lcs(char* v, char* w, int i, int j,
		 int **computed, char **from) {
  if (computed[i][j] != -1) return computed[i][j];
  else if (i == 0 || j == 0) {
    computed[i][j] = 0; from[i][j] = 0; return 0;
  }
  else if (v[i-1] == w[j-1]) {
    int r = memoized_lcs(v,w,i-1,j-1,computed,from) + 1;
    computed[i][j] = r; from[i][j] = 2; return r;
  }
  else {
    int up = memoized_lcs(v,w,i-1,j,computed,from);
    int left = memoized_lcs(v,w,i,j-1,computed,from);
    int r = up > left ? up : left;
    from[i][j] = up > left ? 1 : 3;
    computed[i][j] = r; return r;
  }
}

char* lcs (char* v, char* w) {
  int n = 0, m = 0;
  for (; v[n] != '\0'; n++);
  for (; w[m] != '\0'; m++);
  int **computed = (int**) malloc(sizeof(int*)*(n+1));
  char **from = (char**) malloc(sizeof(char*)*(n+1));
  for (int i = 0; i <= n; i++) {
    computed[i] = (int*) malloc(sizeof(int)*(m+1));
    from[i] = (char*) malloc(sizeof(char)*(m+1));
    for (int j = 0; j <= m; j++) {
      computed[i][j] = -1; from[i][j] = -1;
    }
  }
  int res =  memoized_lcs(v,w,n,m,computed,from);
  /* for (int i = 0; i <= n; i++) { */
  /*   for (int j = 0; j <= m ; j++) */
  /*     printf("%d,%d\t", computed[i][j], (int) from[i][j]); */
  /*   printf ("\n"); */
  /* } */
  /* printf("%d \n", res); */
  char *cs = (char*) malloc(sizeof(char)*(res+1));
  cs[res] = '\0';
  int i = res-1;
  while (i>=0) {
    if (from[n][m] == 2){
      cs[i] = v[n-1] ; i--; m--, n--;
    }
    else if (from[n][m] == 1) n--;
    else if (from[n][m] == 3) m--;
  }
  
  return cs;
}
