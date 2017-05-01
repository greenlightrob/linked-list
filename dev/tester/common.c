#include "common.h"
#include "../../list.h"
#include <string.h>
#include <stdlib.h>

void fatal_error(char *msg, ...) {
    fprintf (stderr, "fatal error: ");
    va_list args;
    va_start (args, msg);
    vfprintf (stderr, msg, args);
    va_end (args);
    fputc ('\n', stderr);
    exit (1);
}

int compare_int(void *a, void *b) {
	return *(int*)a - *(int*)b;
}
int compare_string(void *a, void *b) {
    return strcmp(a, b);
}
int compare_pointer(void *a, void *b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}
