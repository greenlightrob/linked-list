#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
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

// Internal general functions
void list_err(char *msg, ...) {
	fprintf (stderr, "fatal error in linkedlist: ");
	va_list args;
	va_start (args, msg);
	vfprintf (stderr, msg, args);
	va_end (args);
	fputc ('\n', stderr);
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
		list->head == NULL;
		list->tail == NULL;
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
	return tmpitem;
}

// Creating and destroying list
list_t *list_create(cmpfunc_t cmpfunc) {
	list_t *tmp_list = malloc(sizeof(list_t));
	if (tmp_list == NULL) list_err("list_create: failed to allocate memory");
	if (cmpfunc == NULL) list_err("list_create: cmpfunc = NULL");
	tmp_list->cmpfunc = cmpfunc;
	tmp_list->head = NULL;
	tmp_list->tail = NULL;
	tmp_list->hasmap = false;
	tmp_list->size = 0;
	return tmp_list;
}
void list_destroy(list_t *list) {
	if (list == NULL) list_err("list_destroy: list = NULL");
	if (list->hasmap) map_destroy(list->map);
	while (list->size > 0) list_poplast(list);
	free(list);
	return;
}
void list_deepdestroy(list_t *list, destroyfunc_t destroyfunc) {
	if (list == NULL) list_err("list_deepdestroy: list = NULL");
	if (list->hasmap) map_destroy(list->map);
	if (list->size > 0) destroyfunc(list_poplast(list));
	free(list);
	return;
}

void list_usehashmap(list_t *list) {
	list->map = map_create(list->cmpfunc);
	list_iter_t *iter = list_createiter(list);
	while (list_hasnext(iter))
		map_put(list->map, list_next(iter));
	list->hasmap = true;
}
void list_replacecmpfunc(list_t *list, cmpfunc_t cmpfunc) {
	if (list == NULL) list_err("list_replacefunc: list = NULL");
	if (cmpfunc == NULL) list_err("list_replacefunc: cmpfunc = NULL");
	list->cmpfunc = cmpfunc;
	if (list->hasmap) map_replacecmpfunc(list->map, cmpfunc);
}

// Getting list info
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

// Sorting list
void list_sort(list_t *list) {
	// list_err("list sort is not implemented yet");
	list_err("list sort is not implemented yet");
}

// Copying list
list_t *list_copy(list_t *list) {
	if (list == NULL) list_err("list_copy: list = NULL");
	list_t *copy = list_create(list->cmpfunc);
	if (list->hasmap) list_usehashmap(copy);
	list_iter_t *iter = list_createiter(list);
	while (list_hasnext(iter))
		list_addlast(copy, list_next(iter));
	return copy;
}

