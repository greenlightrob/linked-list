#ifndef TESTER_H															
#define TESTER_H															
																			
/*																					
 * List functions															
 */																		
																	
// General list functions													
int test_list_create(int *array);												
int test_list_destroy(int *array);													
int test_list_deepdestroy(int *array);									
int test_list_usehashmap(int *array);			// Initialize hashmap
int test_list_replacecmpfunc(int *array);		// Change the comparefunction used
int test_list_size(int *array);					// Getting list size
int test_list_contains(int *array);				// Checking weather item exits in list
int test_list_sort(int *array); 				// Sorting list							
																
// Copying list																	
int test_list_copy(int *array);													
int test_list_deepcopy(int *array);													
																		
// Adding items															
int test_list_addfirst(int *array);														
int test_list_addlast(int *array);												
																	
// Popping items														
int test_list_popitem(int *array);										
int test_list_popfirst(int *array);							
int test_list_poplast(int *array);								
														
// Removing items										
int test_list_removeitem(int *array);					
int test_list_removefirst(int *array);							
int test_list_removelast(int *array);						
															
// Getting and replacing									
int test_list_getfirst(int *array); 			// bug							
int test_list_getlast(int *array);								
int test_list_getitemnumfromfirst(int *array);					
int test_list_getitemnumfromlast(int *array);						
int test_list_replaceitem(int *array);			// implement				
																		
/*																	
 * Iterator functions												
 */																		
																					
// General iterator functions																
int test_list_createiter(int *array);													
int test_list_copyiter(int *array);												
int test_list_destroyiter(int *array);												
int test_list_resetiter(int *array);														
int test_list_hasnext(int *array);				// Check if current iter has a node (hasprev would do the same)
int test_list_hasbefore(int *array);			// Check if iterator has node before or after
int test_list_hasafter(int *array);				// Check if iterator has node before or after
														
// Iterator manipulations							
int test_list_movenext(int *array);				// Moves the iterator next
int test_list_moveprev(int *array);				// Moves the iterator prev
int test_list_next(int *array);					// Returning item then moving next
int test_list_prev(int *array);					// Returning item then moving prev
																		
// Adding items with iterators													
int test_list_addbefore(int *array);									
int test_list_addafter(int *array);									
															
// Popping items with iterators									
int test_list_popnext(int *array);				// Popping item, then moving next
int test_list_popprev(int *array);				// Popping item, then moving prev
															
// Removing item then moving iterator								
int test_list_removenext(int *array); 			// implement										
int test_list_removeprev(int *array); 			// implement							
																		
// Getting and replacing items with iterators											
int test_list_getitem(int *array);													
int test_list_getbefore(int *array);										
int test_list_getafter(int *array);													
int test_list_replaceiteritem(int *array); 		// fix											
																		
/*																		
 * Specialized list functions												
 */																			
																					
// List manipulations															
int test_list_rolldown(int *array);												
int test_list_rollup(int *array);												
int test_list_reverse(int *array);													
int test_list_randomize(int *array);													

#endif																				
