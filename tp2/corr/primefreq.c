#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int prime(int n) {
  if(n<2) { return 0; }
  for(int i=2; i*i<n; i++) {
    if(n%i == 0){ return 0; }
  }

int main(int argc, char** argv){

  srandom(time(NULL));
  int t = 0;
  
  for(int i=0; i<1000000; i++){
    int r = random()%100;
    if(prime(i)){ t++; }
  }
  
  return EXIT_SUCCESS;
}
