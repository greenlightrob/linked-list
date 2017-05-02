#ifndef tester_h
#define tester_h

/*
//	Testing functions
*/

// Creating and destroying list
int test_list_create(int *array);
int test_list_destroy(int *array);
int test_list_deepdestroy(int *array);

// Config
int test_list_usehashmap(int *array);
int test_list_replacecmpfunc(int *array);

// Getting list info
int test_list_size(int *array);
int test_list_contains(int *array);

// Sorting list
int test_list_sort(int *array);

// Copying list
int test_list_copy(int *array);
int test_list_deepcopy(int *array);

// Adding items
int test_list_addfirst(int *array);
int test_list_addlast(int *array);

// Removing items
int test_list_remove(int *array);
int test_list_deepremove(int *array);

// Popping items (will remove items from list)
int test_list_popfirst(int *array);
int test_list_poplast(int *array);

// Getting the edge items of list
int test_list_getlast(int *array);
int test_list_getfirst(int *array);

// Getting the item that is located at the num-th position
int test_list_getitemnumfromfirst(int *array);
int test_list_getitemnumfromlast(int *array);

// General iterator functions
int test_list_createiter(int *array);
int test_list_copyiter(int *array);
int test_list_destroyiter(int *array);
int test_list_resetiter(int *array);

// Check if current item has a node (hasprev would do the same)
int test_list_hasnext(int *array);

// Check if iterator has node before or after
int test_list_hasbefore(int *array);
int test_list_hasafter(int *array);

// Manipulating items with iteratos
int test_list_getitem(int *array);
int test_list_getbefore(int *array);
int test_list_getafter(int *array);
int test_list_replaceitem(int *array);

// Specific iterator moving
int test_list_movenext(int *array);
int test_list_moveprev(int *array);

// Returning item then moving iterator
int test_list_next(int *array);
int test_list_prev(int *array);

// Popping item then moving iterator
int test_list_popnext(int *array);
int test_list_popprev(int *array);

// Adding item in direction then moving iterator the same direction
int test_list_addnext(int *array);
int test_list_addprev(int *array);

// Adding item in direction
int test_list_addafter(int *array);
int test_list_addbefore(int *array);

// List manipulations
int test_list_rolldown(int *array);
int test_list_rollup(int *array);
int test_list_reverse(int *array);
int test_list_randomize(int *array);

#endif
