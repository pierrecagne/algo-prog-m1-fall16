/* file: ex9_to_11.c -- correction tp3 ex9 ex10 ex11

   Binary decomposition. Remark the binary decomposition of a integer
   of type 'int' (even 'unsigned int') fits necessarily in an array of
   length 32 because it is < 2^32.
*/

#include <stdio.h>
#include <stdlib.h>


// bin is an array of 0 and 1 contaning the binary decomposition of
// 'n' at return point, least siginificant bit first: meaning for
// example that it contains {0,1,1,0,...,0} when executed on 6.
void dec2bin (unsigned int n, char* bin) {
  for(int i = 0; i < 32; i++) {
    bin[i] = (char) (n%2); n /= 2;
  }
}

// executes sum (i=0 to 31) (bin_i * 2^i)
unsigned int bin2dec (char* bin) {
  unsigned int n = 0, pow = 1;
  for (int i = 0; i < 32; i++) {
    n += (bin[i]*pow); pow *= 2;
  }
  return n;
}

void pp_bin (char* bin) {
  int i = 31;
  while (bin[i] == 0) {i--;} // ignore all leading 0s
  while (i >= 0) printf ("%d", (int) bin[i--]);
}

int main (int argc, char** argv) {

  if (argc != 2) {
    printf ("Wrong usage. Use as: %s [n] with n an non negative integer (<2^32).\nExiting.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  unsigned int n; char bin[32];
  if (sscanf(argv[1],"%u",&n) != 1) exit(EXIT_FAILURE); // in case the arg is not an integer
  dec2bin(n,bin);
  printf("Binary for %u is: ", n); pp_bin (bin); printf("\n");
  printf("(Ckeck: %s)\n", n == bin2dec(bin) ? "success" : "failure");
  
  return EXIT_SUCCESS;
}
