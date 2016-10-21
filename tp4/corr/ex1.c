/*
file: ex1.c -- correction exercise 1 tp4

Here are small toy functions about array (of integers). Some are also
usefull for the rest of the exercises.
 */

#include <stdio.h>
#include <stdlib.h>

// pp_array print size integer stored in memory starting at adress
// array.
//
// elements are separated by a blank space and a newline is printed at
// the end
void pp_array (int size, const int *array) {
  for(int i = 0 ; i < size ; i ++)
    printf("%d ", array[i]);
  printf("\n");
}

// copy_array makes an exact copy of src in dest ; dest and src should
// have the same size.
//
// notice the 'const' ; it serves to say that (the dereferentitation
// of) src should not be modified inside coppy_array ; try something
// like 'src[0] = 0' inside the function and gcc (or any reasonable
// compiler) should fail.
void copy_array (int size, int *dest, const int *src) {
  for(int i = 0; i < size; i++) dest[i] = src[i];
}

// swap exchanges the content of array[i] with the one of array[j].
void swap (int i, int j, int *array) {
  int tmp = array[i];
  array[i] = array[j], array[j] = tmp;
}

// max_array returns the index of the first occurence of the maximum
// in array (up to index size-1).
int max_array (int size, int *array) {
  int imax = 0, max = array[0];
  for (int i = 0; i < size; i++)
    if(array[i] > max) imax = i, max = array[i];
  return imax;
}

// similarly for the index of the minimum
int min_array (int size, int *array) {
  int imin = 0, min = array[0];
  for (int i = 0; i < size; i++)
    if(array[i] < min) imin = i, min = array[i];
  return imin;
}

int main(int argc, char **argv) {
  int t[10] = {9,42,35,76,4,13,14,0,34,2};

  pp_array(10,t); // print t
  swap(4,7,t); // exchange 4 and 0 in t
  pp_array(10,t); // print to verify

  int u[7];
  copy_array(7, u, t); // copy the first 7 elts of t in u
  /* Remark that here I use t as an array of 7 elt even if it has
     actually 10 at start. C does not know anything about array
     length, only you do! */
  pp_array(7,u);

  // actually, we can go further in that kind of thing
  copy_array(5, u, t+2);
  copy_array(2, u+5, t);
  pp_array(7,u);

  // continue to play with it to get how pointers and arrays work
  
  return EXIT_SUCCESS;
}
