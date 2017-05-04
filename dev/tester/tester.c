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
	int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// List functions
	print_status("list_create", test_list_create(dup_arr(arr, size)));

	print_status("list_destroy", test_list_destroy(dup_arr(arr, size)));
	print_status("list_deepdestroy", test_list_deepdestroy(dup_arr(arr, size)));

	print_status("list_copy", test_list_copy(dup_arr(arr, size)));
	print_status("list_deepcopy", test_list_deepcopy(dup_arr(arr, size)));

	print_status("list_addfirst", test_list_addfirst(dup_arr(arr, size)));
	print_status("list_addlast", test_list_addlast(dup_arr(arr, size)));

	print_status("list_getfirst", test_list_getfirst(dup_arr(arr, size)));
	print_status("list_getlast", test_list_getlast(dup_arr(arr, size)));
	print_status("list_replaceitem", test_list_replaceitem(dup_arr(arr, size)));

	print_status("list_popitem", test_list_popitem(dup_arr(arr, size)));
	print_status("list_popfirst", test_list_popfirst(dup_arr(arr, size)));
	print_status("list_poplast", test_list_poplast(dup_arr(arr, size)));

	print_status("list_removeitem", test_list_removeitem(dup_arr(arr, size)));
	print_status("list_removefirst", test_list_removefirst(dup_arr(arr, size)));
	print_status("list_removelast", test_list_removelast(dup_arr(arr, size)));

	print_status("list_replacecmpfunc", test_list_replacecmpfunc(dup_arr(arr, size)));
	print_status("list_size", test_list_size(dup_arr(arr, size)));
	print_status("list_contains", test_list_contains(dup_arr(arr, size)));
	print_status("list_sort", test_list_sort(dup_arr(arr, size)));

	// Iterator functions
	print_status("list_createiter", test_list_createiter(dup_arr(arr, size)));
	print_status("list_destroyiter", test_list_destroyiter(dup_arr(arr, size)));
	print_status("list_copyiter", test_list_copyiter(dup_arr(arr, size)));
	print_status("list_resetiter", test_list_resetiter(dup_arr(arr, size)));

	print_status("list_hasnext", test_list_hasnext(dup_arr(arr, size)));
	print_status("list_hasbefore", test_list_hasbefore(dup_arr(arr, size)));
	print_status("list_hasafter", test_list_hasafter(dup_arr(arr, size)));

	print_status("list_movenext", test_list_movenext(dup_arr(arr, size)));
	print_status("list_moveprev", test_list_moveprev(dup_arr(arr, size)));
	print_status("list_next", test_list_next(dup_arr(arr, size)));
	print_status("list_prev", test_list_prev(dup_arr(arr, size)));

	print_status("list_addafter", test_list_addafter(dup_arr(arr, size)));
	print_status("list_addbefore", test_list_addbefore(dup_arr(arr, size)));

	print_status("list_getitem", test_list_getitem(dup_arr(arr, size)));
	print_status("list_getbefore", test_list_getbefore(dup_arr(arr, size)));
	print_status("list_getafter", test_list_getafter(dup_arr(arr, size)));
	print_status("list_replaceiteritem", test_list_replaceiteritem(dup_arr(arr, size)));

	print_status("list_popnext", test_list_popnext(dup_arr(arr, size)));
	print_status("list_popprev", test_list_popprev(dup_arr(arr, size)));
	 
	print_status("list_removenext", test_list_removenext(dup_arr(arr, size)));
	print_status("list_removeprev", test_list_removeprev(dup_arr(arr, size)));

	// Specialized list functions
	print_status("list_rolldown", test_list_rolldown(dup_arr(arr, size)));
	print_status("list_rollup", test_list_rollup(dup_arr(arr, size)));
	print_status("list_reverse", test_list_reverse(dup_arr(arr, size)));
	print_status("list_randomize", test_list_randomize(dup_arr(arr, size)));
	print_status("list_swapitems", test_list_swapitems(dup_arr(arr, size)));
	print_status("list_isequal", test_list_isequal(dup_arr(arr, size)));
	print_status("list_hassameitems", test_list_hassameitems(dup_arr(arr, size)));

	print_status("list_activatehashmap", test_list_activatehashmap(dup_arr(arr, size)));
	print_status("list_deactivatehashmap", test_list_deactivatehashmap(dup_arr(arr, size)));

	print_status("list_activateindex", test_list_activateindex(dup_arr(arr, size)));
	print_status("list_deactivateindex", test_list_deactivateindex(dup_arr(arr, size)));
	print_status("list_getitembyidx", test_list_getitembyidx(dup_arr(arr, size)));
	print_status("list_getidxbyitem", test_list_getidxbyitem(dup_arr(arr, size)));
	print_status("list_replaceitembyidx", test_list_replaceitembyidx(dup_arr(arr, size)));
	print_status("list_swapidxs", test_list_swapidxs(dup_arr(arr, size)));

	print_status("list_activatepriority", test_list_activatepriority(dup_arr(arr, size)));
	print_status("list_deactivatepriority", test_list_deactivatepriority(dup_arr(arr, size)));
	print_status("list_replaceprioritycmpfunc", test_list_replaceprioritycmpfunc(dup_arr(arr, size)));
	print_status("list_poppriority", test_list_poppriority(dup_arr(arr, size)));
	print_status("list_getpriority", test_list_getpriority(dup_arr(arr, size)));
	return 0;
}

