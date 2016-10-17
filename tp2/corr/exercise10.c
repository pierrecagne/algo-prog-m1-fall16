/*
  file: exercise10.c
  date: last updated on 27/09/2016
  ---

  J'aimerais tant voir Syracuse...
*/

#include <stdio.h>
#include <stdlib.h>

int syracuse(int);

int main(int argc, char** argv) {

  for(int m = 1; m <= 100; m++)
    printf("syracuse(%d) hits 1 at time %d.\n", m, syracuse(m));

  return EXIT_SUCCESS;
}
  
//return the first time syracuse hits 1
int syracuse(int m){
  int s = m, i = 0;
  while(s != 1){
    if (s%2 == 0) s/=2; else s=3*s+1;
    i++;
  }
  
  return i;
}
