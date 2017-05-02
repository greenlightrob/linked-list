# linked-list

Created by [David Kristoffersen](https://github.com/davidkristoffersen/) and [Simon Solnes](https://github.com/simonsolnes/).

Doubly liked list with extended functionality for iteration and insertion.

## TODO's:

* Test
	* `list_getitemnumberfrom[first|last]`
	* `list_add[before|after]`
	* `list_deepdestroy`
	* `list_roll[down|up]`
* Implement:
	* `list_randomize`
	* `list_isequal`
	* `list_hassameitems`
* Renaming
	* `list_getitemnumfrom[first|last]`
* Rewriting
	* Inconsistent `list->size == 0` and `list->head == NULL`
	* Internal moving nodes instead of iterating
	* Do we have to use typedefs?


* regarding hashmap
	* implement
		* `map_remove()` add to `list_remove`


### Creating and destroying list
* `list_t *list_create(cmpfunc_t cmpfunc);`
* `void list_destroy(list_t *list);`
* `void list_deepdestroy(list_t *list, destroyfunc_t destroyfunc);`

### Config
* `void list_usehashmap(list_t *list);`
* `void list_replacecmpfunc(list_t *list, cmpfunc_t cmp);`

### Getting list info
* `int list_size(list_t *list);`
* `int list_contains(list_t *list, void *item);`

### Sorting list
* `void list_sort(list_t *list);`

### Copying list
* `list_t *list_copy(list_t *list);`
* `list_t *list_deepcopy(list_t *list, cpyfunc_t cpyfunc);`

### Adding items
* `void list_addfirst(list_t *list, void *item);`
* `void list_addlast(list_t *list, void *item);`

### Removing items
* `void list_remove(list_t *list, void *item);`
* `void list_deepremove(list_t *list, void *item, destroyfunc_t destroyfunc);`

### Popping items (will remove items from list)
* `void *list_popfirst(list_t *list);`
* `void *list_poplast(list_t *list);`

### Getting the edge items of list
* `void *list_getlast(list_t *list);`
* `void *list_getfirst(list_t *list);`

### Getting the item that is located at the num-th position
* `void *list_getitemnumfromfirst(list_t *list, int num);`
* `void *list_getitemnumfromlast(list_t *list, int num);`

### General iterator functions
* `list_iter_t *list_createiter(list_t *list);`
* `void list_copyiter(list_iter_t *a, list_iter_t *b);`
* `void list_destroyiter(list_iter_t *iter);`
* `void list_resetiter(list_iter_t *iter);`

### Check if current item has a node (hasprev would do the same)
* `int list_hasnext(list_iter_t *iter);`

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
* `void *list_popnext(list_iter_t *iter);`
* `void *list_popprev(list_iter_t *iter);`

### Adding item in direction
* `void list_addafter(list_iter_t *iter, void *item);`
* `void list_addbefore(list_iter_t *iter, void *item);`

### List manipulations
* `void list_rolldown(list_t *list);`
* `void list_rollup(list_t *list);`
* `void list_reverse(list_t *list);`
* `void list_randomize(list_t *list);`

## Gems

David once commited this function:

```
void list_remove(list_t *list, void *item) {
	if (list == NULL) list_err("list_remove: list = NULL");
	if (list->head == NULL) list_err("list_remove: head = NULL");
	node_t *node = list->head;	
	while(list->cmpfunc(node->item, item) != 0 && node) node = node->next;
	if (node) {
		if (list->size == 1);
		else if (node == list->head) list->tail = NULL;
		else if (node == list->tail) list->head = NULL;
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		free(node);
	}
}
```