/*
//	Test functions
*/

list_t *list_inputarr(list_t *list, int *array) {
	for (int i = 0; i < size; i++) list_addlast(list, allocate_int(array[i]));
	return list;
}

/*
//	List functions
*/

// Create list
int test_list_create(int *array) {

	// Testing funcion call
	list_t *list = list_create(compare_int);

	int result = (list) ? 1 : 0;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Destroy list
int test_list_destroy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_t *copy = list_copy(list);

	// Testing funcion call
	list_destroy(list);

	int result = (!list) ? 1 : 0;

	// Freeinf memory
	list_deepdestroy(copy, destroy_int);
	free(array);		
	return result;
}
int test_list_deepdestroy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	
	// Testing funcion call
	list_deepdestroy(list, destroy_int);

	int result = (!list) ? 1 : 0;

	// Freeing memory
	free(array);
	return result;
}
// Copy list
int test_list_copy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int result = 1;

	// Testing funcion call
	list_t *copylist = list_copy(list);

	while(list_size(list) > 2 && list_size(copylist) > 2) {
		if (result == 1) result = (compare_int(list_popfirst(list), list_popfirst(copylist)) != 0) ? 0 : 1;
	}
	list_deepdestroy(list, destroy_int);
	int val = *(int *)list_poplast(copylist);
	if (result == 1) result = (val == 9) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(copylist, destroy_int);
	free(array);
	return result;
}
int test_list_deepcopy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int result = 1;

	// Testing funcion call
	list_t *copylist = list_deepcopy(list, copy_int);
	
	while(list_size(list) > 2 && list_size(copylist) > 2) {
		if (result == 1 )result =  (compare_int(list_popfirst(list), list_popfirst(copylist)) != 0) ? 0 : 1;
	}

	list_deepdestroy(list, destroy_int);
	int val = *(int *)list_poplast(copylist);
	if (result == 1) result = (val != 9) ? 0 : 1; 

	// Freeing memory
	list_deepdestroy(copylist, destroy_int);
	free(array);
	return result;
}
// Add item
int test_list_addfirst(int *array) {
	list_t *list = list_create(compare_int);

	// Testing funcion call
	list_addfirst(list, &array[1]);

	int result = (*(int *)list_popfirst(list) != array[1]) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_addlast(int *array) {
	list_t *list = list_create(compare_int);

	// Testing funcion call
	list_addlast(list, &array[1]);

	int result = (*(int *)list_popfirst(list) != array[1]) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Get and replace item
int test_list_getfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	int result = (*(int *)list_getfirst(list) != 0) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_getlast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	int result = (*(int *)list_getlast(list) != 9) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_replaceitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int result = 0;

	// Testing funcion call
	list_replaceitem(list, &array[1], &array[4]);

	result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Pop item
int test_list_popitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	list_popitem(list, &array[5]);

	int result = (list_contains(list, allocate_int(5))) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_popfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	list_popfirst(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_poplast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	list_poplast(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Remove item
int test_list_removeitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	list_removeitem(list, &array[2], destroy_int);

	int result = (!list_contains(list, allocate_int(2))) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_removefirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	list_removefirst(list, destroy_int);

	int result = (!list_contains(list, allocate_int(0))) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_removelast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing funcion call
	list_removelast(list, destroy_int);

	int result = (!list_contains(list, allocate_int(9))) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Genereal list functions
int test_list_replacecmpfunc(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	int cmpres_int = list_contains(list, &array[5]);

	// Testing funcion call
	list_replacecmpfunc(list, compare_null);

	int cmpres_null = list_contains(list, &array[5]);
	int result = (!cmpres_int || cmpres_null) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}

int test_list_size(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int result = 1;

	// Testing function call
	for (int i = 0; i < size; i++, list_poplast(list)) if (result == 1) result = (list_size(list) != size - i) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_contains(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int result = 1;
	
	for (int i = 0; i < size; i++) {

		// Testing function call
		result = (!list_contains(list, &array[i]) && result == 1) ? 0 : 1;

	}

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}

int test_list_sort(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_sort(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}

/*
//	Iterator functions
*/

// Create iterator
int test_list_createiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);

	// Testing function call
	int result = (list_createiter(list)) ? 1: 0;

	return result;
}
int test_list_destroyiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_destroyiter(iter);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_copyiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter_a, *iter_b;
	iter_a = list_createiter(list);
	iter_b = list_createiter(list);
	list_movenext(iter_a);
	list_movenext(iter_a);

	// Testing function call
	list_copyiter(iter_a, iter_b);

	int result = (*(int *)list_getitem(iter_a) != *(int *)list_getitem(iter_b)) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_resetiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_resetiter(iter);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Check wether iterator has a node
int test_list_hasnext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	int result = (!list_hasnext(iter)) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_hasbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);

	// Testing function call
	int result = (!list_hasbefore(iter)) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_hasafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	int result = (!list_hasafter(iter)) ? 0 : 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Iterator manipulations
int test_list_movenext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	// Testing function call
	list_movenext(iter);

	int result = (*(int *)list_getitem(iter) != 1) ? 0 : 1;
	
	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}	
int test_list_moveprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	list_movenext(iter);
	list_movenext(iter);

	// Testing function call
	list_moveprev(iter);

	int result = (*(int *)list_getitem(iter) != 1) ? 0 : 1;
	
	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}	
int test_list_next(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	// Testing function call
	int result = (*(int *)list_next(iter) != 0) ? 0 : 1;
	
	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}	
int test_list_prev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	list_movenext(iter);

	// Testing function call
	list_prev(iter);

	int result = (*(int *)list_next(iter) != 1) ? 0 : 1;
	
	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}	
