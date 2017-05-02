#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../list.h"
#include "common.h"
#include "tester.h"

int *dup_arr(int *array, int size) {
	int *output = calloc(size, sizeof(int));;
	for (int i = 0; i < size; i++) output[i] = array[i];
	return output;
}

void print_status(char *func_name, int status) {
	printf("%s:", func_name);
	for(int i = 4; i > ((strlen(func_name) + 1) / 8); i--) printf("\t");
	status ? printf(" BUILD \e[38;2;0;255;0mPASSED\e[m\n") : printf(" BUILD \e[38;2;255;0;0mBROKE\e[m\n");
}

#define size 10

int main() {
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, i;

	print_status("list_create", test_list_create(dup_arr(arr, size)));
	print_status("list_destroy", test_list_destroy(dup_arr(arr, size)));
	print_status("list_deepdestroy", test_list_deepdestroy(dup_arr(arr, size)));
	print_status("list_usehashmap", test_list_usehashmap(dup_arr(arr, size)));
	print_status("list_replacecmpfunc", test_list_replacecmpfunc(dup_arr(arr, size)));
	print_status("list_size", test_list_size(dup_arr(arr, size)));
	print_status("list_contains", test_list_contains(dup_arr(arr, size)));
	print_status("list_sort", test_list_sort(dup_arr(arr, size)));
	print_status("list_copy", test_list_copy(dup_arr(arr, size)));
	print_status("list_deepcopy", test_list_deepcopy(dup_arr(arr, size)));
	print_status("list_addfirst", test_list_addfirst(dup_arr(arr, size)));
	print_status("list_addlast", test_list_addlast(dup_arr(arr, size)));
	print_status("list_remove", test_list_remove(dup_arr(arr, size)));
	print_status("list_deepremove", test_list_deepremove(dup_arr(arr, size)));
	print_status("list_popfirst", test_list_popfirst(dup_arr(arr, size)));
	print_status("list_poplast", test_list_poplast(dup_arr(arr, size)));
	print_status("list_getlast", test_list_getlast(dup_arr(arr, size)));
	print_status("list_getfirst", test_list_getfirst(dup_arr(arr, size)));
	print_status("list_getitemnumfromfirst", test_list_getitemnumfromfirst(dup_arr(arr, size)));
	print_status("list_getitemnumfromlast", test_list_getitemnumfromlast(dup_arr(arr, size)));
	print_status("list_createiter", test_list_createiter(dup_arr(arr, size)));
	print_status("list_copyiter", test_list_copyiter(dup_arr(arr, size)));
	print_status("list_destroyiter", test_list_destroyiter(dup_arr(arr, size)));
	print_status("list_resetiter", test_list_resetiter(dup_arr(arr, size)));
	print_status("list_hasnext", test_list_hasnext(dup_arr(arr, size)));
	print_status("list_hasbefore", test_list_hasbefore(dup_arr(arr, size)));
	print_status("list_hasafter", test_list_hasafter(dup_arr(arr, size)));
	print_status("list_getitem", test_list_getitem(dup_arr(arr, size)));
	print_status("list_getbefore", test_list_getbefore(dup_arr(arr, size)));
	print_status("list_getafter", test_list_getafter(dup_arr(arr, size)));
	print_status("list_replaceitem", test_list_replaceitem(dup_arr(arr, size)));
	print_status("list_movenext", test_list_movenext(dup_arr(arr, size)));
	print_status("list_moveprev", test_list_moveprev(dup_arr(arr, size)));
	print_status("list_next", test_list_next(dup_arr(arr, size)));
	print_status("list_prev", test_list_prev(dup_arr(arr, size)));
	print_status("list_popnext", test_list_popnext(dup_arr(arr, size)));
	print_status("list_popprev", test_list_popprev(dup_arr(arr, size)));
	print_status("list_addnext", test_list_addnext(dup_arr(arr, size)));
	print_status("list_addprev", test_list_addprev(dup_arr(arr, size)));
	print_status("list_addafter", test_list_addafter(dup_arr(arr, size)));
	print_status("list_addbefore", test_list_addbefore(dup_arr(arr, size)));
	print_status("list_rolldown", test_list_rolldown(dup_arr(arr, size)));
	print_status("list_rollup", test_list_rollup(dup_arr(arr, size)));
	print_status("list_reverse", test_list_reverse(dup_arr(arr, size)));
	print_status("list_randomize", test_list_randomize(dup_arr(arr, size)));
	return 0;
}

