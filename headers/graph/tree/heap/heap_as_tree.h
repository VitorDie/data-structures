#ifndef HEAP_AS_TREE_H
#define HEAP_AS_TREE_H

#include "heap.h"

struct heap_as_tree;

/* O Heap nasce com um primeiro Rei (a raiz da árvore oculta) */
struct heap_as_tree *create_heap_as_tree(int initial_value);
void destroy_heap_as_tree(struct heap_as_tree *hat);

struct heap heap_as_tree_as_heap(struct heap_as_tree *hat);

#endif /* HEAP_AS_TREE_H */