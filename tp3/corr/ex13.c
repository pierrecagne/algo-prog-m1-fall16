/* file: ex13.c -- correction tp 3 ex13

   Quick gcd using binary manipulation of integers. The oprations n%2,
   n/2 and n*2 are respectively n&1, n>>1 and n<<1.
*/

#include <stdio.h>
#include <stdlib.h>

// compute gcd
int gcd(int a, int b) {
  if (!b) return a; if (!a) return b; // base cases
  
  if (!(a&1) && !(b&1)) return gcd (a>>1,b>>1)<<1; // a and b even
  if (!(a&1) && (b&1)) return  gcd (a>>1,b); // a even, b odd
  if ((a&1) && (b&1) && (a>=b)) return gcd (a-b,b); // a and b odd, a>=b

  return gcd (b,a); // otherwise
}


int main (int argc, char** argv) {

  if (argc != 3) {
    printf("Usage: %s [a] [b] with a,b integers.\nExiting...\n", argv[0]);
    exit (EXIT_SUCCESS);
  }

  int a,b;
  if ((sscanf(argv[1],"%d",&a)) != 1) exit(EXIT_FAILURE); // check arg1 is int
  if ((sscanf(argv[2],"%d",&b)) != 1) exit(EXIT_FAILURE); // check arg2 is int

  printf ("gcd(%d,%d) = %d\n", a, b, gcd(a,b));
  
  return EXIT_SUCCESS;
}
