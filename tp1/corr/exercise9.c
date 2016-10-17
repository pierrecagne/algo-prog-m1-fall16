#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  long i,n;
  // trap the user in a loop until a correct entry
  do {
    printf("Choose a integer (≥ 2): ");
    scanf("%ld", &n);
  } while(n<2);
  
  // increment i until i reaches sqrt(n) or divides n
  for(i=2; i*i<=n && n%i!=0; i++);

  // if i>sqrt(n), then n has no divider ≤ sqrt(n), hence is prime
  if(i*i>n){
    printf("%ld is prime.\n",n);
  }
  else {
    printf("%ld is not prime as %ld=%ld*%ld.\n", n, n, i, n/i);
  }

  return EXIT_SUCCESS;
}
