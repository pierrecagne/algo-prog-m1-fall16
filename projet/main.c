#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sudoku.h"
#include "error.h"
#include "list.h"
#include "dlx.h"

char **oneltogrid (char *line);
void optargs (char **argv, int *pos);
void check (char *pgm);
void database (char *path);

int main(int argc, char **argv) {

  /*
    path: array of path to sudoku files
    npath: number of paths given in args
  */
  char **path = malloc(sizeof(char*)*(argc-1)); int npath = 0; 

  // check arguments and their forms
  if (argc < 2) error_usage(argv[0]);
  else {
    int i = 1;
    while(i < argc)
      if (argv[i][0] == '-') optargs(argv, &i);
      else { path[npath++] = argv[i++]; }
  }
  // at least a path should be given
  if (!npath) error_usage(argv[0]);

  while(npath) {
    sudoku_print_all_solutions(sudoku_filetogrid(*path));
    path++; npath--;
  }
  
  return EXIT_SUCCESS;
}

char **oneltogrid (char *line) {
  char **grid = (char **) malloc(sizeof(char*)*9);
  for(size_t i = 0; i < 9; i++)
    grid[i] = (char *) malloc(sizeof(char)*9);

  for(size_t i = 0 ; i < 81; i++)
    if (line[i] < '0' || line[i] > '9') grid[i/9][i%9] = 0;
    else grid[i/9][i%9] = line[i] - '0';
  
  return grid;
}

void optargs (char **argv, int *pos) {
  if (argv[*pos][1] == 'h') {
    (*pos)++;
    printf("\
%s: help\n\
usage: %s [-h] [-c pgm] [-db] [file ...]\n\n\
- if -h is given, prints this help menu and quit.\n\
- if -c pgm is given, check a number of test files again the response of pgm on it.\n\
- if -db is given, file should be a database (oneline sudokus);\n\
  -db should be given as last option\
- file should be a path to a sudoku file; can be ommited only if -h or -c is given.\n",argv[0],argv[0]);
    exit(EXIT_SUCCESS);
  }
  if (argv[*pos][1] == 'c') {
    check(argv[(*pos)+1]); *pos += 2;
  }
  if (argv[*pos][1] == 'd' && argv[*pos][2] == 'b') {
    database(argv[(*pos)+1]); *pos += 1;
  }
  else error_handle ("illegal option");
  return;
}

void check (char *pgm) {
  for(int i = 1; i <= 375; i++) {
    char name[100]; sprintf(name, "test_files/test%d.sudoku", i);
    char **grid = sudoku_filetogrid(name);
    char cmd[200]; sprintf(cmd, "%s %s > tmp_out_file", pgm, name);
    system(cmd);
    char **stud = sudoku_filetogrid("tmp_out_file");
    // sudoku_print(stud);
    if (!sudoku_check(stud,grid)) {
      char msg[ERROR_MAX]; sprintf(msg,"test %d failed", i);
      error_handle(msg);
    }
  }

  printf("All test successfully passed.\n");
  exit(EXIT_SUCCESS);
}

void database (char *path) {
  FILE *db = fopen(path,"r");
  char buf[500];
  while(fgets(buf,500,db)) {
    char **grid = oneltogrid(buf);
    char **sol = sudoku_solve(grid);
    if (!sudoku_check(sol,grid)) error_handle("failure");
  }
  printf("All test passed!\n");
  exit(EXIT_SUCCESS);
}
