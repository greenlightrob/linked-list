# linked-list

Doubly liked list with extended functionality for iteration and insertion.

## TODO's:
* Test the getitemnumberfrom[first|last}
* Document listadd[next|prev]
* Implement: 
	* list_hasprev?
	* list_reverse
	* list_copy

## Documentation

### General list functions

* `list_t *list_create(cmpfunc_t cmpfunc);`
* `void list_destroy(list_t *list);`
* `int list_size(list_t *list);`
* `int list_contains(list_t *list, void *item);`
* `list_t *list_deepcopy(list_t *list, cpyfunc_t cpyfunc);`
* `void list_replacecmpfunc(list_t *list, cmpfunc_t cmp);`
* `void list_sort(list_t *list);`

### Adding items
* `void list_addfirst(list_t *list, void *item);`
* `void list_addlast(list_t *list, void *item);`

### Popping items (will remove items from list)`
* `void *list_popfirst(list_t *list);`
* `void *list_poplast(list_t *list);`

### Getting the edge items of the list
* `void *list_getlast(list_t *list);`
* `void *list_getfirst(list_t *list);`

### Getting the item that is located at the num-th position
* `void *list_getitemnumberfromfirst(list_t *list, int num); // NOTE: Not tested - Simon`
* `void *list_getitemnumberfromlast(list_t *list, int num); // NOTE: Not tested - Simon`

### General iterator functions
* `list_iter_t *list_createiter(list_t *list);`
* `void list_copyiter(list_iter_t *a, list_iter_t *b);`
* `void list_destroyiter(list_iter_t *iter);`
* `void list_resetiter(list_t *list, list_iter_t *iter);`

### Check if current item has a node next
* `int list_hasnext(list_iter_t *iter);`
* `TODO hasprev`

### Check if iterator has node before or after
* `int list_hasbefore(list_iter_t *iter);`
* `int list_hasafter(list_iter_t *iter);`

### Manipulating items with iteratos
* `void *list_getitem(list_iter_t *iter);`
* `void *list_getbefore(list_iter_t *iter);`
* `void *list_getafter(list_iter_t *iter);`
* `void list_replaceitem(list_iter_t *iter, void *item);`

### Specific iterator moving
* `void list_movenext(list_iter_t *iter);`
* `void list_moveprev(list_iter_t *iter);`

### Returning item then moving iterator
* `void *list_next(list_iter_t *iter);`
* `void *list_prev(list_iter_t *iter);`

### Popping item then moving iterator
* `void *list_popnext(list_t *list, list_iter_t *iter);`
* `void *list_popprev(list_t *list, list_iter_t *iter);`

### TODO: documentation
* `void list_addnext(list_t *list, list_iter_t *iter, void *item);`
* `void list_addprev(list_t *list, list_iter_t *iter, void *item);`
