 /* print the elements of an array of given size ; separate elements by spaces and print a newline at the end */
void pp_array (int size, int *array);

/* swap elements of index i and index j in an array */
void swap (int i, int j, int *array);

/* copy the array src into the array dest ; both should have the same size ; notice the 'const' keyword */
void copy_array (int size, int *dest, const int *src);

/* reverse the order of src to put into dest ; both should have the same size */
void reverse_array (int size, int *dest, const int *src);

/* return the index of the maximum or minimum of an array of given size */
int max (int size, int *array);
int min (int size, int *array);
