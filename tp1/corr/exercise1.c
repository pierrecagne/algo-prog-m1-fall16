#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  int n,m;
  
  printf("This program will compute the euclidean division n = mq+r.\n");
  printf("Choose n: ");
  scanf("%d",&n);
  printf("Choose m: ");
  scanf("%d",&m);
  
  printf("The euclidean division is %d = %d * %d + %d\n", n, m, n/m, n%m);
  
  return EXIT_SUCCESS;
}
