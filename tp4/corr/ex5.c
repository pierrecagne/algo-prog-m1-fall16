/*
file: ex5.c -- correction exercise5 tp4

Implements quick sort: choose an element (the last one) as pivot ; put
every smaller elts on the left, and every greather on the right ;
repeat on the left and right subarray thus created.
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

// quick_sort(0,size-1,array) sorts 'array' of size 'size' *in place*
//
// for recursion, more than ever the same trick.
//
// At this point the punchline is: C only knows how to point to
// something, everything else is your doing!
void quick_sort (int min, int max, int *array) {
  if(min >= max) return; // if empty array, nothing to do
  int i = min, j = max, p = array[max]; // p is the pivot
  while (i < j) { // searching for the point of partition
    // put bigger value on the right and smaller on the left
    while (array[i] < p && i <= max && i < j) i++;
    while (array[j] >= p && j >= min && i < j) j--;
    if (i == j) break; else swap (i, j, array);
  }
  swap (j, max, array); // put pivot at partition point
  quick_sort (min, j-1, array); quick_sort (j+1, max, array); // recursive calls
}


int main (int argc, char** argv) {
  int t[17] = {8,24,6,7,90,42,53,17,6,4,19,56,893,2,1,0,3};

  pp_array(17,t); // print t
  quick_sort(0, 16, t); // sort t
  pp_array(17, t); // verify

  for (int i = 0; i < 17; i++) swap (i, (i*i+1)%17, t); // mess t a little
  pp_array(17,t); // for comparison
  quick_sort(5,10,t); // only sort the subarray from t[5] to t[10]
  pp_array(17,t);
  
  return EXIT_SUCCESS;
}
