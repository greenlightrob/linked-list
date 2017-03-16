#include <stdlib.h>
#include <stdio.h>
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

cmpfunc_t get_cmpfunc(list_t *list) {
	return list->cmpfunc;
}

void failcheck(void *x) {
	if (x == NULL) {
		fatal_error("Error: Failed malloc!");
		exit(1);
	}
}
list_t *list_create(cmpfunc_t cmpfunc) {
	list_t *tmp_list = malloc(sizeof(list_t));
	failcheck(tmp_list);
	tmp_list->cmpfunc = cmpfunc;
	tmp_list->head = NULL;
	tmp_list->tail = NULL;
	tmp_list->size = 0;
	return tmp_list;
}
void list_destroy(list_t *list) {
	if (list->size > 0) {
		for (;(list->head->next != NULL) && (list->head != NULL);) {
			list->head = list->head->next;
			free(list->head->prev);
		}
		free(list->head);
	}
	free(list);
	return;
}
int list_size(list_t *list) {
	return list->size;
}
void list_addfirst(list_t *list, void *item) {
	node_t *tmp_node = malloc(sizeof(node_t));
	failcheck(tmp_node);

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
	node_t *tmp_node = malloc(sizeof(node_t));
	failcheck(tmp_node);

	tmp_node->next = NULL;
	tmp_node->prev = list->tail;
	tmp_node->item = item;

	if (list->size == 0) list->head = tmp_node;
	else list->tail->next = tmp_node;
	
	list->tail = tmp_node;
	list->size++;
	return;
}
void *list_popfirst(list_t *list) {
	if (list->head == NULL) return 0;
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
	if (list->tail == NULL) return 0;
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
int list_contains(list_t *list, void *item) {
	if (list->size == 0) return 0;
	node_t *tmp_node = list->head;

	for (;tmp_node != NULL; tmp_node = tmp_node->next)
		if (list->cmpfunc(tmp_node->item, item) == 0) return 1;

	return 0;
}
node_t *_list_quicksort(node_t *left, node_t *right, cmpfunc_t cmpfunc) {	

	// One node
	if (left->next == NULL) return left;

	// Two nodes
	void *tmp;
	if (left->next == right) {
		if (cmpfunc(left->item, right->item) > 0) {
			tmp = left->item;
			left->item = right->item;
			right->item = tmp;
		}
		return left;
	}
	node_t *pivot = left;
	left = left->next;
	node_t *tmp_l = left;
	node_t *tmp_r = right;
	// Used to ensure left or right moves
	int l = 0, r = 0;

	for (; tmp_r->next != NULL; tmp_r = tmp_r->next);

	// Moving and swaping left and right
	for (; cmpfunc(left->item, right->item) != 0;) {
		for (; cmpfunc(left->item, pivot->item) < 0; l = 1) {
			l = -1;
			if (left->next == NULL || left == right) break;
			left = left->next;
		}
		for (; cmpfunc(right->item, pivot->item) > 0; r = -1) {
			r = 1;
			if (right->prev == NULL || right == left) break;
			right = right->prev;
		}
		if (cmpfunc(left->item, right->item) != 0) {
			tmp = left->item;
			left->item = right->item;
			right->item = tmp;
		}
		else break;
	}
	
	// Checking movement outcome
	if (l == 0) left = NULL;
	else if (r == 0) right = NULL;
	else {
		left = left->prev;
		left->next = NULL;
		right->prev = NULL;
	}
	
	// Recursive
	if (left != NULL) left = _list_quicksort(tmp_l, left, cmpfunc);
	if (right != NULL) right = _list_quicksort(right, tmp_r, cmpfunc);

	// Merging
	// Only right moved
	if (left == NULL) {
		tmp_l = pivot;
		pivot->next = right;
		pivot->prev = NULL;
		right->prev = pivot;
	}
	// Only left moved
	else if (right == NULL) {
		tmp_l = left;
		pivot->next = NULL;
		for (; left->next != NULL;) left = left->next;
		pivot->prev = left;
		left->next = pivot;
	}
	// Both left and right moved
	else {
		tmp_l = left;
		for (; left->next != NULL;) left = left->next;
		pivot->next = right;
		pivot->prev = left;
		left->next = pivot;
		right->prev = pivot;
	}
	return tmp_l;
}
void list_sort(list_t *list) {

	node_t *head = list->head;
	node_t *tail = list->tail;
	cmpfunc_t cmpfunc = list->cmpfunc;
	list->head = _list_quicksort(head, tail, cmpfunc);
}
list_iter_t *list_createiter(list_t *list) {
	if (list == NULL) return NULL;
	list_iter_t *tmp_iter = malloc(sizeof(list_iter_t));
	failcheck(tmp_iter);

	tmp_iter->node = list->head;
	return tmp_iter;
}
void list_copy_iter(list_iter_t *a, list_iter_t *b) {
	b->node = a->node;
}
void list_destroyiter(list_iter_t *iter) {
	if (iter == NULL) return;
	free(iter);
}
int list_hasnext(list_iter_t *iter) {
	if (iter == NULL || iter->node == NULL) return 0;
	else return 1;
}
void *list_getitem(list_iter_t *iter) {
	if (iter->node == NULL) return NULL;
	return iter->node->item;
}
void list_replaceitem(list_iter_t *iter, void *item) {
	iter->node->item = item;
}
void list_itermovenext(list_iter_t *iter) {
	if (iter == NULL || iter->node == NULL) return;
	iter->node = iter->node->next;
}
void list_itermoveprev(list_iter_t *iter) {

	if (iter == NULL || iter->node == NULL) return;
	iter->node = iter->node->prev;
}
void *list_next(list_iter_t *iter) {
	if (iter == NULL || iter->node == NULL) return NULL;
	void *tmpitem = list_getitem(iter);
	list_itermovenext(iter);
	return tmpitem;
}
void *list_prev(list_iter_t *iter) {
	if (iter == NULL || iter->node == NULL) return NULL;
	void *tmp_item = iter->node->item;
	iter->node = iter->node->prev;
	return tmp_item;
}
void *list_pop(list_t *list, list_iter_t *iter, char direction) {
	if (list == NULL) fatal_error("list_remove: list does not exist");
	if (iter == NULL) fatal_error("list_remove: list iter does not exist");
	if (list_size(list) == 0) fatal_error("list_remove: list has no items");
	if (iter->node == NULL) fatal_error("list_remove: iter->node is NULL");

	listnode_t *trash = iter->node;
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
void list_popnext(list_t *list, list_iter_t *iter) {
	list_pop(list, iter, 'n');
}
void list_popprev(list_t *list, list_iter_t *iter) {
	list_pop(list, iter, 'p');
}
void list_add(list_t *list, list_iter_t *iter, void *item, char direction) {
	// edgecase checking
	if (list_size(list) == 0) list_addfirst(list, item);
	else if (iter->node == list->head && direction == 'p')
		list_addfirst(list, item);
	else if (iter->node == list->tail && direction == 'n')
		list_addlast(list, item);
	else {
		node_t *new_node = malloc(sizeof(node_t));
		failcheck(tmp_node);
		if (direction == 'n') {
			iter->node->next->prev = new_node;
			new_node->next = iter->node->next;
			new_node->prev = iter->node;
			iter->node->next = new_node;
		}
		else if (direction == 'p') {
			iter->node->prev->next = new_node;
			new_node->prev = iter->node->prev;
			new_node->next = iter->node;
			iter->node->prev = new_node;
		}
		tmp_node->item = item;
		list->size++;
	}
	return;
}
void list_addnext(list_t *list, list_iter_t *iter) {
	list_add(list, iter, 'n');
}
void list_addprev(list_t *list, list_iter_t *iter) {
	list_add(list, iter, 'p');
}

// Debugging
int list_countsize(list_t *list) {
	list_iter_t *iter = list_createiter(list);
	int i;
	printf("\nCounting list size\n");
	for (i = 0; list_hasnext(iter) == 1;) {
		i++;
		printf("Tmp i = %d\n", i);
		list_next(iter);
	}
	printf("Done\n");
	return i;
}
