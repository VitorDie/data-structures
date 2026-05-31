#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <stdbool.h>
#include "graph.h"

struct visitor;

/* Interface Digraph (Herda de Graph) */
struct digraph {
    struct graph base_graph; /* Herança por alinhamento de memória  */

    bool (*is_strongly_connected)(void *object);
    void (*topological_order_traversal)(void *object, struct visitor *visitor);
};

#endif /* DIGRAPH_H */