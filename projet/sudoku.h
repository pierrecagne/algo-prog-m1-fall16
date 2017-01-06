/*
  file: sudoku.h
  updated: 03/01/2017
  author: pierre cagne
  
  header file for sudoku.c; contains functions dealing with the
  reading of a sudoku from a file, the solving of a sudoku with DLX
  method, and the translation back to a sudoku grid
*/

#ifndef SUDOKU_H
#define SUDOKU_H

#include "dlx.h"

/*
  returns the 9 by 9 grid corresponding to the sudoku contains in the
  file at path; 0s correspond to empty cells.
*/
char **sudoku_filetogrid (char *path);

/*
  returns the constraint satisfaction problem in form of a DLX data as
  described by Knuth in his "dancing links" paper.
*/
dlx_data sudoku_gridtodlx (char **grid);

/*
  returns the completed sudoku grid(s) (no 0s).
*/
char **sudoku_solve (char **grid);

/*
  same as sudoku_solve but does not check for unique solution, and
  prints out every solution.
*/
void sudoku_print_all_solutions (char **grid);

/*
  check if a completed grid is actually a solution of a given sudoku
  grid.
*/
char sudoku_check (char **sol, char** grid);
char sudoku_check_fast (char **sol, char** grid);

/*
  returns a string containing a sudoku in a grid form
*/
char *sudoku_gridtostr (char **grid);

/*
  prints out a sudoku in a grid form
*/
void sudoku_print (char **grid);

#endif
