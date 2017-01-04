/*
  file: dlx.h
  updated: 03/01/2017
  author: pierre cagne

  header file for dlx.c; this is the very core of the solver; here we
  define the structure containing the data of the matrix representing
  a constraint satisfaction problem as defined in the project; it also
  implements Knuth's algorithm X.
*/


#ifndef DLX_H
#define DLX_H

#include "list.h"

// type for columns identifiers
/*
  Remark: this is important that is is just an alias for idrow_t if we
  want to be able to use list_t as the type of list of idcolumn_t
  objects (cf. argument of type list_t in dlx_add_row).
*/
typedef idrow_t idcolumn_t;

// type for the cells of the dlx data
typedef struct dlx_cell_s* dlx_cell_ptr;

// type for the column headers
// dlx data (more precisely their root) are peculiar column headers
typedef struct dlx_column_s* dlx_column_ptr;
typedef dlx_column_ptr dlx_data;

/*
  creates a new empty dlx data.
*/
dlx_data dlx_new ();

/*
  add a new empty column with specified identifier to a dlx data,
  modifying it *in place*; returns the modified dlx data.
*/
dlx_data dlx_add_column (idcolumn_t id, dlx_data root);

/*
  add a new row with specified identifier and with 1s in columns
  specified by a list of column identifiers to a dlx data, modifying
  it *in place*; returns the modified dlx data.
*/
dlx_data dlx_add_row (idrow_t id, list_t ones, dlx_data root);

/*
  destructs a dlx data entirely, deallocating all cells and column
  headers previously allocated on the heap.
*/
void dlx_destruct (dlx_data root);

/*
  returns the list of all solutions to a constraint satisfaction
  problem in dlx data form; every solution takes the form of a list of
  row identifiers; this is algorithm X.
*/
lol_t dlx_solve (dlx_data root);

/*
  debugging
*/
void dlx_print (dlx_data root);

#endif
