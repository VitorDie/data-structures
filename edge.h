#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>

struct vertex;

/* Declaração da estrutura opaca */
struct edge;

/* Construtor e Destrutor */
struct edge *create_edge(struct vertex *v0, struct vertex *v1, void *weight, bool directed);
void destroy_edge(struct edge *e);

/* Métodos da interface Edge */
struct vertex *edge_get_v0(struct edge *e);
struct vertex *edge_get_v1(struct edge *e);
void *edge_get_weight(struct edge *e);
bool edge_is_directed(struct edge *e);
struct vertex *edge_get_mate(struct edge *e, struct vertex *v);

/* Equivalente ao Comparable.compareTo do Java */
int edge_compare(struct edge *e1, struct edge *e2);

#endif /* EDGE_H */