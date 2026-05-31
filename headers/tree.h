#ifndef TREE_H
#define TREE_H

#include "graph.h"

/* A Interface da Árvore */
struct tree {
    struct graph base_graph; /* Preserva a essência do Grafo */
    void *object;

    int (*get_root)(void *object);
    int (*get_parent)(void *object, int child);
    void (*add_child)(void *object, int parent, int child);
};

#endif /* TREE_H */