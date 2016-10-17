/*
What happens in the original program?

Recall that 'if(cond){ code1 } else { code2 }' computes cond and
executes code1 if the result is !=0 else executes code2.

If cond is an affectation, it actually does the affectation, and the
affectation 'n=1' returns 1 [try a 'printf("%d",(n=1)))' to see that],
hence is understood as true.

Of course, what is intented here is to test if n is equal to 1, hence
we need to write 'if(n==1)'.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int n=0;
  printf("The value of n is %d.\n", n);
  
  if(n==1){ //correction here: change '=' to '=='
    printf("This case is obviously useless. Or is it?\n");
  }
  else {
    printf("This is what is gonna be printed!\n");
  }

  return EXIT_SUCCESS;
}
