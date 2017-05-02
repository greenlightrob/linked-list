# linked-list

Created by [David Kristoffersen](https://github.com/davidkristoffersen/) and [Simon Solnes](https://github.com/simonsolnes/).

Doubly liked list with extended functionality for iteration and insertion.

## TEST
![badge](https://img.shields.io/badge/start%20witha-whyyyy%3F-brightgreen.svg)

## Implemented

yes: ![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg)

no: ![badge](https://img.shields.io/badge/implemented-no-brightred.svg)

## Works

yes: ![badge](https://img.shields.io/badge/works-yes-brightgreen.svg)
no: ![badge](https://img.shields.io/badge/works-no-brightred.svg)
unknown: ![badge](https://img.shields.io/badge/works-unknown-gray.svg)



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

| Function 																	|
|---------------------------------------------------------------------------|
| *List functions*															|
| General list functions													|
| `list_t *list_create(cmpfunc_t cmpfunc);`									|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `void list_destroy(list_t *list);`										|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `void list_deepdestroy(list_t *list, rmfunc_t rmfunc);`					|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `void list_usehashmap(list_t *list);`										|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `void list_replacecmpfunc(list_t *list, cmpfunc_t cmpfunc);`				|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `int list_size(list_t *list);`											|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `int list_contains(list_t *list, void *item);`							|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `void list_sort(list_t *list);`											|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| Copying list																|![badge](https://img.shields.io/badge/implemented-yes-brightgreen.svg?style=flat)
| `list_t *list_copy(list_t *list);`										|
| `list_t *list_deepcopy(list_t *list, cpyfunc_t cpyfunc);`					|
| Adding items																|
| `void list_addfirst(list_t *list, void *item);`							|
| `void list_addlast(list_t *list, void *item);`							|
| Popping items																|
| `void *list_popitem(list_t *list, void *item);`							|
| `void *list_popfirst(list_t *list);`										|
| `void *list_poplast(list_t *list);`										|
| Removing items															|
| `void list_removeitem(list_t *list, void *item, rmfunc_t rmfunc);`		|
| `void list_removefirst(list_t *list, rmfunc_t rmfunc);`					|
| `void list_removelast(list_t *list, rmfunc_t rmfunc);`					|
| Getting and replacing														|
| `void *list_getfirst(list_t *list);`										|
| `void *list_getlast(list_t *list);`										|
| `void *list_getitemnumfromfirst(list_t *list, int num);`					|
| `void *list_getitemnumfromlast(list_t *list, int num);`					|
| `void list_replaceitem(list_t *list, void *originalitem, void *newitem);`	|
| *Iterator functions*														|
| General iterator functions												|
| `list_iter_t *list_createiter(list_t *list);`								|
| `void list_copyiter(list_iter_t *originaliter, list_iter_t *newiter);`	|
| `void list_destroyiter(list_iter_t *iter);`								|
| `void list_resetiter(list_iter_t *iter);`									|
| `int list_hasnext(list_iter_t *iter);`									|
| `int list_hasbefore(list_iter_t *iter);`									|
| `int list_hasafter(list_iter_t *iter);`									|
| Iterator manipulations													|
| `void list_movenext(list_iter_t *iter);`									|
| `void list_moveprev(list_iter_t *iter);`									|
| `void *list_next(list_iter_t *iter);`										|
| `void *list_prev(list_iter_t *iter);`										|
| Adding items with iterators												|
| `void list_addbefore(list_iter_t *iter, void *item);`						|
| `void list_addafter(list_iter_t *iter, void *item);`						|
| Popping items with iterators												|
| `void *list_popnext(list_iter_t *iter);`									|
| `void *list_popprev(list_iter_t *iter);`									|
| Removing item then moving iterator										|
| `void *list_removenext(list_iter_t *iter, rmfunc_t rmfunc);`				|
| `void *list_removeprev(list_iter_t *iter, rmfunc_t rmfunc);`				|
| Getting and replacing items with iterators								|
| `void *list_getitem(list_iter_t *iter);`									|
| `void *list_getbefore(list_iter_t *iter);`								|
| `void *list_getafter(list_iter_t *iter);`									|
| `void list_replaceiteritem(list_iter_t *iter, void *item);`				|
|*Specialized list functions*												|
| List manipulations														|
| `void list_rolldown(list_t *list);`										|
| `void list_rollup(list_t *list);`											|
| `void list_reverse(list_t *list);`										|
| `void list_randomize(list_t *list);`										|

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
