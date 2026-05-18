#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include <stdbool.h>
#include "edge.h"
#include "vertex.h"

/* Estrutura opaca */
struct graph_edge;

/* Construtor (recebe as interfaces dos vértices) e Destrutor */
struct graph_edge *create_graph_edge(struct vertex v0, struct vertex v1, void *weight, bool directed);
void destroy_graph_edge(struct graph_edge *ge);

/* Cast seguro / Polimorfismo [cite: 1036-1037] */
struct edge graph_edge_as_edge(struct graph_edge *ge);

#endif /* GRAPH_EDGE_H */