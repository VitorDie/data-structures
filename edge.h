#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>
#include "vertex.h"

/* Interface Edge */
struct edge {
    void *object;

    struct vertex (*get_v0)(void *object);
    struct vertex (*get_v1)(void *object);
    void *(*get_weight)(void *object);
    bool (*is_directed)(void *object);
    struct vertex (*get_mate)(void *object, struct vertex v);
};

/* Extração do Comparable.compareTo */
int edge_compare(struct edge e1, struct edge e2);

#endif /* EDGE_H */