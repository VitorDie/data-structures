#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

struct vertex;
struct edge;
struct enumeration;
struct visitor;
struct pre_post_visitor;

/* Declaração da estrutura opaca */
struct graph;

/* Construtor e Destrutor */
struct graph *create_graph(void);
void destroy_graph(struct graph *g);

/* Métodos da interface Graph */
int graph_get_number_of_edges(struct graph *g);
int graph_get_number_of_vertices(struct graph *g);
bool graph_is_directed(struct graph *g);

void graph_add_vertex(struct graph *g, int v);
void graph_add_vertex_with_weight(struct graph *g, int v, void *weight);
struct vertex *graph_get_vertex(struct graph *g, int v);

void graph_add_edge(struct graph *g, int v, int w);
void graph_add_edge_with_weight(struct graph *g, int v, int w, void *weight);
struct edge *graph_get_edge(struct graph *g, int v, int w);
bool graph_is_edge(struct graph *g, int v, int w);

bool graph_is_connected(struct graph *g);
bool graph_is_cyclic(struct graph *g);

struct enumeration *graph_get_vertices(struct graph *g);
struct enumeration *graph_get_edges(struct graph *g);

void graph_depth_first_traversal(struct graph *g, struct pre_post_visitor *visitor, int start);
void graph_breadth_first_traversal(struct graph *g, struct visitor *visitor, int start);

#endif /* GRAPH_H */