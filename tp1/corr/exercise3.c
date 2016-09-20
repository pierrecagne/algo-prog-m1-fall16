#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  int u = 1, v = 1;

  while(v>=u){
    v = v+u;
    u = v-u;
    printf ("%d\n", u);
  }
      
    
  return EXIT_SUCCESS;
}
