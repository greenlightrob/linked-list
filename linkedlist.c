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

void list_err(char *msg, ...)
{
	fprintf (stderr, "fatal error: ");
	va_list args;
	va_start (args, msg);
	vfprintf (stderr, msg, args);
	va_end (args);
	fputc ('\n', stderr);
	exit (1);
}
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
		while ((list->head->next != NULL) && (list->head != NULL)) {
			list->head = list->head->next;
			free(list->head->prev);
		}
		free(list->head);
	}
	free(list);
	return;
}
int list_size(list_t *list) {
	if (list == NULL) list_err("list_size: list = NULL");
	// if (list->size != list_debug_countsize(list)) list_err("list_size: debugger found differences in list size");
	return list->size;
}
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
int list_contains(list_t *list, void *item) {
	if (list == NULL) list_err("list_contains: list = NULL");
	if (list->size == 0) list_err("list_contains: list->size = 0");
	if (item == NULL) list_err("list_contains: item = NULL");

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
/*
 * Merges two sorted lists a and b using the given comparison function.
 * Only assigns the next pointers; the prev pointers will have to be
 * fixed by the caller.  Returns the head of the merged list.
 */
static node_t *merge(node_t *a, node_t *b, cmpfunc_t cmpfunc)
{
    node_t *head, *tail;

    /* Pick the smallest head node */
    if (cmpfunc(a->item, b->item) < 0)
    {
        head = tail = a;
        a = a->next;
    }
    else
    {
        head = tail = b;
        b = b->next;
    }
    /* Now repeatedly pick the smallest head node */
    while (a != NULL && b != NULL)
    {
        if (cmpfunc(a->item, b->item) < 0)
        {
            tail->next = a;
            tail = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            tail = b;
            b = b->next;
        }
    }
    /* Append the remaining non-empty list (if any) */
    if (a != NULL)
    {
        tail->next = a;
    }
    else
    {
        tail->next = b;
    }
    return head;
}

/*
 * Splits the given list in two halves, and returns the head of
 * the second half.
 */
static node_t *splitlist(node_t *head)
{
    node_t *slow, *fast, *half;

    /* Move two pointers, a 'slow' one and a 'fast' one which moves
     * twice as fast.  When the fast one reaches the end of the list,
     * the slow one will be at the middle.
     */
    slow = head;
    fast = head->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    /* Now 'cut' the list and return the second half */
    half = slow->next;
    slow->next = NULL;
    return half;
}

/*
 * Recursive merge sort.  This function is named mergesort_ to avoid
 * collision with the mergesort function that is defined by the standard
 * library on some platforms.
 */
static node_t *_mergesort(node_t *head, cmpfunc_t cmpfunc)
{
    if (head->next == NULL)
    {
        return head;
    }
    else
    {
        node_t *half = splitlist(head);
        head = _mergesort(head, cmpfunc);
        half = _mergesort(half, cmpfunc);
        return merge(head, half, cmpfunc);
    }
}
// void list_sort(list_t *list) {
	// if (list == NULL) list_err("list_sort: list = NULL");
	// if (list->size == 0) return;
	// node_t *head = list->head;
	// node_t *tail = list->tail;
	// cmpfunc_t cmpfunc = list->cmpfunc;
	// list->head = _list_quicksort(head, tail, cmpfunc);
// }

void list_sort(list_t *list)
{
    if (list->head != NULL)
    {
        node_t *prev, *n;

        /* Recursively sort the list */
        list->head = _mergesort(list->head, list->cmpfunc);

        /* Fix the tail and prev links */
        prev = NULL;
        for (n = list->head; n != NULL; n = n->next)
        {
            n->prev = prev;
            prev = n;
        }
        list->tail = prev;
    }
}

void list_replacefunc(list_t *list, cmpfunc_t cmp) {
	list->cmpfunc = cmp;
}

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
int list_hasnext(list_iter_t *iter) {
	if (iter == NULL) list_err("list_hasnext: iter = NULL");
	if (iter->node == NULL) return 0;
	return 1;
}
void *list_getitem(list_iter_t *iter) {
	if (iter == NULL) list_err("list_getitem: iter = NULL");
	if (iter->node == NULL) list_err("list_getitem: iter->node = NULL");
	return iter->node->item;
}
void list_replaceitem(list_iter_t *iter, void *item) {
	if (iter == NULL) list_err("list_replaceitem: iter = NULL");
	if (iter->node == NULL) list_err("list_replaceitem: iter->node = NULL");
	if (item == NULL) list_err("list_replaceitem: item = NULL");
	iter->node->item = item;
}
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

// Debugging
// FIXME: Not working
int list_debug_countsize(list_t *list) {
	printf("entered de\n");
	node_t *current = list->head;
	int counter = 0;
	if (current->next == NULL) goto done;
	counter = 1;
	while (current != NULL) {
		if (current->next == NULL) goto done;
		current = current->next;
		counter++;
	}
	done:
		printf("list_debug_countsize: list->size is %d, counted size = %d\n", list->size, counter);
		return counter;

}