// Add item with iterator
int test_list_addbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);
	
	// Testing function call
	list_addbefore(iter, allocate_int(11));

	int result = (*(int *)list_getfirst(list) != 11) ? 0 : 1;
	
	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}	
int test_list_addafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	// Testing function call
	list_addafter(iter, &array[4]);

	int result = 1;
	
	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}	
// Get and replace item with iterator
int test_list_getitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_getitem(iter);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_getbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);

	// Testing function call
	list_getbefore(iter);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_getafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_getafter(iter);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_replaceiteritem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_replaceiteritem(iter, &array[5]);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Pop item with iterator
int test_list_popnext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	// Testing function call
	list_popnext(iter);

	int result = 1;
	
	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_popprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_popprev(iter);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Remove item, then move iterator
int test_list_removenext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_removenext(iter, destroy_int);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_removeprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	// Testing function call
	list_removeprev(iter, destroy_int);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}

/*
//	Specialized list functions
*/

// Specialized list manipulations
int test_list_rolldown(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_rolldown(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_rollup(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_rollup(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_reverse(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_reverse(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_randomize(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_randomize(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_swapitems(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_swapitems(list, allocate_int(1), allocate_int(9));

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_isequal(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_t *list2 = list_copy(list);

	// Testing function call
	list_isequal(list, list2);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_hassameitems(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_t *list2 = list_copy(list);

	// Testing function call
	list_hassameitems(list, list2);
	
	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Initialize hashmap
int test_list_activatehashmap(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_activatehashmap(list, int_to_str);

	int result = 1;

	// Freeing memory
	list_deactivatehashmap(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_deactivatehashmap(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatehashmap(list, int_to_str);

	// Testing function call
	list_deactivatehashmap(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Index functions
int test_list_activateindex(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_activateindex(list);

	int result = 1;

	// Freeing memory
	list_deactivateindex(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_deactivateindex(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);

	// Testing function call
	list_deactivateindex(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_getitembyidx(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);

	// Testing function call
	list_getitembyidx(list, 4);

	int result = 1;

	// Freeing memory
	list_deactivateindex(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_getidxbyitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);

	// Testing function call
	list_getidxbyitem(list, allocate_int(7));

	int result = 1;

	// Freeing memory
	list_deactivateindex(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_replaceitembyidx(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);

	// Testing function call
	list_replaceitembyidx(list, allocate_int(3), 4);

	int result = 1;

	// Freeing memory
	list_deactivateindex(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_swapidxs(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);

	// Testing function call
	list_swapidxs(list, allocate_int(4), allocate_int(5));

	int result = 1;

	// Freeing memory
	list_deactivateindex(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
// Priority functions
int test_list_activatepriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// Testing function call
	list_activatepriority(list);

	int result = 1;

	// Freeing memory
	list_deactivatepriority(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_deactivatepriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);

	// Testing function call
	list_deactivatepriority(list);

	int result = 1;

	// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_replaceprioritycmpfunc(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);

	// Testing function call
	list_replaceprioritycmpfunc(list, compare_string);

	int result = 1;

	// Freeing memory
	list_deactivatepriority(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_poppriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);

	// Testing function call
	list_poppriority(list);

	int result = 1;

	// Freeing memory
	list_deactivatepriority(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
int test_list_getpriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);

	// Testing function call
	list_getpriority(list);

	int result = 1;

	// Freeing memory
	list_deactivatepriority(list);
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}
