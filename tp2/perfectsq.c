#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  int a, b, c;

  /*  ... computes things with a, b and c ... */

  int i, sqa; //sqa is a boolean
  for(i=0; i*i<=a; i++);
  if(i*i==a){ sqa = 1;} else { sqa = 0;}

  int j, sqb; //sqb is a boolean
  for(j=0; j*j<=b; j++);
  if(j*j==b){ sqb = 1;} else { sqb = 0;}

  int k, sqc; //sqc is a boolean
  for(k=0; k*k<=c; k++);
  if(k*k==c){ sqc = 1;} else { sqc = 0;}

  /* ... code using sqa, sqb and sqc ... */

  return EXIT_SUCCESS;
}
