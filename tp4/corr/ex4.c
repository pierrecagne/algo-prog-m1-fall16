/*
file: ex4.c -- correction exercise4 tp4

Implements insertion sort: insert element i in the array from i+1 of
already sorted elements ; repeat from i = size-1 to i = 0.
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

// insert_sort(size, size-1, array) sorts 'array' of size 'size' *in place*
//
// for recursion, it uses a slight amelioriation of the trick of ex2
// and ex3
//
// The punchline also should be updated: C doesn't know about size of
// arrays, neither does it about "first cell", only you do!
void insert_sort (int size, int i, int *array) {
  if (i < 0) return;
  for (int j = i; j+1 < size; j++)
    if (array[j] > array[j+1]) swap(j,j+1,array);
  insert_sort (size, i-1, array);
}


int main (int argc, char** argv) {
  int t[17] = {8,24,6,7,90,42,53,17,6,4,19,56,893,2,1,0,3};

  pp_array(17,t); // print t
  insert_sort(17, 16, t); // sort t
  pp_array(17, t); // verify

  for (int i = 0; i < 17; i++) swap (i, (i*i+1)%17, t); // mess t a little
  pp_array(17,t); // for comparison
  insert_sort(6,10,t+5); // only sort the subarray from t[5] to t[10]
  pp_array(17,t);
  
  return EXIT_SUCCESS;
}
