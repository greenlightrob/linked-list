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

	print_status("list_addbefore", test_list_addbefore(dup_arr(arr, size)));
	print_status("list_addafter", test_list_addafter(dup_arr(arr, size)));

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
	int result = 1;										// Init
												
	list_t *list = list_create(compare_int); 			// Testing funcion call
	result = (list) ? 1 : 0;					
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);								
	return result;								
}												
// Destroy list									
int test_list_destroy(int *array) {				
	int result = 1;										// Init	
	list_t *list = list_create(compare_int);	
	list_inputarr(list, array);					
													
	list_destroy(list);									// Testing funcion call						
	result = (!list_size(list)) ? 1 : 0;					
													
	free(array);										// Freeing memory							
	return result;								
}													
int test_list_deepdestroy(int *array) {			
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_deepdestroy(list, destroy_int); 				// Testing funcion call
	result = (!list_size(list)) ? 1 : 0;
													
	return result;
}													
// Copy list
int test_list_copy(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_t *copylist = list_copy(list); 				// Testing funcion call
	while(list_size(list) > 2 && list_size(copylist) > 2) {
		int cmpres = compare_int(list_popfirst(list), list_popfirst(copylist));
		if (cmpres != 0) result = 0;
	}
	list_destroy(list);
	int val = *(int *)list_poplast(copylist);
	if (val != 9) result = 0;
													
	list_deepdestroy(copylist, destroy_int); 			// Freeing memory
	free(array);
	return result;
}													
int test_list_deepcopy(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int), *copy;
	list_inputarr(list, array);
													
	copy = list_deepcopy(list, copy_int); 				// Testing funcion call
	while(list_size(list) > 2 && list_size(copy) > 2) {
		int cmpres = compare_int(list_popfirst(list), list_popfirst(copy));
		if (cmpres != 0) result = 0;
	}
													
	list_deepdestroy(list, destroy_int);
	int val = *(int *)list_poplast(copy);
	if (val != 9) result = 0;
													
	list_deepdestroy(copy, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Add item
int test_list_addfirst(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
													
	list_addfirst(list, &array[1]); 					// Testing funcion call
	result = (*(int *)list_popfirst(list) != array[1]) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_addlast(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
													
	list_addlast(list, &array[1]); 						// Testing funcion call
	result = (*(int *)list_popfirst(list) != array[1]) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Get and replace item
int test_list_getfirst(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	result = (*(int *)list_getfirst(list) != 0) ? 0 : 1;// Testing funcion call
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_getlast(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	result = (*(int *)list_getlast(list) != 9) ? 0 : 1;	// Testing funcion call
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_replaceitem(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	void *item_a = allocate_int(1);
	void *item_b = allocate_int(4);
													
	list_replaceitem(list, item_a, item_b); 			// Testing funcion call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Pop item
int test_list_popitem(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_popitem(list, &array[5]); 						// Testing funcion call
	result = (list_contains(list, allocate_int(5))) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_popfirst(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_popfirst(list); 								// Testing funcion call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_poplast(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_poplast(list); 								// Testing funcion call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Remove item
int test_list_removeitem(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int *item = allocate_int(2);
													
	list_removeitem(list, item, destroy_int); 			// Testing funcion call
	result = (list_contains(list, item)) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_removefirst(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int *item = allocate_int(0);
													
	list_removefirst(list, destroy_int); 				// Testing funcion call
	result = (list_contains(list, item)) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_removelast(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int *item = allocate_int(9);
													
	list_removelast(list, destroy_int); 				// Testing funcion call
	result = (list_contains(list, item)) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Genereal list functions
int test_list_replacecmpfunc(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int cmpres_int = list_contains(list, &array[5]);
													
	list_replacecmpfunc(list, compare_null); 			// Testing funcion call
	int cmpres_null = list_contains(list, &array[5]);
	result = (!cmpres_int || cmpres_null) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
													
int test_list_size(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	for (int i = 0; i < size; i++, list_poplast(list)) {
		if (list_size(list) != size - i) result = 1; 	// Testing function call
	}
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_contains(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);			
	list_inputarr(list, array);							
														
	for (int i = 0; i < size; i++) {					
		if (!list_contains(list, &array[i])) result = 1;// Testing function call
	}
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
													
int test_list_sort(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_sort(list); 									// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
													
/*													
//	Iterator functions
*/													
													
// Create iterator
int test_list_createiter(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	result = (list_createiter(list)) ? 1: 0; 			// Testing function call
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_destroyiter(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_destroyiter(iter); 							// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_copyiter(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter_a, *iter_b;
	iter_a = list_createiter(list);
	iter_b = list_createiter(list);
	list_movenext(iter_a);
	list_movenext(iter_a);
													
	list_copyiter(iter_a, iter_b); 						// Testing function call
	result = (*(int *)list_getitem(iter_a) != *(int *)list_getitem(iter_b)) ? 0 : 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_resetiter(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_resetiter(iter); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Check wether iterator has a node
int test_list_hasnext(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	result = (!list_hasnext(iter)) ? 0 : 1; 			// Testing function call
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_hasbefore(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);
													
	result = (!list_hasbefore(iter)) ? 0 : 1; 			// Testing function call
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_hasafter(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	result = (!list_hasafter(iter)) ? 0 : 1; 			// Testing function call
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Iterator manipulations
int test_list_movenext(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
														
	list_movenext(iter); 								// Testing function call
	result = (*(int *)list_getitem(iter) != 1) ? 0 : 1;
	
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}														
int test_list_moveprev(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);
	list_movenext(iter);
													
	list_moveprev(iter); 								// Testing function call
	result = (*(int *)list_getitem(iter) != 1) ? 0 : 1;
	
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}														
int test_list_next(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	result = (*(int *)list_next(iter) != 0) ? 0 : 1; 	// Testing function call
	
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}														
int test_list_prev(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);
	list_movenext(iter);
													
	list_prev(iter); 									// Testing function call
	result = (*(int *)list_next(iter) != 1) ? 0 : 1;
	
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}														
// Add item with iterator
int test_list_addbefore(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);
														
	list_addbefore(iter, allocate_int(11)); 			// Testing function call
	list_moveprev(iter);
	result = (*(int *)list_prev(iter) != 11) ? 0 : 1;
														
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}														
int test_list_addafter(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
														
	list_addafter(iter, allocate_int(4)); 				// Testing function call
	result = 1;
														
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}														
// Get and replace item with iterator
int test_list_getitem(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_getitem(iter); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_getbefore(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);
													
	list_getbefore(iter); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_getafter(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_getafter(iter); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_replaceiteritem(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_replaceiteritem(iter, allocate_int(5)); 		// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Pop item with iterator
int test_list_popnext(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
														
	list_popnext(iter); 								// Testing function call
	result = 1;
														
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_popprev(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_popprev(iter); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Remove item, then move iterator
int test_list_removenext(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_removenext(iter, destroy_int); 				// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_removeprev(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
													
	list_removeprev(iter, destroy_int); 				// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
													
/*													
//	Specialized list functions
*/													
													
// Specialized list manipulations
int test_list_rolldown(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_rolldown(list); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_rollup(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_rollup(list); 									// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_reverse(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_reverse(list); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_randomize(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_randomize(list); 								// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_swapitems(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	int *item_a = allocate_int(1);
	int *item_b = allocate_int(9);
													
	list_swapitems(list, item_a, item_b); 				// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_isequal(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_t *list2 = list_copy(list);
													
	list_isequal(list, list2); 							// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_hassameitems(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_t *list2 = list_copy(list);
													
	list_hassameitems(list, list2); 					// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
		// Initialize hashmap
int test_list_activatehashmap(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_activatehashmap(list, int_to_str); 			// Testing function call
	result = 1;
													
	list_deactivatehashmap(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_deactivatehashmap(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatehashmap(list, int_to_str);
													
	list_deactivatehashmap(list); 						// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
// Index functions
int test_list_activateindex(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_activateindex(list); 							// Testing function call
	result = 1;
													
	list_deactivateindex(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_deactivateindex(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
													
	list_deactivateindex(list); 						// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_getitembyidx(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
													
	list_getitembyidx(list, 4); 						// Testing function call
	result = 1;
													
	list_deactivateindex(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_getidxbyitem(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
													
	list_getidxbyitem(list, allocate_int(7)); 			// Testing function call
	result = 1;
													
	list_deactivateindex(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_replaceitembyidx(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
													
	list_replaceitembyidx(list, allocate_int(3), 4); 	// Testing function call
	result = 1;
													
	list_deactivateindex(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_swapidxs(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
	int *item_a = allocate_int(4);
	int *item_b = allocate_int(5);
													
	list_swapidxs(list, item_a, item_b); 				// Testing function call
	result = 1;
													
	list_deactivateindex(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
// Priority functions
int test_list_activatepriority(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
													
	list_activatepriority(list); 						// Testing function call
	result = 1;
													
	list_deactivatepriority(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_deactivatepriority(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
													
	list_deactivatepriority(list); 						// Testing function call
	result = 1;
													
	list_deepdestroy(list, destroy_int); 				// Freeing memory
	free(array);
	return result;
}													
int test_list_replaceprioritycmpfunc(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
													
	list_replaceprioritycmpfunc(list, compare_string);	// Testing function call
	result = 1;
													
	list_deactivatepriority(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_poppriority(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
													
	list_poppriority(list); 							// Testing function call
	result = 1;
													
	list_deactivatepriority(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
int test_list_getpriority(int *array) {
	int result = 1;										// Init
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
													
	list_getpriority(list); 							// Testing function call
	result = 1;
													
	list_deactivatepriority(list); 						// Freeing memory
	list_deepdestroy(list, destroy_int);
	free(array);
	return result;
}													
