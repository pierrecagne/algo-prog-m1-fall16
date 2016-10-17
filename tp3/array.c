#include <stdio.h>
#include <stdlib.h>

void table(int,int*);

int main (int argc, char** argv) {

  int tab7[10];
  table(7,tab7);

  printf("Table of 7:\n");
  for(int i = 0; i < 10; i++) {
    printf("7*%d = %d\n", i+1, tab7[i]);
  }

  table(9,tab7);
  printf("\nStill table of 7?\n");
  for(int i = 0; i < 10; i++) {
    printf("7*%d ?= %d\n", i+1, tab7[i]);
  }
    
  
  return EXIT_SUCCESS;
}

void table(int n, int* t) {
  for(int i = 0; i < 10; i++) {
    t[i] = n*(i+1);
  }
}
