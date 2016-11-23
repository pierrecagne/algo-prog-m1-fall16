/*
  fopen takes the file path as a string and the opening mode that
  could be multiple thing: for our use, we just consider mode to be
  "r", opening the file in read-only mode.

  It returns a pointeur to a FILE structure, that we shall consider
  opaque.

  E.g.: FILE* f = fopen("path/to/my/file", "r");
*/
FILE* fopen (const char* path, const char* mode);

/*
  fgetc takes a pointer to a FILE and returns either a character just
  read in the file f or EOF, a constant meaning the End Of the File is
  reached.

  Beware that, when it does returns a character, it casts it to an
  int.

  E.g. : if( (c = fgetc(f)) != EOF ) printf("%c", (char) c);
*/
int fgetc (FILE* f);

/*
  fgets takes a string s, a buffer length size and a pointer to a FILE
  f; it reads in f a string of length size-1 (stopping to the first
  '\n' or EOF if encountered) and puts it inside s. It writes a '\0'
  as the last character of s. It returns s if everything went right
  and NULL if not or if EOF is encountered before reading anything.

  E.g. : char s[10]; if ( fgets(s,10,f) != NULL ) printf("%s",s);
*/
char* fgets (char* s, int size, FILE* f);

/*
  rewind puts the current position in the file back to the beginning
  of the file pointed by f.

  It behaves like closing (see below) and reopening the file.
*/
void rewind (FILE* f);

/*
  fclose frees the memory allocated for the FILE structure pointed by
  f; it returns 0 upon success (and something else upon failure we are
  not interested in here).
*/
int fclose(FILE* f);
