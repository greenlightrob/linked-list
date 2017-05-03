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
| `list_replacecmpfunc`			| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_size`					| Yes			| Unknown	||
| `list_contains`				| Yes			| Unknown	||
| `list_sort`					| No			| Unknown	||
| `list_copy`					| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_deepcopy`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_addfirst`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_addlast`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_popitem`				| Yes			| Unknown	| Hashmap can be used better on this Changes must also happen in hashmap|
| `list_popfirst`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_poplast`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_removeitem`				| Yes			| Unknown	| Hashmap can be used better on this Changes must also happen in hashmap|
| `list_removefirst`			| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_removelast`				| Yes			| Unknown	| Changes must also happen in hashmap|
| `list_getfirst`				| Yes			| Unknown	||
| `list_getlast`				| Yes			| Unknown	||
| `list_getitemnumfromfirst`	| Yes			| Unknown	| Needs to be renamed|
| `list_getitemnumfromlast`		| Yes			| Unknown	| Needs to be renamed|
| `list_replaceitem`			| Yes			| Unknown	| Hashmap can be used better on this Changes must also happen in hashmap|
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
| `list_rolldown`				| Yes			| Unknown	||
| `list_rollup`					| Yes			| Unknown	||
| `list_reverse`				| Yes			| Unknown	||
| `list_randomize`				| No			| Unknown	||
| `list_isequal`				| No			| Unknown	||
| `list_hassameitems`			| No			| Unknown	||
