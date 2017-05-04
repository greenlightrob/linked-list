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
	free(array);
	return (list_create(compare_int)) ? 1: 0;
}
// Destroy list
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
// Copy list
int test_list_copy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_t *copylist = list_copy(list);
	while(list_size(list) > 2 && list_size(copylist) > 2) {
		if (compare_int(list_popfirst(list), list_popfirst(copylist)) != 0) return 0;
	}

	list_deepdestroy(list, destroy_int);
	int val = *(int *)list_poplast(copylist);
	if (val == 9) return 0; 
	free(array);
	return 1;
}
int test_list_deepcopy(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_t *copylist = list_deepcopy(list, copy_int);
	while(list_size(list) > 2 && list_size(copylist) > 2) {
		if (compare_int(list_popfirst(list), list_popfirst(copylist)) != 0) return 0;
	}

	list_deepdestroy(list, destroy_int);
	int val = *(int *)list_poplast(copylist);
	if (val != 9) return 0; 
	free(array);
	return 1;
}
// Add item
int test_list_addfirst(int *array) {
	list_t *list = list_create(compare_int);

	list_addfirst(list, &array[1]);
	if (*(int *)list_popfirst(list) != array[1]) return 0;

	free(array);
	return 1;
}
int test_list_addlast(int *array) {
	list_t *list = list_create(compare_int);

	list_addlast(list, &array[1]);
	if (*(int *)list_popfirst(list) != array[1]) return 0;

	free(array);
	return 1;
}
// Get and replace item
int test_list_getfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	if (*(int *)list_getfirst(list) != 0) return 0;

	free(array);
	return 1;
}
int test_list_getlast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	if (*(int *)list_getlast(list) != 9) return 0;;

	free(array);
	return 1;
}
int test_list_replaceitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	// list_replaceitem(list, &array[1], &array[4]);

	free(array);
	return 1;
}
// Pop item
int test_list_popitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_popitem(list, &array[5]);
	if (list_contains(list, allocate_int(5))) return 0;

	free(array);
	return 1;
}
int test_list_popfirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_popfirst(list);

	free(array);
	return 1;
}
int test_list_poplast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_poplast(list);

	free(array);
	return 1;
}
// Remove item
int test_list_removeitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_removeitem(list, &array[2], destroy_int);
	if (!list_contains(list, allocate_int(2))) return 0;

	free(array);
	return 1;
}
int test_list_removefirst(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_removefirst(list, destroy_int);
	if (!list_contains(list, allocate_int(0))) return 0;

	free(array);
	return 1;
}
int test_list_removelast(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_removelast(list, destroy_int);
	if (!list_contains(list, allocate_int(9))) return 0;

	free(array);
	return 1;
}
// Genereal list functions
int test_list_replacecmpfunc(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	int cmpres_int = list_contains(list, &array[5]);
	list_replacecmpfunc(list, compare_null);
	int cmpres_null = list_contains(list, &array[5]);
	if (!cmpres_int || cmpres_null) return 0;
	free(array);
	return 1;
}

