/*
file: ex6.c -- correction exercise6 tp4

Implements merge sort: divides the array in two (almost) equal parts ;
recursively sort both then merge te two results into one sorted array.

'merge_aux' is kind of difficult to get, but it is very C-flavoured:
little less readable, but very compact. Try to understand it!
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

// merge_sort(0,size-1,array) sorts 'array' of size 'size', not
// exactly in place, but stores the result again in 'array'.
//
// for recursion, more than ever the same trick.

// auxiliary function, only called by 'merge' ; compare array[lpos]
// and array[rpos], then put the smaller one in *tmp ; recursively
// call to continue the merge ; don't forget to increment tmp also!
void merge_aux(int lpos, int lend, int rpos, int rend,
	       int *array, int *tmp) {
  if (lpos > lend && rpos > rend) return; // done
  // if one of the array is done, just copy the end of the remaining
  // one
  else if (lpos > lend || rpos > rend) {
    *tmp = array[ lpos > lend ? rpos++ : lpos ++ ];
    merge_aux(lpos,lend,rpos,rend,array,tmp+1);
  }
  // actual merge
  else {
    *tmp = array[ array[lpos] < array[rpos] ? lpos++ : rpos++ ] ;
    merge_aux(lpos,lend,rpos,rend,array,tmp+1);
  }
}

// merge into a new array (again stored in 'array') the sorted
// subarrays {array[0],...,array[mid-1]} and
// {array[mid],...,array[end]}
void merge (int start, int mid, int end, int *array) {
  int tmp[end-start+1]; // temporary array to store the result
  merge_aux (start, mid-1, mid, end, array, tmp); // get merge_aux to do the work
  for (int i = start; i <= end; i++) array[i] = tmp[i-start]; // copy tmp into array
}

// exactly maches the description of the algorithm
void merge_sort (int start, int end, int *array) {
  if (start >= end) return;
  merge_sort (start, (end+start)/2, array);
  merge_sort ((end+start)/2 + 1, end, array);
  merge (start, (end+start)/2 + 1, end, array);
}


int main (int argc, char** argv) {
  int t[17] = {8,24,6,7,90,42,53,17,6,4,19,56,893,2,1,0,3};
  
  pp_array(17,t); // print t
  merge_sort(0, 16, t); // sort t
  pp_array(17, t); // verify

  for (int i = 0; i < 17; i++) swap (i, (i*i+1)%17, t); // mess t a little
  pp_array(17,t); // for comparison
  merge_sort(5,10,t); // only sort the subarray from t[5] to t[10]
  pp_array(17,t);
  
  return EXIT_SUCCESS;
}
