# linked-list

Created by [David Kristoffersen](https://github.com/davidkristoffersen/) and [Simon Solnes](https://github.com/simonsolnes/).

Doubly liked list with extended functionality for iteration and insertion.

## Docs
coming

## Development:

### Todos
check if list is sorted when list contains
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
| `list_replacecmpfunc`			| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_size`					| Yes			| Unknown	||
| `list_contains`				| Yes			| Unknown	||
| `list_sort`					| ```diff -No ```| Unknown	||
| `list_copy`					| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_deepcopy`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_addfirst`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_addlast`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_popitem`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_popfirst`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_poplast`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_removeitem`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_removefirst`			| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_removelast`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_getfirst`				| Yes			| Unknown	||
| `list_getlast`				| Yes			| Unknown	||
| `list_replaceitem`			| Yes			| Unknown	|Changes must also happen in hashmap|
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
| `list_addbefore`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_addafter`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_popnext`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_popprev`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_removenext`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_removeprev`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_getitem`				| Yes			| Unknown	||
| `list_getbefore`				| Yes			| Unknown	||
| `list_getafter`				| Yes			| Unknown	||
| `list_replaceiteritem`		| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_rolldown`				| Yes			| Unknown	|Bug|
| `list_rollup`					| Yes			| Unknown	|Bug|
| `list_reverse`				| Yes			| Unknown	||
| `list_swapitems`				| Yes			| Unknown	||
| `list_randomize`				| Yes			| Unknown	||
| `list_isequal`				| Yes			| Unknown	||
| `list_hassameitems`			| Yes			| Unknown	||
| `list_index(list_t *list)`	| Yes			| Unknown	||
| `list_swapidxs`				| Yes			| Unknown	||
| `list_getitembyidx`			| Yes			| Unknown	||
| `list_getidxbyitem`			| Yes			| Unknown	||