list_t *list_deepcopy(list_t *list, cpyfunc_t cpyfunc) {
	if (list == NULL) list_err("list_deepcopy: list = NULL");
	list_t *copy = list_create(list->cmpfunc);
	list_iter_t *iter = list_createiter(list);
	if (list->hasmap) list_usehashmap(copy);
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
void *list_popitem(list_t *list, void *item) {
	if (list == NULL) list_err("list_popitem: list = NULL");
	if (list->head == NULL) list_err("list_popitem: head = NULL");
	if (list->hasmap) map_remove(list->map, item);
	node_t *node = list->head;
	while (node->next) {
		if (list->cmpfunc(node->item, item) == 0) break;
		node = node->next;
	}
	if (list->cmpfunc(node->item, item) != 0) list_err("list_popitem: cannot remove something that is not here");

	return pop_node(list, node);
}
void list_remove(list_t *list, void *item, destroyfunc_t destroyfunc) {
	if (list == NULL) list_err("list_remove: list = NULL");
	if (list->head == NULL) list_err("list_remove: head = NULL");
	if (list->hasmap) map_remove(list->map, item);
	node_t *node = list->head;
	while (node->next) {
		if (list->cmpfunc(node->item, item) == 0) break;
		node = node->next;
	}
	if (list->cmpfunc(node->item, item) != 0) list_err("list_remove: cannot remove something that is not here");

	destroyfunc(pop_node(list, node));
}

// Popping items
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

// Getting the edge items of list
void *list_getlast(list_t *list) {
	if (list == NULL) list_err("list_getlast: list = NULL");
	if (list->tail == NULL) list_err("list_getlast: tail = NULL");
	if (list->size == 0) list_err("list_getlast: list->size = 0");
	return list->tail->item;
}
void *list_getfirst(list_t *list) {
	if (list == NULL) list_err("list_getfist: list = NULL");
	if (list->head == NULL) list_err("list_getfirst: head = NULL");
	if (list->size == 0) list_err("list_getfist: list->size = 0");
	return list->tail->item;
}

// Getting the item that is located at the num-th position
void *list_getitemnumfromfirst(list_t *list, int num) {
	if (list == NULL) list_err("list_getitemnumberfromfist: list = NULL");
	if (list->size == 0) list_err("list_getitemnumberfromfist: list->size = 0");
	if (num >= list->size) list_err("list_getitemnumberfromfirst: num is larger than list");
	node_t *tmp_node = list->head;
	for (int i = 0; i < num; i++) {
		if (tmp_node == NULL) list_err("list_getitemnumberfromfirst: cannot fetch next");
		if (tmp_node->next == NULL) list_err("list_getitemnumberfromfirst: cannot fetch next->next");
		tmp_node = tmp_node->next;
	}
	return tmp_node->item;
}
void *list_getitemnumfromlast(list_t *list, int num) {
	if (list == NULL) list_err("list_getitemnumberfromlast: list = NULL");
	if (list->size == 0) list_err("list_getitemnumberfromlast: list->size = 0");
	if (num >= list->size) list_err("list_getitemnumberfromflast: num is larger than list");
	node_t *tmp_node = list->tail;
	for (int i = 0; i < num; i++) {
		if (tmp_node == NULL) list_err("list_getitemnumberfromflast: cannot fetch prev");
		if (tmp_node->prev == NULL) list_err("list_getitemnumberfromflast: cannot fetch prev->prev");
		tmp_node = tmp_node->prev;
	}
	return tmp_node->item;
}

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
}
void list_resetiter(list_iter_t *iter) {
	if (iter->list == NULL) list_err("list_resetiter: list = NULL");
	if (iter == NULL) list_err("list_resetiter: iter = NULL");
	iter->node = iter->list->head;
}

// Check if current item has a node (hasprev would do the same)
int list_hasnext(list_iter_t *iter) {
	if (iter == NULL) list_err("list_hasnext: iter = NULL");
	if (iter->node == NULL) return 0;
	return 1;
}

// Check if iterator has node before or after
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

// Manipulating items with iterators
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
void list_replaceitem(list_iter_t *iter, void *item) {
	if (iter == NULL) list_err("list_replaceitem: iter = NULL");
	if (iter->node == NULL) list_err("list_replaceitem: iter->node = NULL");
	if (item == NULL) list_err("list_replaceitem: item = NULL");
	if (iter->list->hasmap) {
		map_remove(iter->list->map, iter->node->item);
		map_put(iter->list->map, item);
	}
	iter->node->item = item;
}

// Specific iterator moving
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

// Returning item the moving iterator
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

// Popping item then moving iterator
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

// Adding items in direction
void list_addafter(list_iter_t *iter, void *item) {
	if (iter == NULL) list_err("list_addafter: list iter does not exist");
	if (iter->list == NULL) list_err("list_addafter: list does not exist");
	if (item == NULL) list_err("list_addafter: item = NULL");

	if (iter->node == NULL || iter->list->size < 1 || iter->node == iter->list->head) {
		list_addfirst(iter->list, item);
		iter->node == iter->list->head; // hm
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
void list_addbefore(list_iter_t *iter, void *item) {
	if (iter == NULL) list_err("list_addbefore: list iter does not exist");
	if (iter->list == NULL) list_err("list_addbefore: list does not exist");
	if (item == NULL) list_err("list_addbrefore: item = NULL");

	if (iter->node == NULL || iter->list->size < 1 || iter->node == iter->list->tail) {
		list_addlast(iter->list, item);
		iter->node == iter->list->tail; // hm
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

// ----------

// List manipulations
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

}

// Hashmap
unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
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
	mapnode_t *tmpnode;
	for (int i = 0; i < map->maxsize; i++)
		if (map->hashtable[i] != NULL)
			list_destroy(map->hashtable[i]);
	free(map->hashtable);
	free(map);
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
