/*
file: ex2.c -- correction exercise2 tp4

Implements selection sort: select maximum and put it at the end of the
array ; repeat with the yet unsorted elements.
 */

#include <stdio.h>
#include <stdlib.h>

// repeat useful function from ex1
void pp_array (int size, const int *array) {
  for(int i = 0 ; i < size ; i ++)
    printf("%d ", array[i]);
  printf("\n");
}

void swap (int i, int j, int *array) {
  int tmp = array[i];
  array[i] = array[j], array[j] = tmp;
}

int max_array (int size, int *array) {
  int imax = 0, max = array[0];
  for (int i = 0; i < size; i++)
    if(array[i] > max) imax = i, max = array[i];
  return imax;
}

// select_sort sorts 'array' of size 'size' *in place*
//
// remember that array is actually a pointer on the first cell of
// 'array', hence 'array' is also an array of size anything smaller
// than 'size'.
//
// Again: C doesn't know about size of arrays, only you do!
void select_sort (int size, int *array) {
  if(size == 0) return ; // if array is empty, nothing to do
  // else swap maximum with last element and repeat on first elements
  swap (max_array(size, array), size-1, array);
  select_sort (size-1, array);
}

int main (int argc, char** argv) {
  int t[17] = {8,24,6,7,90,42,53,17,6,4,19,56,893,2,1,0,3};

  pp_array(17,t); // print t
  select_sort(17, t); // sort t
  pp_array(17, t); // verify

  for (int i = 0; i < 17; i++) swap (i, (i*i+1)%17, t); // mess t a little
  pp_array(17,t); // for comparison
  select_sort(6,t+5); // only sort the subarray from t[5] to t[10]
  pp_array(17,t);
  
  return EXIT_SUCCESS;
}
