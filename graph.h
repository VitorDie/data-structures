#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "vertex.h"
#include "edge.h"

/* Forward declarations */
struct enumeration;
struct visitor;
struct pre_post_visitor;

/* Interface Graph */
struct graph {
    void *object;

    int (*get_number_of_edges)(void *object);
    int (*get_number_of_vertices)(void *object);
    bool (*is_directed)(void *object);

    void (*add_vertex)(void *object, int v);
    void (*add_vertex_with_weight)(void *object, int v, void *weight); /* Sobrecarga resolvida */
    struct vertex (*get_vertex)(void *object, int v);

    void (*add_edge)(void *object, int v, int w);
    void (*add_edge_with_weight)(void *object, int v, int w, void *weight); /* Sobrecarga resolvida */
    struct edge (*get_edge)(void *object, int v, int w);
    bool (*is_edge)(void *object, int v, int w);

    // bool (*is_connected)(void *object);
    // bool (*is_cyclic)(void *object);

    // struct enumeration *(*get_vertices)(void *object);
    // struct enumeration *(*get_edges)(void *object);

    // void (*depth_first_traversal)(void *object, struct pre_post_visitor *visitor, int start);
    // void (*breadth_first_traversal)(void *object, struct visitor *visitor, int start);
};

#endif /* GRAPH_H */