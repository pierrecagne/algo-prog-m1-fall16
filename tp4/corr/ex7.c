/* file: ex7.c -- correction tp4 ex7

   Implements Eratosthenes's sieve.
*/

#include <stdio.h>
#include <stdlib.h>

// sieve executes Eratosthenes's sieve for 'n' on the array 'era'.
//
// era should be an interger array of size n+1; n should be at least 2
void sieve (int n, char* era) {
  for (int i = 0; i < n+1; i++) era[i] = 1; // everyone is potentially prime
  era[0] = 0; era[1] = 0; // 0 and 1 are not primes
  for (int i = 0 ; i < n+1; i++) {
    if (era[i]) { // if i is not crossed, cross all its multiples
      for (int j = 2*i ; j < n+1 ; j += i) era[j] = 0;
    }
  }
}

int main (int argc, char** argv) {

  char tab[10000] = {0};
  sieve(9999,tab);
  printf("All primes < 10000: ");
  for (int i = 0; i < 10000; i++) {
    if (tab[i]) printf("%d ",i);
  }
  printf("\n");
  
  return EXIT_SUCCESS;
}
