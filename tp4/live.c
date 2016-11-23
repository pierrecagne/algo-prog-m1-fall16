#include <stdio.h>
#include <stdlib.h>

void pp_array (int size, const int *array) {
  for(int i = 0 ; i < size ; i ++)
    printf("%d ", array[i]);
  printf("\n");
}

void copy_array (int size, int *dest, const int *src) {
  for(int i = 0; i < size; i++)
    dest[i] = src[i];
}

void swap (int i, int j, int *array) {
  int tmp = array[i];
  array[i] = array[j], array[j] = tmp;
}

int max_array (int size, int *array) {
  int imax = 0, max = array[0];
  for (int i = 0; i < size; i++)
    if(array[i] >= max) imax = i, max = array[i];
  return imax;
}

void select_sort (int size, int *array) {
  if(size == 0) return ;
  swap (max_array(size, array), size-1, array);
  select_sort (size-1, array);
}

void bubble_sort (int size, int *array) {
  if(size == 0) return;
  for (int i = 0; i+1 < size; i++)
    if(array[i] > array[i+1]) swap(i,i+1,array);
  bubble_sort (size-1, array);
}

void insert_sort (int size, int i, int *array) {
  if (i < 0) return;
  for (int j = i; j+1 < size; j++)
    if (array[j] > array[j+1]) swap(j,j+1,array);
  insert_sort (size, i-1, array);
}


int main (int argc, char **argv) {

  int t[10] = {8,53,7,86,33,42,86,9,54,2};

  pp_array(10,t);
  select_sort(10,t);
  pp_array(10,t);

  return EXIT_SUCCESS;
}
