/*
  file: sudoku.c
  updated: 03/01/2017
  author: pierre cagne
  
  contains functions dealing with the reading of a sudoku from a file,
  the solving of a sudoku with DLX method, and the translation back to
  a sudoku grid
*/

#include <stdlib.h>
#include <stdio.h>
#include "error.h"

/*
  returns the 9 by 9 grid corresponding to the sudoku contains in the
  file at path; 0s correspond to empty cells.
*/
char **sudoku_filetogrid (char *path){
  // allocating 9x9 grid on the heap
  char **grid = (char **) malloc(sizeof(char*)*9);
  for (size_t i = 0; i < 9; i++)
    grid[i] = (char *) malloc(sizeof(char)*9);
  
  // open file at path and treat errors
  FILE *file = fopen(path,"r");
  if (!file) {
    char msg[ERROR_MAX];
    (void) sprintf(msg, "Error while opening %s", path);
    error_handle(msg);
  }

  // write inside grid the number stored in the file
  for (size_t i = 0; i < 9; i++){
    for (size_t j = 0; j < 9; j++){
      int c = fgetc(file);
      // handle unexpected EOF
      if (c == EOF) {
	char msg[ERROR_MAX];
	(void) sprintf(msg, "Unexpected EOF: file %s probably not in sudoku format", path);
	error_handle(msg);
      }
      grid[i][j] = ((char) c) - '0'; // convert c into the integer it contains
    }
    // each line ends with a '\n'
    int c = fgetc(file);
    if (c != '\n') {
	char msg[ERROR_MAX];
	(void) sprintf(msg, "Unexpected EOF: file %s probably not in sudoku format", path);
	error_handle(msg);
    }
  }

  // close file
  (void) fclose(file);
  
  return grid;
}

/*
  returns the constraint satisfaction problem in form of a DLX data as
  described by Knuth in his "dancing links" paper.

  coding: 
    
    - filling by n (n=1,...,9) the cell (i,j) will be represented by a
  row whose id is 'ijn' in decimal writting
   
    - the constraint that cell (i,j) must be filled is represented by
      a column whose id is 'ij0' in decimal writting
   
    - the constraint that column j must contain n is represented by
      a column whose id is '0jn' in decimal writting
   
    - the constraint that row i must contain n is represented by
      a column whose id is 'i0n' in decimal writting
   
    - the constraint that block b must contain n is represented by
      a column whose id is 'b00n' in decimal writting
      
      Blocks are numeroted 
*/
dlx_data sudoku_gridtodlx (char **grid) {
  
}

/*
  returns the completed sudoku grid(s) (no 0s).
*/
// char **sudoku_solvefromdlx (dlx_data dlx);

/*
  returns a string containing a sudoku in a grid form
*/
char *sudoku_gridtostr (char **grid) {
  char *str = (char *) malloc(sizeof(char)*91);
  str[90] = '\0';
  for (size_t i = 0; i < 9; i++){
    for (size_t j = 0; j < 9; j++) {
      str[10*i+j] = grid[i][j] + '0';
    }
    str[10*i+9] = '\n';
  }

  return str;
}

/*
  prints out a sudoku in a grid form
*/
void sudoku_print (char **grid) {
  printf ("%s", sudoku_gridtostr(grid));

  return;
}
