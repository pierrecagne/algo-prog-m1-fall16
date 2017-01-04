/*
  file: dlx.c
  updated: 03/01/2017
  author: pierre cagne

  this is the very core of the solver; here we define the structure
  containing the data of the matrix representing a constraint
  satisfaction problem as defined in the project; it also implements
  Knuth's algorithm X.
*/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "dlx.h"
#include "error.h"

// cells represent 1s in the matrix representation of a constraint
// satisfaction problem
struct dlx_cell_s {
  struct dlx_cell_s *up, *down; // prev and next in column
  struct dlx_cell_s *left, *right; // prev and next in row

  struct dlx_column_s *column; // pointer to cell's own column
  idrow_t idrow; // identifier of cell's own row
} dlx_cell_t;


// column headers are 'entry points' for columns of the matrix
struct dlx_column_s {
  struct dlx_column_s *left, *right; // prev and next in headers
  
  struct dlx_cell_s head; // each header contains a cell
  /*
    the head of a column will have NULL left and right fields, and 0
    as idrow; it column is of course the header itself.
  */
  size_t len; // number of ones in the column
  idcolumn_t idcol; // identifier of the column
  /* 
     /!\ Important: a zero idcol will indicate the root /!\ 
  */
} dlx_column_t;

/*
  every function declare with the word 'static' is only usable by
  function inside this file; hence, we can use any name for those
  static functions without any care of future use of this library; in
  particular we delete the dlx_ prefix for those.
*/

// prototypes; see the actual functions for documentation
static dlx_cell_ptr allocate_cell (idrow_t idrow);
static dlx_column_ptr allocate_column (idcolumn_t idcol);
static dlx_column_ptr search (idcolumn_t idcol, dlx_data root
			      );
static void vcover_cell (dlx_cell_ptr cell);
static void hcover_cell (dlx_cell_ptr cell);
static void hcover_header (dlx_column_ptr column);
static void cover_column (dlx_column_ptr column);
static void vuncover_cell (dlx_cell_ptr cell);
static void huncover_cell (dlx_cell_ptr cell);
static void huncover_header (dlx_column_ptr column);
static void uncover_column (dlx_column_ptr column);
static void vinsert_cell (dlx_cell_ptr cell, dlx_cell_ptr prev);
static void hinsert_cell (dlx_cell_ptr cell, dlx_cell_ptr prev);
static void hinsert_header (dlx_column_ptr column, dlx_column_ptr prev);

/*
  returns a pointer to a new cell with specified idrow, whose fields
  up,down,left,right all point to itself and column orphelin
*/
static dlx_cell_ptr allocate_cell (idrow_t idrow) {
  dlx_cell_ptr new = (dlx_cell_ptr) malloc(sizeof(dlx_cell_t));
  new->up = new; new->down = new; new->left = new; new->right = new;
  new->idrow = idrow;
  new->column = NULL;

  return new;
}

/*
  returns a pointer to a new header with specified idcol, whose
  fields left and right point to itself.
*/
static dlx_column_ptr allocate_column (idcolumn_t idcol) {
  dlx_column_ptr new = (dlx_column_ptr) malloc(sizeof(dlx_column_t));
  new->left = new; new->right = new;
  new->idcol = idcol;
  new->len = 0;

  new->head.left = NULL; new->head.right = NULL;
  new->head.up = &(new->head); new->head.down = &(new->head);
  new->head.idrow = 0;
  new->head.column = new;

  return new;
}

/*
  returns a pointer to the column header in root having idcol as
  identifier; if not found, returns NULL.
*/
static dlx_column_ptr search (idcolumn_t idcol, dlx_data root) {
  for(dlx_column_ptr p = root->right; p != root; p = p->right)
    if (p->idcol == idcol) return p;
  return NULL;
}

/*
  cover a cell in its vertical (circular doubly linked) list
*/
static void vcover_cell (dlx_cell_ptr cell) {
  cell->up->down = cell->down; cell->down->up = cell->up;
  return;
}

/*
  cover a cell in its horizontal (circular doubly linked) list
*/
static void hcover_cell (dlx_cell_ptr cell) {
  cell->left->right = cell->right; cell->right->left = cell->left;
  return;
}

/*
  cover a column header in its horizontal (circular doubly linked) list
*/
static void hcover_header (dlx_column_ptr column) {
  column->left->right = column->right; column->right->left = column->left;
  return;
}

/*
  cover a column in Knuth's sense: h-cover the header and v-cover each
  cell in the same row as some cell of the column.
*/
static void cover_column (dlx_column_ptr column) {
  hcover_header(column);
  for(dlx_cell_ptr p = column->head.down; p != &(column->head); p = p->down)
    for(dlx_cell_ptr q = p->right; q != p; q = q->right) {
      vcover_cell(q); q->column->len--;
    }
  return;
}

/*
  uncover a cell in its vertical (circular doubly linked) list
*/
static void vuncover_cell (dlx_cell_ptr cell) {
  cell->up->down = cell; cell->down->up = cell;
  return;
}

/*
  uncover a cell in its horizontal (circular doubly linked) list
*/
static void huncover_cell (dlx_cell_ptr cell) {
  cell->left->right = cell; cell->right->left = cell;
  return;
}

/*
  uncover a column header in its horizontal (circular doubly linked) list
*/
static void huncover_header (dlx_column_ptr column) {
  column->left->right = column; column->right->left = column;
  return;
}