int test_list_size(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	free(array);
	for (int i = 0; i < size; i++, list_poplast(list)) if (list_size(list) != size - i) return 0;
	return 1;
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

int test_list_sort(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_sort(list);

	free(array);
	return 1;
}

/*
//	Iterator functions
*/

// Create iterator
int test_list_createiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	free(array);
	return (list_createiter(list)) ? 1: 0;
}
int test_list_destroyiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_destroyiter(iter);

	free(array);
	return 1;
}
int test_list_copyiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter_a, *iter_b;
	iter_a = list_createiter(list);
	iter_b = list_createiter(list);
	list_movenext(iter_a);
	list_movenext(iter_a);
	list_copyiter(iter_a, iter_b);
	if(*(int *)list_getitem(iter_a) != *(int *)list_getitem(iter_b)) return 0;

	free(array);
	return 1;
}
int test_list_resetiter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_resetiter(iter);

	free(array);
	return 1;
}
// Check wether iterator has a node
int test_list_hasnext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	if (!list_hasnext(iter)) return 0;

	free(array);
	return 1;
}
int test_list_hasbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);

	if (!list_hasbefore(iter)) return 0;

	free(array);
	return 1;
}
int test_list_hasafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	if (!list_hasafter(iter)) return 0;

	free(array);
	return 1;
}
// Iterator manipulations
int test_list_movenext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	list_movenext(iter);
	if (*(int *)list_getitem(iter) != 1) return 0;
	
	free(array);
	return 1;
}	
int test_list_moveprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	list_movenext(iter);
	list_movenext(iter);
	list_moveprev(iter);
	if (*(int *)list_getitem(iter) != 1) return 0;
	
	free(array);
	return 1;
}	
int test_list_next(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	if(*(int *)list_next(iter) != 0) return 0;
	
	free(array);
	return 1;
}	
int test_list_prev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	list_movenext(iter);
	list_prev(iter);
	if(*(int *)list_next(iter) != 1) return 0;
	
	free(array);
	return 1;
}	
// Add item with iterator
int test_list_addbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);
	
	list_addbefore(iter, allocate_int(11));
	if (*(int *)list_getfirst(list) != 11) return 0;
	
	free(array);
	return 1;
}	
int test_list_addafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	list_addafter(iter, &array[4]);
	
	free(array);
	return 1;
}	
// Get and replace item with iterator
int test_list_getitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_getitem(iter);

	free(array);
	return 1;
}
int test_list_getbefore(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	list_movenext(iter);

	list_getbefore(iter);

	free(array);
	return 1;
}
int test_list_getafter(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_getafter(iter);

	free(array);
	return 1;
}
int test_list_replaceiteritem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_replaceiteritem(iter, &array[5]);

	free(array);
	return 1;
}
// Pop item with iterator
int test_list_popnext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);
	
	list_popnext(iter);
	
	free(array);
	return 1;
}
int test_list_popprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_popprev(iter);

	free(array);
	return 1;
}
// Remove item, then move iterator
int test_list_removenext(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_removenext(iter, destroy_int);

	free(array);
	return 1;
}
int test_list_removeprev(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_iter_t *iter= list_createiter(list);

	list_removeprev(iter, destroy_int);

	free(array);
	return 1;
}

/*
//	Specialized list functions
*/

// Specialized list manipulations
int test_list_rolldown(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_rolldown(list);

	free(array);
	return 1;
}
int test_list_rollup(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_rollup(list);

	free(array);
	return 1;
}
int test_list_reverse(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_reverse(list);

	free(array);
	return 1;
}
int test_list_randomize(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_randomize(list);

	free(array);
	return 1;
}
int test_list_swapitems(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);

	list_swapitems(list, allocate_int(1), allocate_int(9));

	free(array);
	return 1;
}
int test_list_isequal(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_t *list2 = list_copy(list);

	list_isequal(list, list2);

	free(array);
	return 1;
}
int test_list_hassameitems(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_t *list2 = list_copy(list);

	list_hassameitems(list, list2);

	free(array);
	return 1;
}
// Initialize hashmap
int test_list_activatehashmap(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatehashmap(list, int_to_str);

	list_deactivatehashmap(list);
	free(array);
	return 1;
}
int test_list_deactivatehashmap(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatehashmap(list, int_to_str);
	list_deactivatehashmap(list);

	free(array);
	return 1;
}
// Index functions
int test_list_activateindex(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);

	list_deactivateindex(list);
	free(array);
	return 1;
}
int test_list_deactivateindex(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
	list_deactivateindex(list);

	free(array);
	return 1;
}
int test_list_getitembyidx(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
	list_getitembyidx(list, 4);

	list_deactivateindex(list);
	free(array);
	return 1;
}
int test_list_getidxbyitem(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
	list_getidxbyitem(list, allocate_int(7));

	list_deactivateindex(list);
	free(array);
	return 1;
}
int test_list_replaceitembyidx(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
	list_replaceitembyidx(list, allocate_int(3), 4);

	list_deactivateindex(list);
	free(array);
	return 1;
}
int test_list_swapidxs(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activateindex(list);
	list_swapidxs(list, allocate_int(4), allocate_int(5));
	list_deactivateindex(list);
	free(array);
	return 1;
}
// Priority functions
int test_list_activatepriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);

	list_deactivatepriority(list);
	free(array);
	return 1;
}
int test_list_deactivatepriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
	list_deactivatepriority(list);

	free(array);
	return 1;
}
int test_list_replaceprioritycmpfunc(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
	list_replaceprioritycmpfunc(list, compare_string);

	list_deactivatepriority(list);
	free(array);
	return 1;
}
int test_list_poppriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
	list_poppriority(list);

	list_deactivatepriority(list);
	free(array);
	return 1;
}
int test_list_getpriority(int *array) {
	list_t *list = list_create(compare_int);
	list_inputarr(list, array);
	list_activatepriority(list);
	list_getpriority(list);

	list_deactivatepriority(list);
	free(array);
	return 1;
}
