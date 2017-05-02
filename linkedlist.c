#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "list.h"

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
};
struct list_iter {
	node_t *node;
};

// Internal general functions
void list_err(char *msg, ...) {
	fprintf (stderr, "fatal error: ");
	va_list args;
	va_start (args, msg);
	vfprintf (stderr, msg, args);
	va_end (args);
	fputc ('\n', stderr);
	exit (1);
}
node_t *create_node(void *item) {
	// fill
}

// Creating and destroying list
list_t *list_create(cmpfunc_t cmpfunc) {
	list_t *tmp_list = malloc(sizeof(list_t));
	if (tmp_list == NULL) list_err("list_create: failed to allocate memory");
	tmp_list->cmpfunc = cmpfunc;
	tmp_list->head = NULL;
	tmp_list->tail = NULL;
	tmp_list->size = 0;
	return tmp_list;
}
void list_destroy(list_t *list) {
	if (list == NULL) list_err("list_destroy: list = NULL");
	if (list->size > 0) {
		while ( (list->head != NULL) && (list->head->next != NULL)) {
			list->head = list->head->next;
			free(list->head->prev);
		}
		free(list->head);
	}
	free(list);
	return;
}
void list_deepdestroy(list_t *list, destroyfunc_t destroyfunc) {
	if (list == NULL) list_err("list_deepdestroy: list = NULL");
	if (list->size > 0) {
		while ( (list->head != NULL) && (list->head->next != NULL)) {
			list->head = list->head->next;
			destroyfunc(list->head->prev->item);
			free(list->head->prev);
		}
		destroyfunc(list->head->item);
		free(list->head);
	}
	free(list);
	return;
}

// Config
void list_replacecmpfunc(list_t *list, cmpfunc_t cmp) {
	if (list == NULL) list_err("list_replacefunc: list = NULL");
	list->cmpfunc = cmp;
}

// Getting list info
int list_size(list_t *list) {
	if (list == NULL) list_err("list_size: list = NULL");
	return list->size;
}
int list_contains(list_t *list, void *item) {
	if (list == NULL) list_err("list_contains: list = NULL");
	if (list->size == 0) list_err("list_contains: list->size = 0");
	if (item == NULL) list_err("list_contains: item = NULL");

	node_t *tmp_node = list->head;
	for (;tmp_node != NULL; tmp_node = tmp_node->next)
		if (list->cmpfunc(tmp_node->item, item) == 0) return 1;
	return 0;
}

// Sorting list
void list_sort(list_t *list) {
	printf("list sort is not implemented yet");
}

// Copying list
list_t *list_copy(list_t *list) {
	if (list == NULL) list_err("list_copy: list = NULL");
	list_t *copy = list_create(list->cmpfunc);
	list_iter_t *iter = list_createiter(list);
	while (list_hasnext(iter))
		list_addlast(copy, list_next(iter));
	return copy;
}
list_t *list_deepcopy(list_t *list, cpyfunc_t cpyfunc) {
	if (list == NULL) list_err("list_deepcopy: list = NULL");
	list_t *copy = list_create(list->cmpfunc);
	list_iter_t *iter = list_createiter(list);
	while (list_hasnext(iter))
		list_addlast(copy, cpyfunc(list_next(iter)));
	return copy;
}

// Adding items
void list_addfirst(list_t *list, void *item) {
	if (list == NULL) list_err("list_addfirst: list = NULL");
	if (item == NULL) list_err("list_addfirst: item = NULL");
	node_t *tmp_node = malloc(sizeof(node_t));
	if (tmp_node == NULL) list_err("list_addfirst: failed to allocate memory");

	tmp_node->prev = NULL;
	tmp_node->next = list->head;
	tmp_node->item = item;

	if (list->size == 0) list->tail = tmp_node;
	else list->head->prev = tmp_node;

	list->head = tmp_node;
	list->size++;
	return;
}
void list_addlast(list_t *list, void *item) {
	if (list == NULL) list_err("list_addlast: list = NULL");
	if (item == NULL) list_err("list_addlast: item = NULL");
	node_t *tmp_node = malloc(sizeof(node_t));
	if (tmp_node == NULL) list_err("list_addlast: failed to allocate memory");

	tmp_node->next = NULL;
	tmp_node->prev = list->tail;
	tmp_node->item = item;

	if (list->size == 0) list->head = tmp_node;
	else list->tail->next = tmp_node;
	
	list->tail = tmp_node;
	list->size++;
	return;
}

// Removing items
void list_remove(list_t *list, void *item) {
	if (list == NULL) list_err("list_remove: list = NULL");
	if (list->head == NULL) list_err("list_remove: head = NULL");
	node_t *node = list->head;	
	while(list->cmpfunc(node->item, item) != 0 && node) node = node->next;
	if (node) {
		if (list->size == 1);
		else if (node == list->head) list->head = NULL;
		else if (node == list->tail) list->tail = NULL;
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		free(node);
	}
}
void list_deepremove(list_t *list, void *item, destroyfunc_t destroyfunc) {
	if (list == NULL) list_err("list_remove: list = NULL");
	if (list->head == NULL) list_err("list_remove: head = NULL");
	node_t *node = list->head;	
	while(list->cmpfunc(node->item, item) != 0 && node) node = node->next;
	if (node) {
		if (list->size == 1);
		else if (node == list->head) list->head = NULL;
		else if (node == list->tail) list->tail = NULL;
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		destroyfunc(node->item);
		free(node);
	}
}

