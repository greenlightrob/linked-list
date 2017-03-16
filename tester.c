#include <stdio.h>
#include "list.h"

int intcompare(void *a, void *b) {
	return *(int*)a - *(int*)b;
}
/*
Functions to be tested
	+ list_t *list_create(cmpfunc_t cmpfunc);
	+ void list_destroy(list_t *list);
	+ int list_size(list_t *list);
	+ void list_addfirst(list_t *list, void *item);
	+ void list_addlast(list_t *list, void *item);
	+ void *list_popfirst(list_t *list);
	+ void *list_poplast(list_t *list);
	- int list_contains(list_t *list, void *item);
	- void list_sort(list_t *list);

	- list_iter_t *list_createiter(list_t *list);
	- void list_copy_iter(list_iter_t *a, list_iter_t *b);
	- void list_destroyiter(list_iter_t *iter);

	- int list_hasnext(list_iter_t *iter);
	- void *list_getitem(list_iter_t *iter);
	- void list_replaceitem(list_iter_t *iter, void *item);

	- void list_itermovenext(list_iter_t *iter);
	- void list_itermoveprev(list_iter_t *iter);

	- void *list_next(list_iter_t *iter);
	- void *list_prev(list_iter_t *iter);


	- void *list_popnext(list_t *list, list_iter_t *iter);
	- void *list_popprev(list_t *list, list_iter_t *iter);

	- void list_addnext(list_t *list, list_iter_t *iter, void *item);
	- void list_addprev(list_t *list, list_iter_t *iter, void *item);

// Debugging
int list_debug_countsize(list_t *list);
*/

int main() {
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i;
	printf("1\n");
	list_t *list = list_create(intcompare);
	printf("2\n");
	list_destroy(list);
	list = list_create(intcompare);
	printf("3\n");
	list_addfirst(list, &arr[1]);
	printf("4\n");
	list_poplast(list);
	if (list_size(list) != 0) printf("error in list size\n");
	list_destroy(list);
	list = list_create(intcompare);
	printf("5\n");
	for (i = 0; i < 10; i++) list_addlast(list, &(arr[i]));
	printf("6\n");
	for (i = 0; i < 10; i++) if (*(int*)list_popfirst(list) !=  i) printf("error\n");
	printf("7\n");
	if (list_size(list) != 0) printf("error in list size\n");
	printf("8\n");
	for (i = 0; i < 10; i++) list_addfirst(list, &(arr[i]));
	printf("9\n");
	for (i = 0; i < 10; i++) if (*(int*)list_poplast(list) != i) printf("error\n");
	printf("10\n");
	


	return 0;
}
