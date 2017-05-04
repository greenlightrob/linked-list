#ifndef TESTER_H														
#define TESTER_H														
														
/*														
 * List functions														
 */														
														
// Create list														
int test_list_create(int *array);														
														
// Destroy list																												
int test_list_destroy(int *array);																												
int test_list_deepdestroy(int *array);																												
																												
// Copy list																												
int test_list_copy(int *array);																												
int test_list_deepcopy(int *array);																												
																												
// Add item																												
int test_list_addfirst(int *array);																												
int test_list_addlast(int *array);																												
																												
// Get and replace item																												
int test_list_getfirst(int *array); 					// bug																												
int test_list_getlast(int *array);																												
int test_list_replaceitem(int *array);																												
																												
// Pop item																												
int test_list_popitem(int *array);																												
int test_list_popfirst(int *array);																												
int test_list_poplast(int *array);																												
																												
// Remove item																												
int test_list_removeitem(int *array);																												
int test_list_removefirst(int *array);																												
int test_list_removelast(int *array);																												
																												
// General list functions																												
int test_list_replacecmpfunc(int *array);				// Change the comparefunction used																					
int test_list_size(int *array);							// Getting list size																					
int test_list_contains(int *array);						// Checking weather item exits in list																			
int test_list_sort(int *array); 						// Sorting list
																								
/*																								
 * Iterator functions																								
 */																								
																								
// Create iterator																								
int test_list_createiter(int *array);																								
int test_list_destroyiter(int *array);																								
int test_list_copyiter(int *array);																								
int test_list_resetiter(int *array);																								
																								
// Check whether iterator has a node																								
int test_list_hasnext(int *array);						// Check if current iter has a node (hasprev would do the same)
int test_list_hasbefore(int *array);					// Check if iterator has node before or after
int test_list_hasafter(int *array);						// Check if iterator has node before or after
																								
// Iterator manipulations																								
int test_list_movenext(int *array);						// Moves the iterator next
int test_list_moveprev(int *array);						// Moves the iterator prev
int test_list_next(int *array);							// Returning item then moving next
int test_list_prev(int *array);							// Returning item then moving prev
																								
// Add item with iterator																								
int test_list_addbefore(int *array);																								
int test_list_addafter(int *array);																								
																								
// Get and replace item with iterator																								
int test_list_getitem(int *array);																								
int test_list_getbefore(int *array);																								
int test_list_getafter(int *array);																								
int test_list_replaceiteritem(int *array);																								
																								
// Pop item with iterator																								
int test_list_popnext(int *array);						// Popping item, then moving next
int test_list_popprev(int *array);						// Popping item, then moving prev
																								
// Remove item, then moving iterator																								
int test_list_removenext(int *array);																								
int test_list_removeprev(int *array);																								
																								
/*																								
 * Specialized list functions																								
 */																								
																								
int test_list_rolldown(int *array);																								
int test_list_rollup(int *array);																								
int test_list_reverse(int *array);																								
int test_list_randomize(int *array);																								
int test_list_swapitems(int *array);																								
int test_list_isequal(int *array);																								
int test_list_hassameitems(int *array);																								
																								
// Initialize hashmap																								
int test_list_activatehashmap(int *array);				// Initialize hashmap																								
int test_list_deactivatehashmap(int *array);																								

// Index functions
int test_list_activateindex(int *array);
int test_list_deactivateindex(int *array);
int test_list_getitembyidx(int *array);
int test_list_getidxbyitem(int *array);
int test_list_replaceitembyidx(int *array);
int test_list_swapidxs(int *array);

// Priority functions
int test_list_activatepriority(int *array);
int test_list_deactivatepriority(int *array);
int test_list_replaceprioritycmpfunc(int *array);
int test_list_poppriority(int *array);																								
int test_list_getpriority(int *array);																								
																								
#endif																								
