/* Author: Steffen Viken Valvaag <steffenv@cs.uit.no> */
#ifndef LIST_H
#define LIST_H

typedef int (*cmpfunc_t)(void *, void *);
typedef void *(*cpyfunc_t)(void *);

struct list;
typedef struct list list_t;
struct list_iter;
typedef struct list_iter list_iter_t;

list_t *list_create(cmpfunc_t cmpfunc);
void list_destroy(list_t *list);
int list_size(list_t *list);
void list_addfirst(list_t *list, void *item);
void list_addlast(list_t *list, void *item);
void *list_popfirst(list_t *list);
void *list_poplast(list_t *list);
int list_contains(list_t *list, void *item);
void list_sort(list_t *list);

list_t *list_copy(list_t *list, cpyfunc_t cpyfunc);

void list_replacefunc(list_t *list, cmpfunc_t cmp);

// Iteration
list_iter_t *list_createiter(list_t *list);
void list_copyiter(list_iter_t *a, list_iter_t *b);
void list_destroyiter(list_iter_t *iter);
void list_resetiter(list_t *list, list_iter_t *iter);

int list_hasnext(list_iter_t *iter);
int list_hasbefore(list_iter_t *iter);
int list_hasafter(list_iter_t *iter);

void *list_getitem(list_iter_t *iter);
void *list_getbefore(list_iter_t *iter);
void *list_getafter(list_iter_t *iter);
void list_replaceitem(list_iter_t *iter, void *item);

void list_movenext(list_iter_t *iter);
void list_moveprev(list_iter_t *iter);

void *list_next(list_iter_t *iter);
void *list_prev(list_iter_t *iter);

// Iter goes next, and pops behind
void *list_popnext(list_t *list, list_iter_t *iter);
// Iter goes prev, and pops front
void *list_popprev(list_t *list, list_iter_t *iter);

void list_addnext(list_t *list, list_iter_t *iter, void *item);
void list_addprev(list_t *list, list_iter_t *iter, void *item);

// Debugging
int list_debug_countsize(list_t *list);

#endif
