#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"

// Boolean
enum bool {
	true = 1,
	false = 0
};

// Hashmap structs
typedef struct mapnode {
	void *key;
} mapnode_t;
typedef struct map {
	list_t **hashtable;
	int size;
	int maxsize;
	cmpfunc_t cmpfunc;
} map_t;

// List structs
typedef struct node {
	struct node *next;
	struct node *prev;
	void *item;

} node_t;
struct list {
	cmpfunc_t cmpfunc;
	node_t *head;
	node_t *tail;
	int size;

	// Hashmap
	enum bool hasmap;
	map_t *map;

	// Priority
	enum bool haspriority;
	list_t *priority;

	// Index
	enum bool hasindex;
	void **index;
};

// Iterator
struct list_iter {
	list_t *list;
	node_t *node;
};

// Hashmap declarations
map_t *map_create(cmpfunc_t cmpfunc);
void map_destroy(map_t *map);
void map_replacecmpfunc(map_t *map, cmpfunc_t cmpfunc);
void map_put(map_t *map, void *key);
void map_remove(map_t *map, void *key);
int map_haskey(map_t *map, void *key);

/*
 * Internal functions
 */

void list_err(char *msg) {
	fprintf (stderr, "\e[38;2;255;0;0mlinkedlist error:\e[m %s\n", msg);
	exit (1);
}
node_t *create_node(list_t *list, void *item) {
	node_t *node = malloc(sizeof(node_t));
	if (node == NULL) list_err("create_node: failed to allocate memory");
	node->item = item;
	if (list->hasmap) map_put(list->map, item);
	list->size++;
	return node;
}
void *pop_node(list_t *list, node_t *node) {
	if (list->hasmap) map_remove(list->map, node->item);
	void *tmpitem = node->item;
	if (list->size == 1) {
		list->head = NULL;
		list->tail = NULL;
	}
	else if (node == list->head) {
		list->head = list->head->next;
		list->head->prev = NULL;
	}
	else if (node == list->tail) {
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	list->size--;
	free(node);
	node = NULL;
	return tmpitem;
}

/*
 * List functions
 */

// General list functions
list_t *list_create(cmpfunc_t cmpfunc) {
	list_t *tmp_list = malloc(sizeof(list_t));
	if (tmp_list == NULL) list_err("list_create: failed to allocate memory");
	if (cmpfunc == NULL) list_err("list_create: cmpfunc = NULL");
	tmp_list->cmpfunc = cmpfunc;
	tmp_list->head = NULL;
	tmp_list->tail = NULL;
	tmp_list->hasmap = false;
	tmp_list->haspriority = false;
	tmp_list->index = false;
	tmp_list->size = 0;
	return tmp_list;
}
void list_destroy(list_t *list) {
	if (list == NULL) list_err("list_destroy: list = NULL");
	if (list->hasmap) map_destroy(list->map);
	while (list->size > 0) list_poplast(list);
	free(list);
	list = NULL;
	return;
}
void list_deepdestroy(list_t *list, rmfunc_t rmfunc) {
	if (list == NULL) list_err("list_deepdestroy: list = NULL");
	if (list->hasmap) map_destroy(list->map);
	if (list->size > 0) rmfunc(list_poplast(list));
	free(list);
	list = NULL;
	return;
}

void list_replacecmpfunc(list_t *list, cmpfunc_t cmpfunc) {
	if (list == NULL) list_err("list_replacefunc: list = NULL");
	if (cmpfunc == NULL) list_err("list_replacefunc: cmpfunc = NULL");
	list->cmpfunc = cmpfunc;
	if (list->hasmap) map_replacecmpfunc(list->map, cmpfunc);
}
int list_size(list_t *list) {
	if (list == NULL) list_err("list_size: list = NULL");
	return list->size;
}
int list_contains(list_t *list, void *item) {
	if (list == NULL) list_err("list_contains: list = NULL");
	if (item == NULL) list_err("list_contains: item = NULL");
	if (list->hasmap) return map_haskey(list->map, item);
	node_t *tmp_node = list->head;
	for (;tmp_node != NULL; tmp_node = tmp_node->next)
		if (list->cmpfunc(tmp_node->item, item) == 0) return 1;
	return 0;
}
// TODO: implement
void list_sort(list_t *list) {
	// list_err("list sort is not implemented yet");
}

// Copying list
list_t *list_copy(list_t *list) {
	if (list == NULL) list_err("list_copy: list = NULL");
	list_t *copy = list_create(list->cmpfunc);
	if (list->hasmap) list_activatehashmap(copy);
	list_iter_t *iter = list_createiter(list);
	while (list_hasnext(iter))
		list_addlast(copy, list_next(iter));
	return copy;
}
list_t *list_deepcopy(list_t *list, cpyfunc_t cpyfunc) {
	if (list == NULL) list_err("list_deepcopy: list = NULL");
	list_t *copy = list_create(list->cmpfunc);
	list_iter_t *iter = list_createiter(list);
	if (list->hasmap) list_activatehashmap(copy);
	while (list_hasnext(iter))
		list_addlast(copy, cpyfunc(list_next(iter)));
	return copy;
}

// Adding items
void list_addfirst(list_t *list, void *item) {
	if (list == NULL) list_err("list_addfirst: list = NULL");
	if (item == NULL) list_err("list_addfirst: item = NULL");
	node_t *tmp_node = create_node(list, item);
	tmp_node->prev = NULL;
	tmp_node->next = list->head;
	if (list->size == 1) list->tail = tmp_node;
	else list->head->prev = tmp_node;
	list->head = tmp_node;
	return;
}
void list_addlast(list_t *list, void *item) {
	if (list == NULL) list_err("list_addlast: list = NULL");
	if (item == NULL) list_err("list_addlast: item = NULL");
	node_t *tmp_node = create_node(list, item);
	tmp_node->next = NULL;
	tmp_node->prev = list->tail;
	if (list->size == 1) list->head = tmp_node;
	else list->tail->next = tmp_node;
	list->tail = tmp_node;
	return;
}

// Popping items
void *list_popitem(list_t *list, void *item) {
	if (list == NULL) list_err("list_popitem: list = NULL");
	if (list->head == NULL) list_err("list_popitem: head = NULL");
	if (!list_contains(list, item)) list_err("list_popitem: trying to pop something that does not exist");
	node_t *node = list->head;
	while (node->next) {
		if (list->cmpfunc(node->item, item) == 0) break;
		node = node->next;
	}
	if (list->cmpfunc(node->item, item) != 0) list_err("list_popitem: Bug in linkedlist. Not users fault");
	if (list->hasmap) map_remove(list->map, item);
	return pop_node(list, node);
}
void *list_popfirst(list_t *list) {
	if (list == NULL) list_err("list_popfirst: list = NULL");
	if (list->head == NULL) list_err("list_popfirst: head = NULL");
	if (list->size == 0) list_err("list_popfirst: list->size = 0");
	return pop_node(list, list->head);
}
void *list_poplast(list_t *list) {
	if (list == NULL) list_err("list_poplast: list = NULL");
	if (list->tail == NULL) list_err("list_poplast: head = NULL");
	if (list->size == 0) list_err("list_poplast: list->size = 0");
	return pop_node(list, list->tail);
}

// Removing items
void list_removeitem(list_t *list, void *item, rmfunc_t rmfunc) {
	if (list == NULL) list_err("list_removeitem: list = NULL");
	if (list->head == NULL) list_err("list_removeitem: head = NULL");
	if (!list_contains(list, item)) list_err("list_removeitem: trying to remove something that does not exist");
	node_t *node = list->head;
	while (node->next) {
		if (list->cmpfunc(node->item, item) == 0) break;
		node = node->next;
	}
	if (list->cmpfunc(node->item, item) != 0) list_err("list_remove: Bug in linkedlist. Not users fault.");
	if (list->hasmap) map_remove(list->map, item);
	rmfunc(pop_node(list, node));
}
void list_removefirst(list_t *list, rmfunc_t rmfunc) {
	if (list == NULL) list_err("list_removefirst: list = NULL");
	if (list->head == NULL) list_err("list_removefirst: head = NULL");
	if (list->size == 0) list_err("list_removefirst: list->size = 0");
	rmfunc(pop_node(list, list->head));
}
void list_removelast(list_t *list, rmfunc_t rmfunc) {
	if (list == NULL) list_err("list_removelast: list = NULL");
	if (list->tail == NULL) list_err("list_removelast: head = NULL");
	if (list->size == 0) list_err("list_removelast: list->size = 0");
	rmfunc(pop_node(list, list->tail));
}

// Getting and replacing
void *list_getfirst(list_t *list) {
	if (list == NULL) list_err("list_getfirst: list = NULL");
	if (list->head == NULL) list_err("list_getfirst: head = NULL");
	if (list->size == 0) list_err("list_getfirst: list->size = 0");
	return list->head->item;
}
void *list_getlast(list_t *list) {
	if (list == NULL) list_err("list_getlast: list = NULL");
	if (list->tail == NULL) list_err("list_getlast: tail = NULL");
	if (list->size == 0) list_err("list_getlast: list->size = 0");
	return list->tail->item;
}
void list_replaceitem(list_t *list, void *originalitem, void *newitem) {
	if (list == NULL) list_err("list_replaceitem: list = NULL");
	if (list->head == NULL) list_err("list_replaceitem: head = NULL");
	if (!list_contains(list, originalitem)) list_err("list_replaceitem: trying to replace something that does not exist");
	node_t *node = list->head;
	while (node->next) {
		if (list->cmpfunc(node->item, originalitem) == 0) break;
		node = node->next;
	}
	node->item = newitem;
	if (list->cmpfunc(node->item, originalitem) != 0) list_err("list_replaceitem: Bug in linkedlist. Not users fault.");
	if (list->hasmap) {
		map_remove(list->map, originalitem);
		map_put(list->map, newitem);
	}
}

/*
 * Iterator functions
 */

// General iterator functions
list_iter_t *list_createiter(list_t *list) {
	if (list == NULL) list_err("list_createiter: list = NULL");
	list_iter_t *tmp_iter = malloc(sizeof(list_iter_t));
	if (tmp_iter == NULL) list_err("list_createiter: iter = NULL");

	tmp_iter->node = list->head;
	tmp_iter->list = list;
	return tmp_iter;
}
void list_copyiter(list_iter_t *a, list_iter_t *b) {
	if (a == NULL) list_err("list_copy_iter: iter_a = NULL");
	if (b == NULL) list_err("list_copy_iter: iter_b = NULL");
	b->node = a->node;
}
void list_destroyiter(list_iter_t *iter) {
	if (iter == NULL) list_err("list_destroyiter: iter = NULL");
	free(iter);
	iter = NULL;
}
void list_resetiter(list_iter_t *iter) {
	if (iter->list == NULL) list_err("list_resetiter: list = NULL");
	if (iter == NULL) list_err("list_resetiter: iter = NULL");
	iter->node = iter->list->head;
}
int list_hasnext(list_iter_t *iter) {
	if (iter == NULL) list_err("list_hasnext: iter = NULL");
	if (iter->node == NULL) return 0;
	return 1;
}
int list_hasbefore(list_iter_t *iter) {
	if (iter == NULL) list_err("list_hasbefore: iter = NULL");
	if (iter->node == NULL) list_err("list_hasbefore: node = NULL");
	if (iter->node->prev) return 1;
	else return 0;
}
int list_hasafter(list_iter_t *iter) {
	if (iter == NULL) list_err("list_hasafter: iter = NULL");
	if (iter->node == NULL) list_err("list_hasafter: node = NULL");
	if (iter->node->next) return 1;
	else return 0;
}

// Iterator manipulations
void list_movenext(list_iter_t *iter) {
	if (iter == NULL) list_err("list_movenext: iter = NULL");
	if (iter->node == NULL) list_err("list_movenext: iter->node = NULL");
	iter->node = iter->node->next;
}
void list_moveprev(list_iter_t *iter) {
	if (iter == NULL) list_err("list_moveprev: iter = NULL");
	if (iter->node == NULL) list_err("list_moveprev: iter->node = NULL");
	iter->node = iter->node->prev;
}
void *list_next(list_iter_t *iter) {
	if (iter == NULL) list_err("list_next: iter = NULL");
	if (iter->node == NULL) list_err("list_next: iter->node = NULL");
	void *tmpitem = list_getitem(iter);
	list_movenext(iter);
	return tmpitem;
}
void *list_prev(list_iter_t *iter) {
	if (iter == NULL) list_err("list_prev: iter = NULL");
	if (iter->node == NULL) list_err("list_prev: iter->node = NULL");
	void *tmp_item = iter->node->item;
	iter->node = iter->node->prev;
	return tmp_item;
}

// Adding items with iterators
void list_addbefore(list_iter_t *iter, void *item) {
	if (iter == NULL) list_err("list_addbefore: list iter does not exist");
	if (iter->list == NULL) list_err("list_addbefore: list does not exist");
	if (item == NULL) list_err("list_addbrefore: item = NULL");

	if (iter->node == NULL || iter->list->size < 1 || iter->node == iter->list->tail) {
		list_addlast(iter->list, item);
		iter->node = iter->list->tail; // hm
	}
	else if (iter->node == iter->list->head) list_addlast(iter->list, item);
	else {
		node_t *node = create_node(iter->list, item);
		iter->node->prev->next = node;
		node->prev = iter->node->prev;
		node->next = iter->node;
		iter->node->prev = node;
	}
}
void list_addafter(list_iter_t *iter, void *item) {
	if (iter == NULL) list_err("list_addafter: list iter does not exist");
	if (iter->list == NULL) list_err("list_addafter: list does not exist");
	if (item == NULL) list_err("list_addafter: item = NULL");

	if (iter->node == NULL || iter->list->size < 1 || iter->node == iter->list->head) {
		list_addfirst(iter->list, item);
		iter->node = iter->list->head; // hm
	}
	else if (iter->node == iter->list->head) list_addlast(iter->list, item);
	else {
		node_t *node = create_node(iter->list, item);
		iter->node->next->prev = node;
		node->next = iter->node->next;
		node->prev = iter->node;
		iter->node->next = node;
	}
}

// Popping items with iterators
void *list_popnext(list_iter_t *iter) {
	if (iter == NULL) list_err("list_popnext: list iter does not exist");
	if (iter->list == NULL) list_err("list_popnext: list does not exist");
	if (iter->list->size == 0) list_err("list_popnext: list has no items");
	if (iter->node == NULL) list_err("list_popnext: iter->node is NULL");
	node_t *trash = iter->node;
	iter->node = iter->node->next;
	return pop_node(iter->list, trash);
}

void *list_popprev(list_iter_t *iter) {
	if (iter == NULL) list_err("list_popprev: list iter does not exist");
	if (iter->list == NULL) list_err("list_popprev: list does not exist");
	if (iter->list->size == 0) list_err("list_popprev: list has no items");
	if (iter->node == NULL) list_err("list_popprev: iter->node is NULL");
	node_t *trash = iter->node;
	iter->node = iter->node->prev;
	return pop_node(iter->list, trash);
}

// Removing item then moving iterator
void list_removenext(list_iter_t *iter, rmfunc_t rmfunc) {
	if (iter == NULL) list_err("list_removenext: list iter does not exist");
	if (iter->list == NULL) list_err("list_removenext: list does not exist");
	if (iter->list->size == 0) list_err("list_removenext: list has no items");
	if (iter->node == NULL) list_err("list_removenext: iter->node is NULL");
	node_t *newiterpos = iter->node->next;
	rmfunc(pop_node(iter->list, iter->node));
	iter->node = newiterpos;
}
void list_removeprev(list_iter_t *iter, rmfunc_t rmfunc) {
	if (iter == NULL) list_err("list_removeprev: list iter does not exist");
	if (iter->list == NULL) list_err("list_removeprev: list does not exist");
	if (iter->list->size == 0) list_err("list_removeprev: list has no items");
	if (iter->node == NULL) list_err("list_removeprev: iter->node is NULL");
	node_t *newiterpos = iter->node->prev;
	rmfunc(pop_node(iter->list, iter->node));
	iter->node = newiterpos;
}

// Getting and replacing items with iterators
void *list_getitem(list_iter_t *iter) {
	if (iter == NULL) list_err("list_getitem: iter = NULL");
	if (iter->node == NULL) list_err("list_getitem: iter->node = NULL");
	return iter->node->item;
}
void *list_getbefore(list_iter_t *iter) {
	if (iter == NULL) list_err("list_getbefore: iter = NULL");
	if (iter->node == NULL) list_err("list_getbefore: iter->node = NULL");
	if (iter->node->prev == NULL) list_err("list_getbefore: iter->node->prev = NULL");
	return iter->node->prev->item;
}
void *list_getafter(list_iter_t *iter) {
	if (iter == NULL) list_err("list_getafter: iter = NULL");
	if (iter->node == NULL) list_err("list_getafter: iter->node = NULL");
	if (iter->node->next == NULL) list_err("list_getafter: iter->node->next = NULL");
	return iter->node->next->item;
}
void list_replaceiteritem(list_iter_t *iter, void *item) {
	if (iter == NULL) list_err("list_replaceitem: iter = NULL");
	if (iter->node == NULL) list_err("list_replaceitem: iter->node = NULL");
	if (item == NULL) list_err("list_replaceitem: item = NULL");
	if (iter->list->hasmap) {
		map_remove(iter->list->map, iter->node->item);
		map_put(iter->list->map, item);
	}
	iter->node->item = item;
}

/*
 * Specialized list functions
 */

void list_rolldown(list_t *list) {
	if (list == NULL) list_err("list_rolldown: list = NULL");
	if (list->size < 2) return;
	node_t *tmptail = list->tail;

	list->tail = list->tail->prev;
	list->tail->next = NULL;

	tmptail->next = list->head;
	tmptail->prev = NULL;
	list->head = tmptail;
}
void list_rollup(list_t *list) {
	if (list == NULL) list_err("list_rollup: list = NULL");
	if (list->size < 2) return;
	node_t *tmphead = list->head;
	
	list->head = list->head->next;
	tmphead->prev = list->tail;
	tmphead->next = NULL;
	list->tail = tmphead;
}
void list_reverse(list_t *list) {
	if (list == NULL) list_err("list_addfirst: list = NULL");
	if (list->size == 1) return;
	node_t *beg = list->head, *end = list->tail;
	void *tmp;
	for (int i = 0; i < list->size / 2; i++) {
		tmp = beg->item;
		beg->item = end->item;
		end->item = tmp;
		beg = beg->next;
		end = end->prev;
	}
}
void list_randomize(list_t *list) {
	if (list == NULL) list_err("list_randomize: list = NULL");
	if (list->size < 2) return;
	srand(time(0));
	void *itema;
	void *itemb;
	for (int i = list->size * 5; i > 1; i--) {
		itema = list_getitembyidx(list, rand() % list->size);
		itemb = list_getitembyidx(list, rand() % list->size);
		list_replaceitem(list, itema, itemb);
		list_replaceitem(list, itemb, itema);
	}
}
void list_swapitems(list_t *list, void *itema, void *itemb) {
	if (list == NULL) list_err("list_swapitems: first list = NULL");
	if (itema == NULL) list_err("list_replaceitem: item = NULL");
	if (itemb == NULL) list_err("list_replaceitem: item = NULL");
	list_replaceitem(list, itema, itemb);
	list_replaceitem(list, itemb, itema);
}
int list_isequal(list_t *lista, list_t *listb) {
	if (lista == NULL) list_err("list_isequal: first list = NULL");
	if (listb == NULL) list_err("list_isequal: second list = NULL");
	if (lista->cmpfunc != listb->cmpfunc) list_err("list_isequal: lists has different cmpfuncs");
	if (lista->size != listb->size) return 0;
	list_iter_t *itera = list_createiter(lista);
	list_iter_t *iterb = list_createiter(listb);
	while (list_hasnext(itera) && list_hasnext(iterb)) if (lista->cmpfunc(list_next(itera), list_next(iterb)) != 0) return 0;
	return 1;
}
int list_hassameitems(list_t *lista, list_t *listb) {
	if (lista == NULL) list_err("list_isequal: first list = NULL");
	if (listb == NULL) list_err("list_isequal: second list = NULL");
	if (lista->cmpfunc != listb->cmpfunc) list_err("list_isequal: lists has different cmpfuncs");
	list_t *largest;
	list_t *smallest;
	if (lista->size > listb->size) {
		largest = lista;
		smallest = listb;
	}
	else {
		largest = listb;
		smallest = lista;
	}
	list_iter_t *iter = list_createiter(largest);
	while (list_hasnext(iter)) if (list_contains(smallest, list_next(iter)) == 0) return 0;
	return 1;
}
// Hashmap functions
void list_activatehashmap(list_t *list) {
	list->map = map_create(list->cmpfunc);
	list_iter_t *iter = list_createiter(list);
	while (list_hasnext(iter))
		map_put(list->map, list_next(iter));
	list->hasmap = true;
}
// TODO: implement
void list_deactivatehashmap(list_t *list) {

}

// Index functions
// TODO: implement
void list_activateindex(list_t *list) {
	if (list == NULL) list_err("list_activateindex: list = NULL");
	list->haspriority = true;
	list->priority = list_copy(list);
	list_sort(list->priority);
}
// TODO: implement
void list_deactivateindex(list_t *list) {
	if (list == NULL) list_err("list_deactivateindex: list = NULL");
	if (list->priority == NULL) list_err("list_deactivateindex: list->priority = NULL");
	list->haspriority = false;
	list_destroy(list->priority);
}
// TODO: implement
void list_swapidxs(list_t *list, void *itema, void *itemb) {
	
}
void *list_getitembyidx(list_t *list, int idx) {
	if (list == NULL) list_err("list_getitembyidx: list = NULL");
	if (list->size == 0) list_err("list_getitembyidx: list->size = 0");
	if (idx >= list->size) list_err("list_getitemnbyidx: num is larger than list");
	node_t *tmp_node = list->head;
	for (int i = 0; i < idx; i++) {
		if (tmp_node == NULL) list_err("list_getitemnbyidx: Bug in list. Not users fault.");
		if (tmp_node->next == NULL) list_err("list_getitemnbyidx: Bug in list. Not users fault.");
		tmp_node = tmp_node->next;
	}
	return tmp_node->item;
}
// TODO: implement
int list_getidxbyitem(list_t *list, void *item) {
	if (list == NULL) list_err("list_getidxbyitem: list = NULL");
	if (list->size == 0) list_err("list_getidxbyitem: list->size = 0");
	if (item == NULL) list_err("list_getidxbyitem: num is larger than list");
		
	return 0;
}

// Priority functions
void list_activateprioriy(list_t *list) {
	if (list == NULL) list_err("list_activatepriority: list = NULL");
	list->haspriority = true;
	list->priority = list_copy(list);
	list_sort(list->priority);
}
void list_deactivatepriority(list_t *list) {
	if (list == NULL) list_err("list_deactivatepriority: list = NULL");
	if (list->priority == NULL) list_err("list_deactivatepriority: list->priority = NULL");
	list->haspriority = false;
	list_destroy(list->priority);
}
void *list_poppriority(list_t *list) {
	if (list == NULL) list_err("list_deactivatepriority: list = NULL");
	if (list->priority == NULL) list_err("list_deactivatepriority: list->priority = NULL");
	if (!list->priority->size) list_err("list_deactivatepriority: list->priority = NULL");
	return list_popitem(list, list_popfirst(list->priority));
}
void *list_getpriority(list_t *list) {
	if (list == NULL) list_err("list_deactivatepriority: list = NULL");
	if (list->priority == NULL) list_err("list_deactivatepriority: list->priority = NULL");
	return list_getfirst(list->priority);
}

/*
 * Hashmap
 */

// Hashmap
unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
void error_check(void *input) {
	if (input == NULL) list_err("fuc u");
}
int map_resize(map_t *map) {
	list_t *tmp_list = list_create(map->cmpfunc);
	void *tmp_item;
	for (int i = 0; i < map->maxsize; i++) {
		if (map->hashtable[i] != NULL) {
			while (list_size(map->hashtable[i]) > 0)
				list_addlast(tmp_list, list_popfirst(map->hashtable[i]));
		}
	}
	map->maxsize = map->maxsize * 2;
	map->hashtable = calloc(sizeof(list_t*), map->maxsize);
	while (list_size(tmp_list) > 0) {
		tmp_item = list_popfirst(tmp_list);
		map_put(map, ((mapnode_t*)tmp_item)->key);
	}
	list_destroy(tmp_list);
	return 0;
}
mapnode_t *map_new_node(void *key) {
	mapnode_t *newnode = malloc(sizeof(mapnode_t));
	error_check(newnode);
	newnode->key = key;
	return newnode;
}
map_t *map_create(cmpfunc_t cmpfunc) {
	map_t *map = malloc(sizeof(map_t));
	error_check(map);
	map->size = 0;
	map->maxsize = 10;
	map->hashtable = calloc(sizeof(list_t*), map->maxsize);
	map->cmpfunc = cmpfunc;
	return map;
}
void map_destroy(map_t *map) {
	for (int i = 0; i < map->maxsize; i++)
		if (map->hashtable[i] != NULL)
			list_destroy(map->hashtable[i]);
	free(map->hashtable);
	map->hashtable = NULL;
	free(map);
	map = NULL;
}
void map_replacecmpfunc(map_t *map, cmpfunc_t cmpfunc) {
	map->cmpfunc = cmpfunc;
}
void map_put(map_t *map, void *key) {
	unsigned long hashval = djb2(key);
	int idx = hashval % map->maxsize;
	if (map_haskey(map, key) == 0) {
		if (map->hashtable[idx] == NULL) {
			map->hashtable[idx] = list_create(map->cmpfunc);
			map->size++;
		}
		list_addlast(map->hashtable[idx], map_new_node(key));
		if (map->size >= map->maxsize / 2)
			map_resize(map);
	}
	else {
		list_iter_t *iter = list_createiter(map->hashtable[idx]);
		void *tmp_item;
		while (list_hasnext(iter)) {
			tmp_item = list_next(iter);
			if (djb2(((mapnode_t*)tmp_item)->key) == hashval)
				if (!map->cmpfunc(((mapnode_t*)tmp_item)->key, key))
					break;
		}
	}
}
// TODO: can david check that this seems right
void map_remove(map_t *map, void *key) {
	if (map_haskey(map, key) == 0) list_err("map_remove: cannot remove something that is not here");
	unsigned long hashval = djb2(key);
	int idx = hashval % map->maxsize;
	list_popitem(map->hashtable[idx], key);
}
int map_haskey(map_t *map, void *key) {
	unsigned long hashval = djb2(key);
	int idx = hashval % map->maxsize;
	if (map->hashtable[idx] == NULL)
		return 0;
	list_iter_t *iter = list_createiter(map->hashtable[idx]);
	void *tmp_item;
	while (list_hasnext(iter)) {
		tmp_item = list_next(iter);
		if (djb2(((mapnode_t*)tmp_item)->key) == hashval) {
			if (!map->cmpfunc(((mapnode_t*)tmp_item)->key, key))
				return 1;
		}
	}
	return 0;
}
