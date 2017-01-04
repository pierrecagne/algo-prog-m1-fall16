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

/*
  returns the 9 by 9 grid corresponding to the sudoku contains in the
  file at path; 0s correspond to empty cells.
*/
char **sudoku_filetogrid (char *path);

/*
  returns the constraint satisfaction problem in form of a DLX data as
  described by Knuth in his "dancing links" paper.
*/
//dlx_data sudoku_gridtodlx (char **grid);

/*
  returns the completed sudoku grid(s) (no 0s).
*/
//char **sudoku_solvefromdlx (dlx_data dlx);

/*
  returns a string containing a sudoku in a grid form
*/
char *sudoku_gridtostr (char **grid);

/*
  prints out a sudoku in a grid form
*/
void sudoku_print (char **grid);

#endif
