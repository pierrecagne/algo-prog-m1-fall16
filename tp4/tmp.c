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
    if(array[i] > max) imax = i, max = array[i];
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

void quick_sort (int min, int max, int *array) {
  if(min >= max) return;
  int i = min, j = max, p = array[max];
  while (i < j) {
    while (array[i] < p && i <= max) i++;
    while (array[j] >= p && j >= min) j--;
    if (i < j) swap (i, j, array);
  }
  if (array[j] < p) j++;
  swap (j, max, array);
  quick_sort (min, j-1, array); quick_sort (j+1, max, array);
}

void merge_aux(int lpos, int lend, int rpos, int rend,
	       int *array, int *tmp) {
  if (lpos > lend && rpos > rend) return;
  else if (lpos > lend)
    *tmp = array[rpos], merge_aux(lpos,lend,rpos+1,rend,array,tmp+1);
  else if (rpos > rend)
    *tmp = array[lpos], merge_aux(lpos+1,lend,rpos,rend,array,tmp+1);
  else if (array[lpos] < array[rpos]) {
    *tmp = array[lpos];
    merge_aux(lpos+1,lend,rpos,rend,array,tmp+1);
  } else {
    *tmp = array[rpos];
    merge_aux(lpos,lend,rpos+1,rend,array,tmp+1);
  }
}

/* void merge_aux(int lpos, int lend, int rpos, int rend, */
/* 	       int *array, int *tmp) { */
/*   if (lpos > lend) { */
/*     for(int i = rpos; i <= rend; i++,tmp++) *tmp = array[i]; */
/*     return; */
/*   } */
/*   if (rpos > rend) { */
/*     for(int i = lpos; i <= lend; i++,tmp++) *tmp = array[i]; */
/*     return; */
/*   } */
/*   if (array[lpos] < array[rpos]) { */
/*     *tmp = array[lpos]; */
/*     merge_aux(lpos+1,lend,rpos,rend,array,tmp+1); */
/*   } else { */
/*     *tmp = array[rpos]; */
/*     merge_aux(lpos,lend,rpos+1,rend,array,tmp+1); */
/*   } */
/* } */

void merge (int start, int mid, int end, int *array) {
  int tmp[end-start+1];
  merge_aux (start, mid-1, mid, end, array, tmp);
  for (int i = start; i <= end; i++) array[i] = tmp[i-start];
}
/* void merge (int start, int mid, int end, int *array) { */
/*   int tmp[end-start+1]; */
/*   int i = start, j = mid, k; */
/*   for (k = 0; i < mid && j <= end; k++) { */
/*     if (array[i] < array[j]) { tmp[k] = array[i]; i++; } */
/*     else { tmp[k] = array[j]; j++; } */
/*   } */
/*   if (i == mid) */
/*     for (; j <= end; k++, j++) tmp[k] = array[j]; */
/*   else */
/*     for (; i < mid; k++, i++) tmp[k] = array[i]; */
/*   for (int l = start; l <= end; l++) array[l] = tmp[l-start]; */
/* } */

void merge_sort (int start, int end, int *array) {
  if (start >= end) return;
  merge_sort (start, (end+start)/2, array);
  merge_sort ((end+start)/2 + 1, end, array);
  merge (start, (end+start)/2 + 1, end, array);
}

int main (int argc, char** argv) {
  int t[17] = {8,24,6,7,90,42,53,17,6,4,19,56,893,2,1,0,3};

  merge_sort(2, 7, t);
  pp_array(17, t);
  
  return EXIT_SUCCESS;
}
