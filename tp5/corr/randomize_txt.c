
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* typedef struct buff_size_s buff_size_t; */
/* struct buff_size_s { */
/*   int nlines; */
/*   int max_line; */
/* }; */

int number_of_lines (FILE* stream) {
  fpos_t *curr = (fpos_t *) malloc(sizeof(fpos_t));
  (void) fgetpos(stream, curr); // save current position
  rewind(stream);

  int nlines = 1, c;
  while ( (c = fgetc(stream)) != EOF ) {
    if ((char) c == '\n') nlines++;
  }

  (void) fsetpos(stream, curr); // restore position
  return nlines;
}

void go_to_line (int n, FILE* stream) {
  rewind(stream);
  int nlines = 1, c;
  while ( nlines < n && (c = fgetc(stream)) != EOF ) {
    if ((char) c == '\n') nlines++;
  }
}

void copy_line (FILE* dst, FILE* src) {
  int c;
  while ( (c = fgetc(src)) != EOF ) {
    fputc(c, dst); if ((char) c == '\n') break;
  }
  if (c == EOF) fputc('\n',dst);
}

int main (int argc, char** argv) {

  // deal with args
  if (argc != 4) {
    printf ("Usage: sort [path] [output] [numbe_of_output_lines].\n\
 Exiting...\n");
    exit (EXIT_SUCCESS);
  }

  srand((unsigned int) time(NULL));
  
  char *path_in = argv[1], *path_out = argv[2];
  int num;
  if(sscanf(argv[3],"%d",&num) != 1) exit(EXIT_FAILURE);
  FILE *in = (FILE*) malloc(sizeof(FILE)), *out = (FILE*) malloc(sizeof(FILE));
  if (! (in = fopen(path_in,"r"))) {
    printf ("Failed while opening %s. Exiting...",path_in);
    exit (EXIT_FAILURE);
  }
  if (! (out = fopen(path_out,"w"))) {
    printf ("Failed while opening %s. Exiting...",path_in);
    exit (EXIT_FAILURE);
  }
  int nol = number_of_lines(in), rl;
  if (nol < num) exit (EXIT_FAILURE);
  for (int i = 0; i < num; i++) {
    printf ("Selecting line %d of %d.\n",  rl = 1+(rand()%nol), nol);
    go_to_line(rl,in);
    copy_line(out,in);
  }

  (void) fclose(in); (void) fclose(out);
    
  return EXIT_SUCCESS;
}