/*
//	Testing functions
*/

list_t *list_inputarr(list_t *list, int *array) {
	for (int i = 0; i < size; i++) list_addlast(list, allocate_int(array[i]));
	return list;
}

// Creating and destroying list
int test_list_create(int *array) {
	free(array);
	return (list_create(compare_int)) ? 1: 0;
}
int test_list_destroy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_destroy(list);
	free(array);
	return (!list) ? 1 : 0;
}
int test_list_deepdestroy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_deepdestroy(list, destroy_int);
	free(array);
	if (!list) return 1;
	return 0;
}

// Config
int test_list_usehashmap(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_usehashmap(list);

	return 1;
}
int test_list_replacecmpfunc(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_replacecmpfunc(list, compare_string);
	free(array);
	return 1;
}

// Getting list info
int test_list_size(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	free(array);
	if (list_size(list) == size) return 1;
	return 0;
}
int test_list_contains(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	
	for (int i = 0; i < size; i++)
		if(!list_contains(list, &array[i])) {
			free(array);
			return 0;
		}
	free(array);
	return 1;
}

// Sorting list
int test_list_sort(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_sort(list);

	return 1;
}

// Copying list
int test_list_copy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_copy(list);
	return 1;
}
int test_list_deepcopy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_deepcopy(list, copy_int);

	return 1;
}

// Adding items
int test_list_addfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_addfirst(list, &array[1]);

	return 1;
}
int test_list_addlast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_addlast(list, &array[1]);

	return 1;
}

// Removing items
int test_list_remove(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_remove(list, &array[1]);

	return 1;
}
int test_list_deepremove(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_deepremove(list, &array[1], destroy_int);

	return 1;
}

// Popping items (will remove items from list)
int test_list_popfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_popfirst(list);

	return 1;
}
int test_list_poplast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_poplast(list);

	return 1;
}

// Getting the edge items of list
int test_list_getlast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_getlast(list);

	return 1;
}
int test_list_getfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_getfirst(list);

	return 1;
}

// Getting the item that is located at the num-th position
int test_list_getitemnumfromfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_getitemnumfromfirst(list, size / 2);

	return 1;
}
int test_list_getitemnumfromlast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_getitemnumfromlast(list, size / 2);

	return 1;
}

// General iterator functions
int test_list_createiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_createiter(list);

	return 1;
}
int test_list_copyiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *a, *b;
	a = list_createiter(list);
	list_copyiter(a, b);

	return 1;
}
int test_list_destroyiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_destroyiter(iter);

	return 1;
}
int test_list_resetiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_resetiter(list, iter);

	return 1;
}

// Check if current item has a node (hasprev would do the same)
int test_list_hasnext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_hasnext(iter);

	return 1;
}

// Check if iterator has node before or after
int test_list_hasbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_hasbefore(iter);

	return 1;
}
int test_list_hasafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_hasafter(iter);

	return 1;
}

// Manipulating items with iteratos
int test_list_getitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_getitem(iter);

	return 1;
}
int test_list_getbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);

	list_getbefore(iter);

	return 1;
}
int test_list_getafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_getafter(iter);

	return 1;
}
int test_list_replaceitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_replaceitem(iter, &array[1]);

	return 1;
}

// Specific iterator moving
int test_list_movenext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_movenext(iter);

	return 1;
}
int test_list_moveprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_moveprev(iter);

	return 1;
}

// Returning item then moving iterator
int test_list_next(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_next(iter);

	return 1;
}
int test_list_prev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_prev(iter);

	return 1;
}

// Popping item then moving iterator
int test_list_popnext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_popnext(list, iter);

	return 1;
}
int test_list_popprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_popprev(list, iter);

	return 1;
}

// Adding item in direction then moving iterator the same direction
int test_list_addnext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_addnext(list, iter, &array[1]);

	return 1;
}
int test_list_addprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_addprev(list, iter, &array[1]);

	return 1;
}

// Adding item in direction
int test_list_addafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_addafter(list, iter, &array[4]);

	return 1;
}
int test_list_addbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);

	list_addbefore(list, iter, &array[9]);

	return 1;
}

// List manipulations
int test_list_rolldown(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_rolldown(list);

	return 1;
}
int test_list_rollup(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_rollup(list);

	return 1;
}
int test_list_reverse(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_reverse(list);

	return 1;
}
int test_list_randomize(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_randomize(list);

	return 1;
}
