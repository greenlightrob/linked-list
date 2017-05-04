#ifndef common_h
#define common_H

#include <stdio.h>
#include <stdarg.h>
#include "../../list.h"

// Print error message and exit program
void fatal_error(char *msg, ...);

// Generic compare functions
typedef int (*cmpfunc_t)(void *, void *);
typedef void *(*copyfunc_t)(void *);
typedef void (*destroy_t)(void *);

void *copy_int(void *input);
void destroy_int(void *input);

// Type specific compare functions
int compare_int(void *a, void *b);
int compare_string(void *a, void *b);
int compare_pointer(void *a, void *b);
int compare_null(void *a, void *b);

// strfunc
unsigned char *int_to_str(void *a);

int *allocate_int(int input);
char *allocate_string(char *input);
#endif