// Popping items
void *list_popfirst(list_t *list) {
	if (list == NULL) list_err("list_popfirst: list = NULL");
	if (list->head == NULL) list_err("list_popfirst: head = NULL");
	if (list->size == 0) list_err("list_popfirst: list->size = 0");
	void *tmp_item = list->head->item;
	if (list->size > 1) {
		list->head = list->head->next;
		free(list->head->prev);
		list->head->prev = NULL;
	}
	else {
 		free(list->head);
		list->head = NULL;
		list->tail = NULL;
	}
	list->size--;
	return tmp_item;
}
void *list_poplast(list_t *list) {
	if (list == NULL) list_err("list_poplast: list = NULL");
	if (list->tail == NULL) list_err("list_poplast: head = NULL");
	if (list->size == 0) list_err("list_poplast: list->size = 0");
	void *tmp_item = list->tail->item;
	if (list->size > 1) {
		list->tail = list->tail->prev;
		free(list->tail->next);
		list->tail->next = NULL;
	}
	else {
 		free(list->tail);
		list->head = NULL;
		list->tail = NULL;
	}
	list->size--;
	return tmp_item;
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
void list_resetiter(list_t *list, list_iter_t *iter) {
	if (list == NULL) list_err("list_resetiter: list = NULL");
	if (iter == NULL) list_err("list_resetiter: iter = NULL");
	iter->node = list->head;
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
void *list_pop(list_t *list, list_iter_t *iter, char direction) {
	if (list == NULL) list_err("list_pop: list does not exist");
	if (iter == NULL) list_err("list_pop: list iter does not exist");
	if (list->size == 0) list_err("list_pop: list has no items");
	if (iter->node == NULL) list_err("list_pop: iter->node is NULL");

	node_t *trash = iter->node;
	if (list->size == 1) {
		iter->node = NULL;
		list->head = NULL;
		list->tail = NULL;
	}
	else if (trash == list->head) {
		if (direction == 'n') iter->node = iter->node->next;
		if (direction == 'p') iter->node = NULL;
		return list_popfirst(list);
	}
	else if (trash == list->tail) {
		if (direction == 'n') iter->node = NULL;
		if (direction == 'p') iter->node = iter->node->prev;
		return list_poplast(list);
	}
	else {
		if (direction == 'n') iter->node = iter->node->next;
		if (direction == 'p') iter->node = iter->node->prev;
		trash->prev->next = trash->next;
		trash->next->prev = trash->prev;
	}
	void *item = trash->item;
	free(trash);
	list->size--;
	return item;
}
void *list_popnext(list_t *list, list_iter_t *iter) {
	return list_pop(list, iter, 'n');
}
void *list_popprev(list_t *list, list_iter_t *iter) {
	return list_pop(list, iter, 'p');
}

// Adding item in direction then moving iterator the same direction
void list_add(list_t *list, list_iter_t *iter, void *item, char direction) {
	if (list == NULL) list_err("list_add: list does not exist");
	if (iter == NULL) list_err("list_add: list iter does not exist");
	if (item == NULL) list_err("list_add: item = NULL");
	if (list->size == 0) {
		list_addfirst(list, item);
		iter->node = list->head;
	}
	else if (iter->node == NULL) list_err("list_add: iter->node = NULL");

	else if (iter->node == list->head && direction == 'p') {
		list_addfirst(list, item);
		iter->node = list->head;
	}
	else if (iter->node == list->tail && direction == 'n') {
		list_addlast(list, item);
		iter->node = list->tail;
	} 
	else {
		node_t *new_node = malloc(sizeof(node_t));
		if (new_node == NULL) list_err("list_add: failed to allcoate memory");
		if (direction == 'n') {
			iter->node->next->prev = new_node;
			new_node->next = iter->node->next;
			new_node->prev = iter->node;
			iter->node->next = new_node;
			iter->node = iter->node->next;
		}
		else if (direction == 'p') {
			iter->node->prev->next = new_node;
			new_node->prev = iter->node->prev;
			new_node->next = iter->node;
			iter->node->prev = new_node;
			iter->node = iter->node->prev;
		}
		new_node->item = item;
		list->size++;
	}
	return;
}
void list_addnext(list_t *list, list_iter_t *iter, void *item) {
	list_add(list, iter, item, 'n');
}
void list_addprev(list_t *list, list_iter_t *iter, void *item) {
	list_add(list, iter, item, 'p');
}

// Adding items in direction
void list_additem(list_t *list, list_iter_t *iter, void *item, char direction) {
	if (list == NULL) list_err("list_add: list does not exist");
	if (iter == NULL) list_err("list_add: list iter does not exist");
	if (item == NULL) list_err("list_add: item = NULL");
	if (list->size == 0) list_addfirst(list, item);
	else if (iter->node == NULL) list_err("list_add: iter->node = NULL");

	else if (iter->node == list->head && direction == 'a') list_addfirst(list, item);
	else if (iter->node == list->tail && direction == 'b') list_addlast(list, item); 
	else {
		node_t *new_node = malloc(sizeof(node_t));
		if (new_node == NULL) list_err("list_add: failed to allcoate memory");
		if (direction == 'a') {
			iter->node->next->prev = new_node;
			new_node->next = iter->node->next;
			new_node->prev = iter->node;
			iter->node->next = new_node;
		}
		else if (direction == 'b') {
			iter->node->prev->next = new_node;
			new_node->prev = iter->node->prev;
			new_node->next = iter->node;
			iter->node->prev = new_node;
		}
		new_node->item = item;
		list->size++;
	}
	return;
}
void list_addafter(list_t *list, list_iter_t *iter, void *item) {
	list_additem(list, iter, item, 'a');
}
void list_addbefore(list_t *list, list_iter_t *iter, void *item) {
	list_additem(list, iter, item, 'b');
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
void randomize(list_t *list) {

}