/*
  uncover a column in Knuth's sense: h-uncover the header and v-uncover each
  cell in the same row as some cell of the column.
*/
static void uncover_column (dlx_column_ptr column) {
  for(dlx_cell_ptr p = column->head.up; p != &(column->head); p = p->up)
    for(dlx_cell_ptr q = p->left; q != p; q = q->left) {
      vuncover_cell(q); q->column->len++;
    }
  huncover_header(column);
  return;
}

/*
  insert a cell vertically under prev
*/
static void vinsert_cell (dlx_cell_ptr cell, dlx_cell_ptr prev) {
  cell->up = prev; cell->down = prev->down;
  vuncover_cell(cell);
  return;
}

/*
  insert a cell horizontally right og prev
*/
static void hinsert_cell (dlx_cell_ptr cell, dlx_cell_ptr prev) {
  cell->left = prev; cell->right = prev->right;
  huncover_cell(cell);
  return;
}

/*
  insert a column header horizontally right of prev
*/
static void hinsert_header (dlx_column_ptr column, dlx_column_ptr prev) {
  column->left = prev; column->right = prev->right;
  huncover_header(column);
  return;
}

/*
  creates a new empty dlx data.
*/
dlx_data dlx_new () {
  return allocate_column(0);
} 

/*
  add a new empty column with specified identifier to a dlx data,
  modifying it *in place*; returns the modified dlx data.
*/
dlx_data dlx_add_column (idcolumn_t id, dlx_data root) {
  hinsert_header(allocate_column(id), root);
  return root;
}

/*
  add a new row with specified identifier and with 1s in columns
  specified by a list of column identifiers to a dlx data, modifying
  it *in place*; returns the modified dlx data.
*/
// auxiliary function, defined below
static void add_row_recurse (idrow_t id, list_t ones, dlx_data root, dlx_cell_ptr tmp); 

dlx_data dlx_add_row (idrow_t id, list_t ones, dlx_data root) {
  dlx_cell_ptr tmp = allocate_cell(id);
  add_row_recurse(id,ones,root,tmp);
  hcover_cell(tmp); free(tmp);
  return root;
}

static void add_row_recurse (idrow_t id, list_t ones, dlx_data root, dlx_cell_ptr tmp) {
  if (!ones) return; // init case

  dlx_column_ptr found = search(list_head(ones), root);
  // handle error if column not found
  if (!found) {
    char msg[ERROR_MAX];
    (void) sprintf(msg, "Error building DLX problem: column id %d not found", list_head(ones));
    error_handle(msg);
  }
  dlx_cell_ptr new = allocate_cell(id);
  new->column = found; 
  hinsert_cell(new,tmp); vinsert_cell(new,&(found->head));
  found->len++;
  return add_row_recurse(id,list_tail(ones),root,tmp);
}

/*
  destructs a dlx data entirely, deallocating all cells and column
  headers previously allocated on the heap.
*/
// auxialiary, defined below.
static void destruct_column (dlx_column_ptr column);

void dlx_destruct (dlx_data root) {
  if (root->right == root) // if no column left
    return;

  destruct_column(root->right);
  return dlx_destruct(root);
}

static void destruct_column (dlx_column_ptr column) {
  if (!column->len) { // if no element left in column
    /* printf("deleting column %d\n",(int) (column->idcol)); */
    hcover_header(column);
    free(column);
    return;
  }

  dlx_cell_ptr todelete = column->head.down;
  /* printf("\nstill %d cells in this column.\n", (int) column->len); */
  /* printf("deleting cell in row %d and column %d...\n", todelete->idrow, column->idcol); */
  vcover_cell(todelete); hcover_cell(todelete);
  /* printf("    cell covered..."); */
  free(todelete);
  /* printf("    cell deleted!\n"); */
  column->len--;

  /* printf("###\n");dlx_print(column->left);printf("\n"); */
  
  return destruct_column(column);
}

/*
  returns the list of all solutions to a constraint satisfaction
  problem in dlx data form; every solution takes the form of a list of
  row identifiers; this is algorithm X.
*/

//auxiliary recursive function, see definition below
static void solve_recurse(dlx_data root, list_t curr_sol, lol_t *sols);

lol_t dlx_solve (dlx_data root) {
  lol_t solutions = lol_new();
  solve_recurse(root, list_new(), &solutions);
  return solutions;
}

static void solve_recurse(dlx_data root, list_t curr_sol, lol_t *sols) {
  if (root->right == root) { // if no more constraints
    *sols = lol_cons(curr_sol, *sols); // add current solution to set of solutions
    return;
  }

  // else choose column with minimal length
  dlx_column_ptr pmin = root->right; size_t min = pmin->len;
  for(dlx_column_ptr p = pmin; p != root; p = p->right)
    if (p->len < min) { pmin = p; min = p->len; }

  cover_column(pmin);
  for(dlx_cell_ptr p = pmin->head.down; p != &(pmin->head); p = p->down) {
    for(dlx_cell_ptr q = p->right; q != p; q = q->right) // cover all conflicting lines
      cover_column(q->column);
    solve_recurse(root, list_cons(p->idrow,curr_sol), sols); // recursive call
    for(dlx_cell_ptr q = p->left; q != p; q = q->left) // uncover what have been covered
      uncover_column(q->column);
  }
  uncover_column(pmin);
  return;
}


/*
  for debugging only; prints out the dlx data
*/
void dlx_print (dlx_data root) {
  for(dlx_column_ptr c = root->right; c != root; c = c->right) {
    printf("Column id: %d\n    ", c->idcol);
    for(dlx_cell_ptr p = c->head.down; p != &(c->head); p = p->down)
      printf(":%d    ", p->idrow);
    printf("\n");
  }
  return;
}
