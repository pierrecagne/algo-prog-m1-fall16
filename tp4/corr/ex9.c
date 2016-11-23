/* file: ex9.c -- correction tp4 ex9 (homeworks)

   Introduction to dynamic programming.
*/

#include <stdio.h>
#include <stdlib.h>

/* Complexity is O(size^2) because of the nested loops.
   In details, it is given by:

   sum (for i = 0 to size-1) ( size-i + O(1) )
   = sum (for i = 1 to size) ( i + O(1) )
   = O(size^2)
 */
int max_sum (int size, int* array) {
  int max = 0, curr;
  for (int i = 0; i < size; i++) { // for every start i
    curr = 0;
    for (int j = i; j < size; j++) { // and every stop j
      curr += array[j];
      if (curr > max) max = curr; // compare with array[i]+...+array[j]
    }
  }
  return max;
}

// returns the maximum of two integers
int maximum (int a, int b) { return a > b ? a : b; }

/*
  m_{i+1} = max ( m_i,  max of array[j]+...+array[i+1] with j <= i) otherwise

  Complexity is obviously O(n).
*/
int max_sum_better (int size, int* array) {
  int max = 0, max_ending_here = 0;
  // max will be the maximum so far ; max_ending_here will be the
  // maximum of sum of subarray ending at current index.
  for (int i = 0; i < size; i++) {
    max_ending_here = maximum (0,max_ending_here + array[i]);
    max = maximum (max, max_ending_here);
  }
  return max;
}

int main (int argc, char** argv) {

  int t[] = {-1,1,8,-7,9,-2};
  printf("with max_sum: %d / with max_sum_better: %d\n", max_sum(6,t), max_sum_better(6,t));
  
  return EXIT_SUCCESS;
}
