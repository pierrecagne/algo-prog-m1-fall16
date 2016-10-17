#include <stdio.h>
#include <stdlib.h>

int issquare(int n) {
  int i;
  for(i=0; i*i<=n; i++);
  if(i*i==n){ return 1; } else { return 0; }
}


int main(int argc, char** argv){

  int a, b, c;

  /* ... computes things with a, b and c ... */

  int sqa = issquare(a), sqb = issquare(b), sqc = issquare(c);

  /* ... code using sqa, sqb and sqc ... */

  return EXIT_SUCCESS;
}
