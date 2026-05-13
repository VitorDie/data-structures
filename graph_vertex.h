#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include "vertex.h"

/* estrutura opaca */ 
struct graph_vertex;

/* Construtor e Destrutor */
struct graph_vertex *create_graph_vertex(int number, void *weight);
void destroy_graph_vertex(struct graph_vertex *gv);

/* O "Cast" seguro que preenche a interface com as funções desta classe [cite: 1036-1037] */
struct vertex graph_vertex_as_vertex(struct graph_vertex *gv);

#endif /* GRAPH_VERTEX_H */