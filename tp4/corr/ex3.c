/*
file: ex3.c -- correction exercise3 tp4

Implements bubble sort: "push" maximum at the end of the array by
successive local swap ; repeat with the yet unsorted elements.
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

// bubble_sort sorts 'array' of size 'size' *in place*
//
// for recursion, it uses the same trick as select_sort of ex2
//
// This should now become your punchline about arrays: C doesn't know
// about size of arrays, only you do!
void bubble_sort (int size, int *array) {
  if(size == 0) return;
  for (int i = 0; i+1 < size; i++) // bubble the maximum up
    if(array[i] > array[i+1]) swap(i,i+1,array);
  bubble_sort (size-1, array);
}


int main (int argc, char** argv) {
  int t[17] = {8,24,6,7,90,42,53,17,6,4,19,56,893,2,1,0,3};

  pp_array(17,t); // print t
  bubble_sort(17, t); // sort t
  pp_array(17, t); // verify

  for (int i = 0; i < 17; i++) swap (i, (i*i+1)%17, t); // mess t a little
  pp_array(17,t); // for comparison
  bubble_sort(6,t+5); // only sort the subarray from t[5] to t[10]
  pp_array(17,t);
  
  return EXIT_SUCCESS;
}
