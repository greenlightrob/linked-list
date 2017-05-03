#ifndef LIST_H
#define LIST_H

typedef int (*cmpfunc_t)(void *, void *);
typedef void *(*cpyfunc_t)(void *);
typedef void (*rmfunc_t)(void *);
typedef char *(*strfunc_t)(void *);
typedef unsigned long (*hashfunc_t)(unsigned char *);

struct list;
typedef struct list list_t;
struct list_iter;
typedef struct list_iter list_iter_t;

/*
 * List functions
 */

// General list functions
list_t *list_create(cmpfunc_t cmpfunc);
void list_destroy(list_t *list);
void list_deepdestroy(list_t *list, rmfunc_t rmfunc);
void list_replacecmpfunc(list_t *list, cmpfunc_t cmpfunc);					// Change the comparefunction used
int list_size(list_t *list);												// Getting list size
int list_contains(list_t *list, void *item);								// Checking weather item exits in list
void list_sort(list_t *list); // Sorting list

// Copying list
list_t *list_copy(list_t *list);
list_t *list_deepcopy(list_t *list, cpyfunc_t cpyfunc);

// Adding items
void list_addfirst(list_t *list, void *item);
void list_addlast(list_t *list, void *item);

// Popping items
void *list_popitem(list_t *list, void *item);
void *list_popfirst(list_t *list);
void *list_poplast(list_t *list);

// Removing items
void list_removeitem(list_t *list, void *item, rmfunc_t rmfunc);
void list_removefirst(list_t *list, rmfunc_t rmfunc);
void list_removelast(list_t *list, rmfunc_t rmfunc);

// Getting and replacing
void *list_getfirst(list_t *list); // bug
void *list_getlast(list_t *list);
void list_replaceitem(list_t *list, void *originalitem, void *newitem);	// implement

/*
 * Iterator functions
 */

// General iterator functions
list_iter_t *list_createiter(list_t *list);
void list_copyiter(list_iter_t *originaliter, list_iter_t *newiter);
void list_destroyiter(list_iter_t *iter);
void list_resetiter(list_iter_t *iter);
int list_hasnext(list_iter_t *iter);										// Check if current iter has a node (hasprev would do the same)
int list_hasbefore(list_iter_t *iter);										// Check if iterator has node before or after
int list_hasafter(list_iter_t *iter);										// Check if iterator has node before or after

// Iterator manipulations
void list_movenext(list_iter_t *iter);										// Moves the iterator next
void list_moveprev(list_iter_t *iter);										// Moves the iterator prev
void *list_next(list_iter_t *iter);											// Returning item then moving next
void *list_prev(list_iter_t *iter);											// Returning item then moving prev

// Adding items with iterators
void list_addbefore(list_iter_t *iter, void *item);
void list_addafter(list_iter_t *iter, void *item);

// Popping items with iterators
void *list_popnext(list_iter_t *iter);										// Popping item, then moving next
void *list_popprev(list_iter_t *iter);										// Popping item, then moving prev

// Removing item then moving iterator
void list_removenext(list_iter_t *iter, rmfunc_t rmfunc); // implement
void list_removeprev(list_iter_t *iter, rmfunc_t rmfunc); // implement

// Getting and replacing items with iterators
void *list_getitem(list_iter_t *iter);
void *list_getbefore(list_iter_t *iter);
void *list_getafter(list_iter_t *iter);
void list_replaceiteritem(list_iter_t *iter, void *item); // fix

/*
 * Specialized list functions
 */

void list_rolldown(list_t *list);
void list_rollup(list_t *list);
void list_reverse(list_t *list);
void list_randomize(list_t *list);
void list_swapitems(list_t *list, void *itema, void *itemb);
int list_isequal(list_t *lista, list_t *listb);
int list_hassameitems(list_t *lista, list_t *listb);

// Initialize hashmap
void list_activatehashmap(list_t *list, strfunc_t strfunc);											// Initialize hashmap
void list_deactivatehashmap(list_t *list);

// Index functions
void list_activateindex(list_t *list);
void list_deactivateindex(list_t *list);
void list_swapidxs(list_t *list, void *itema, void *itemb);
void *list_getitembyidx(list_t *list, int idx);
int list_getidxbyitem(list_t *list, void *item);

// Priority functions
void list_activatepriority(list_t *list);
void list_deactivatepriority(list_t *list);
void list_replaceprioritycmpfunc(list_t *list, cmpfunc_t cmpfunc);
void *list_poppriority(list_t *list);
void *list_getpriority(list_t *list);

#endif
