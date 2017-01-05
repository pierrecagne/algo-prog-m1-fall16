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
#include "dlx.h"
#include "list.h"

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
      
      Blocks are numbered as follow: cell (i,j) is in block b =
      3*qi+qj+1 where qi (resp. qj) is the quotient in the euclidian
      division of i-1 (resp. j-1) by 3 (cf. scheme).
      
       ------ ------ ------
      |      |      |      |
      |  1   |   2  |   3  |
      |      |      |      |
       ------ ------ ------
      |      |      |      |
      |  4   |   5  |   6  |
      |      |      |      |
       ------ ------ ------
      |      |      |      |
      |  7   |   8  |   9  |
      |      |      |      |
       ------ ------ ------ 

  for example, filling cell (3,5) with a 9 (supposing it is an empty
  cell) satisfies the constraints of filling (3,5), having a 9 in
  column 5, in row 3 and in block 2; hence there will be a row with id
  359 having 1s in the columns with following ids: 350, 59, 309, 2009.

  if a cell (i,j) is pre-filled with digit n, there is a row 'ijn' and
  no row 'ijk' for any other digit k; this row will be selected in a
  solution by the solver, as it is then the only one having a 1 in
  column 'ij0'.
*/
// auxialiary, see definition below
static list_t get_constraint (size_t i, size_t j, size_t n);

dlx_data sudoku_gridtodlx (char **grid) {
  dlx_data root = dlx_new(); // initialize the dlx data

  /*  let's start by adding the columns (i.e. constraints) */
  // each cell must be filled
  for (idcolumn_t i = 1; i <= 9; i++)
    for (idcolumn_t j = 1; j <= 9; j++)
      root = dlx_add_column(i*100+j*10, root);
  // each row must contain 1,2,...,9
  for (idcolumn_t i = 1; i <= 9; i++)
    for (idcolumn_t n = 1; n <= 9; n++)
      root = dlx_add_column(i*100+n,root);
  // each column must contain 1,2,...,9
  for (idcolumn_t j = 1; j <= 9; j++)
    for (idcolumn_t n = 1; n <= 9; n++)
      root = dlx_add_column(j*10+n,root);
  // each block must contain 1,2,...,9
  for (idcolumn_t b = 1; b <= 9; b++)
    for (idcolumn_t n = 1; n <= 9; n++)
      root = dlx_add_column(b*1000+n,root);

  /* now, let's add the row */
  for (size_t ii = 0; ii < 9; ii++)
    for (size_t jj = 0; jj < 9; jj++) {
      size_t i = ii+1, j = jj+1; // match the usual numbering
      if (grid[ii][jj]) // if cell pre-filled
	root = dlx_add_row((idrow_t) (i*100+j*10+grid[ii][jj]), get_constraint(i,j,grid[ii][jj]), root);
      else // if cell is empty, add one row per filling
	for (size_t n = 1; n <=9; n++)
	  root = dlx_add_row((idrow_t) (i*100+j*10+n), get_constraint(i,j,n),root);
    }

  return root;
}

/*
  returns the list of column ids for which row 'ijn' should have a 1
*/
static list_t get_constraint (size_t i, size_t j, size_t n) {
  return list_cons((idcolumn_t) ((3*((i-1)/3)+(j-1)/3+1)*1000+n),
		   list_cons((idcolumn_t) (j*10+n),
			     list_cons((idcolumn_t) (i*100+n),
				       list_cons((idcolumn_t) (i*100+j*10),list_new()))));
}
			     
      
/*
  returns the completed sudoku grid(s) (no 0s).
*/
char **sudoku_solve (char **grid) {
  // get the solutions
  dlx_data dlxsol = sudoku_gridtodlx(grid);
  lol_t sols = dlx_solve(dlxsol);

  // if no solutions
  if (!sols) error_handle("No solution found: invalid sudoku.");

  list_t head = lol_head(sols);
  lol_t tail = lol_tail(sols);
  // if more than one solution
  if (tail) error_handle("More than one solution: invalid sudoku.");

  // allocate memory for solution grid
  char **sol = (char **) malloc(sizeof(char *)*9);
  for(size_t i = 0; i < 9; i++)
    sol[i] = (char *) malloc(sizeof(char)*9);

  for(; head; head = list_tail(head)) {
    idrow_t id = list_head(head);
    char n = (char) (id % 10); id /= 10;
    size_t j = (size_t) (id % 10); id /= 10;
    size_t i = (size_t) (id % 10); id /= 10;
    if (id) error_handle("Invalid id for a row.");
    sol[i-1][j-1] = n;
  }

  dlx_destruct(dlxsol);

  return sol;
}

/*
  checks if a completed grid is actually a solution of a given sudoku
  grid; returns 1 if everything is ok, 0 otherwise.

  for debugging
*/
char sudoku_check (char **sol, char** grid) {
  for(size_t i = 0; i < 9; i++)
    for(size_t j = 0; j < 9; j++) {
      char n = sol[i][j];
      // if pre-filled cell does not match solution cell
      if (grid[i][j] && (n != grid[i][j])) {printf("i:%d, j:%d, prefilled\n",(int) (i+1), (int) (j+1)); return 0;}
      // check row
      for(size_t jj = 0; jj < 9; jj++)
	if(jj != j && grid[i][jj] == n) {printf("i:%d, j:%d, row\n",(int) (i+1), (int) (j+1)); return 0;}
      // check column
      for(size_t ii = 0; ii < 9; ii++)
	if(ii != i && grid[ii][j] == n) {printf("i:%d, j:%d, column\n",(int) (i+1), (int) (j+1)); return 0;}
      // check block
      size_t iblock = 3*(i/3), jblock = 3*(j/3);
      /* 
	 (iblock,jblock) is the top most left most cell of the block
	 containing (i,j)
      */
      for(size_t ii = iblock; ii < iblock+3; ii++)
	for(size_t jj = jblock; jj < jblock+3; jj++)
	  if(ii != i && jj != j && grid[ii][jj] == n) {printf("i:%d, j:%d, block\n",(int) (i+1), (int) (j+1)); printf("ii:%d, jj:%d, block\n",(int) (ii+1), (int) (jj+1)); return 0;}
    }

  // if we made it here, the solution is correct
  return 1;
}

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
