#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sudoku.h"
#include "list.h"
#include "dlx.h"

int main(int argc, char** argv) {

  char **grid = sudoku_filetogrid("sudoku_test");
  printf("Sudoku to solve:\n%s\n", sudoku_gridtostr(grid));

  /* lol_t lines = lol_new(); */
  /* for (size_t i = 0; i < 9 ; i++) { */
  /*   list_t list = list_new(); */
  /*   for (size_t j = 0; j < 9; j++) { */
  /*     if (i == 2 && j == 1) printf ("cell (2,1) is: %d\n", (int) grid[i][j]); */
  /*     list = list_cons((idrow_t) grid[i][j], list); */
  /*   } */
  /*   lines = lol_cons(list,lines); */
  /* } */

  /* printf ("\n####\n\n"); */

  /* idcolumn_t id1 = 3, id2 = 101; */
  /* list_t li = list_cons(id1,list_cons(id2,list_new())); */

  /* printf ("head: %d\n", (int) list_head(li)); */

  printf ("\n####\n\n");

  dlx_data root = dlx_new();
  for(int i = 7; i >= 1; i--)
    root = dlx_add_column((idcolumn_t) i,root);
  list_t row[6];
  row[5] = list_cons(4,list_cons(5,list_cons(7,list_new())));
  row[4] = list_cons(2,list_cons(7,list_new()));
  row[3] = list_cons(1,list_cons(4,list_new()));
  row[2] = list_cons(2,list_cons(3,list_cons(6,list_new())));
  row[1] = list_cons(1,list_cons(4,list_cons(7,list_new())));
  row[0] = list_cons(3,list_cons(5,list_cons(6,list_new())));
  for (int i = 6; i >= 1; i--)
    root = dlx_add_row((idrow_t) 11*i, row[i-1], root);
  
  dlx_print(root);

  lol_t res = dlx_solve(root);

  printf("\n###solutions:\n");
  for(; res; res = lol_tail(res)) {
    list_t li = lol_head(res);
    for(; li; li = list_tail(li))
      printf ("row:%d    ",(int) list_head(li));
    printf("\n");
  }
  
  dlx_destruct(root);
  
  return EXIT_SUCCESS;
}
