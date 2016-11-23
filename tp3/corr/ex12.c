/* file: ex12.c -- correction tp3 ex12
   
   Complement by 2: how to extend binary decomposition to negative
   integers.
*/

#include <stdio.h>
#include <stdlib.h>

// keep this one
void pp_bin (char* bin) {
  int i = 31;
  while (bin[i] == 0) {i--;} // ignore all leading 0s
  while (i >= 0) printf ("%d", (int) bin[i--]);
}

// keep this one for non negative integers
void dec2bin_comp (int n, char* bin) {
  for(int i = 0; i < 31; i++) {
    bin[i] = (char) (n%2); n /= 2;
  }
}

// the number represented by bin is negative if and only if its most
// significant bit is '1'
char is_pos (char* bin) {
  return bin[31] == 0 ? 1 : 0;
}

// by definition, opp codes the opposite of the number repsented by
// bin if and only if the sum of the binaries opp + bin is 2^n. So opp
// can be deduced from bin by putting a 1 in each case where bin as a
// 0, then adding 1 to th result.
void opposite (char* bin, char *opp) {
  for (int i = 0; i < 32; i++) opp[i] = (bin[i] == 0 ? 1 : 0);
  // now adding 1: while encountering bit 1, propagate
  int i = 0;
  while (opp[i] == 1) opp[i++] = 0; 
  if (i == 32) exit(EXIT_FAILURE); // means that bin was -2^{n-1}
  opp[i] = 1; 
}
  
int main (int argc, char** argv) {

  if (argc != 2) {
    printf ("Wrong usage. Use as: %s [n] with n an non negative integer (<2^32).\nExiting.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  int n; char bin[32], opp[32], oppopp[32];
  if (sscanf(argv[1],"%d",&n) != 1) exit(EXIT_FAILURE); // in case the arg is not an integer
  dec2bin_comp (n, bin);
  printf ("%d is %s.\n", n, is_pos(bin) ? "positive" : "negative");
  opposite (bin, opp);
  opposite (opp, oppopp);
  printf ("Binary for %d: ", n); pp_bin(bin); printf ("\n");
  printf ("And its opposite: "); pp_bin (opp); printf("\n");

  // check that opposite of opposite is self
  printf ("Checking... "); char b = 1; int i = 0;
  while (b && i < 32) {
    if (bin[i] != oppopp[i]) b = 0; i++;
  }
  printf (b ? "success.\n" : "failure.\n");
  
  return EXIT_SUCCESS;
}
