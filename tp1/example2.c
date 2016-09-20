#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  int n ;
  printf("Choose a number: ");
  scanf("%d", &n); //remark the &
  printf("You chose %d.\n", n);
  
  return EXIT_SUCCESS;
}
