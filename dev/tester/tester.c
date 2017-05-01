#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../../list.h"

int compare_ints(void *a, void *b) {
	return *(int*)a - *(int*)b;
}
void *create_int(int in) {
	int *ptr = malloc(sizeof(int));
	*ptr = in;
	return ptr;
}

void print_int(void *number) {
	printf("%d\n", *(int*)number);
}

void variadic_print_int(list_t *list, void *a, ...) {

	va_list args;
	va_start(args, 1);
	printf("argument is: ");
	printf("%d\n", va_arg(args, int));
	va_end(args);
}

int main() {
	list_t *list = list_create(compare_ints);
	for (int i = 0; i < 10; i++) list_addlast(list, create_int(i));
	for (int i = 0; i < 10; i++) print_int(list_poplast(list));

	void *a;
	
	variadic_print_int(list, a);
}
