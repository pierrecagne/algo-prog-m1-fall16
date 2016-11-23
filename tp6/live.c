#include <stdio.h>
#include <stdlib.h>

/************* TP6 ****************/
char compare_str(char* s, char* t){
  int i = 0;
  while((s[i] == t[i]) && (s[i]!='\0') && (t[i]!='\0'))
    i++;
  return (char) s[i] < t[i];
}

void pp_array (int size, const char** array) {
  for(int i = 0 ; i < size ; i++) printf("%s", array[i]);
}

void swap (int i, int j, char** array) {
  char* tmp = array[i];
  array[i] = array[j], array[j] = tmp;
}

void quick_sort (int min, int max, char** array) {
  if(min >= max) return; // if empty array, nothing to do
  int i = min, j = max;
  char* p = array[max]; // p is the pivot
  while (i < j) { // searching for the point of partition
    // put bigger value on the right and smaller on the left
    while (compare_str(array[i],p) && i <= max && i < j) i++;
    while (!compare_str(array[j],p) && j >= min && i < j) j--;
    if (i == j) break; else swap (i, j, array);
  }
  swap (j, max, array); // put pivot at partition point
  quick_sort (min, j-1, array); quick_sort (j+1, max, array); // recursive calls
}
/************* TP6 ****************/

typedef struct buff_size_s buff_size_t;
struct buff_size_s {
  int nlines;
  int max_line;
};

buff_size_t sizes (FILE* stream) {
  fpos_t *curr = (fpos_t *) malloc(sizeof(fpos_t));
  (void) fgetpos(stream, curr); // save current position
  rewind(stream);

  int nlines = 1, max_line = 0, curr_line = 0, c;
  while ( (c = fgetc(stream)) != EOF ) {
    if ((char) c == '\n') {
      nlines++;
      if (curr_line > max_line) max_line = curr_line;
      curr_line = 0;
    }
    curr_line++;
  }

  (void) fsetpos(stream, curr); // restore position
  return (buff_size_t) {nlines, max_line};
}

void file_to_array(FILE* stream, char** array, int size, int max_size) {
  fpos_t *curr = (fpos_t *) malloc(sizeof(fpos_t));
  (void) fgetpos(stream, curr); // save current position
  rewind(stream);

  for(int i = 0; i < size; i++) fgets(array[i],max_size+1,stream);
  
  (void) fsetpos(stream, curr); // restore position
  return;
}


int main(int argc, char** argv){
    // deal with args
  if (argc != 2) {
    printf ("Usage: sort [path]. File at path should end by an empty\
line.\nExiting...\n");
    exit (EXIT_SUCCESS);
  }

  char* path = argv[1];
  FILE *input = fopen(path,"r");
  if (!input) {
    printf("Failed while opening %s.\nExiting...\n", path);
    exit (EXIT_FAILURE);
  }
  
  buff_size_t s = sizes(input);
  char** tab = (char**) malloc(s.nlines*sizeof(char*));
  for (int i = 0; i < s.nlines; i++)
    tab[i] = malloc(s.max_line*sizeof(char));
  
  file_to_array(input, tab, s.nlines, s.max_line);
  
  quick_sort(0,s.nlines-1,tab);
  pp_array(s.nlines, tab);
  
  return EXIT_SUCCESS;
}
