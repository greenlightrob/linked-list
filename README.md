# linked-list

Created by [David Kristoffersen](https://github.com/davidkristoffersen/) and [Simon Solnes](https://github.com/simonsolnes/).

Doubly liked list with extended functionality for iteration and insertion.

## Docs
coming

## Development:

### Todos
* Rewriting
	* Inconsistent `list->size == 0` and `list->head == NULL`
	* Internal moving nodes instead of iterating
	* Do we have to use typedefs?

| Function 						| Implemented 	| Works		| Status	|
|-------------------------------|---------------|-----------|-----------|
| `list_create`					| Yes			| Unknown	||
| `list_destroy;`				| Yes			| Unknown	||
| `list_deepdestroy`			| Yes			| Unknown	||
| `list_usehashmap`				| Yes			| Unknown	||
| `list_replacecmpfunc`			| Yes			| Unknown	||
| `list_size`					| Yes			| Unknown	||
| `list_contains`				| Yes			| Unknown	||
| `list_sort`					| No			| Unknown	||
| `list_copy`					| Yes			| Unknown	||
| `list_deepcopy`				| Yes			| Unknown	||
| `list_addfirst`				| Yes			| Unknown	||
| `list_addlast`				| Yes			| Unknown	||
| `list_popitem`				| Yes			| Unknown	||
| `list_popfirst`				| Yes			| Unknown	||
| `list_poplast`				| Yes			| Unknown	||
| `list_removeitem`				| Yes			| Unknown	||
| `list_removefirst`			| Yes			| Unknown	||
| `list_removelast`				| Yes			| Unknown	||
| `list_getfirst`				| Yes			| Unknown	||
| `list_getlast`				| Yes			| Unknown	||
| `list_getitemnumfromfirst`	| Yes			| Unknown	| Needs to be renamed|
| `list_getitemnumfromlast`		| Yes			| Unknown	| Needs to be renamed|
| `list_replaceitem`			| No			| Unknown	||
| `list_createiter`				| Yes			| Unknown	||
| `list_copyiter`				| Yes			| Unknown	||
| `list_destroyiter`			| Yes			| Unknown	||
| `list_resetiter`				| Yes			| Unknown	||
| `list_hasnext`				| Yes			| Unknown	||
| `list_hasbefore`				| Yes			| Unknown	||
| `list_hasafter`				| Yes			| Unknown	||
| `list_movenext`				| Yes			| Unknown	||
| `list_moveprev`				| Yes			| Unknown	||
| `list_next`					| Yes			| Unknown	||
| `list_prev`					| Yes			| Unknown	||
| `list_addbefore`				| Yes			| Unknown	||
| `list_addafter`				| Yes			| Unknown	||
| `list_popnext`				| Yes			| Unknown	||
| `list_popprev`				| Yes			| Unknown	||
| `list_removenext`				| Yes			| Unknown	||
| `list_removeprev`				| Yes			| Unknown	||
| `list_getitem`				| Yes			| Unknown	||
| `list_getbefore`				| Yes			| Unknown	||
| `list_getafter`				| Yes			| Unknown	||
| `list_replaceiteritem`		| Yes			| Unknown	||
| `list_rolldown`				| Yes			| Unknown	||
| `list_rollup`					| Yes			| Unknown	||
| `list_reverse`				| Yes			| Unknown	||
| `list_randomize`				| No			| Unknown	||
| `list_isequal`				| No			| Unknown	||
| `list_hassameitems`			| No			| Unknown	||

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
