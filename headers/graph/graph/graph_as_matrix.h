#ifndef GRAPH_AS_MATRIX_H
#define GRAPH_AS_MATRIX_H

#include <stdbool.h>
#include "graph.h"

/* Estrutura opaca */
struct graph_as_matrix;

/* Construtor e Destrutor */
struct graph_as_matrix *create_graph_as_matrix(bool directed);
void destroy_graph_as_matrix(struct graph_as_matrix *gam);

/* Polimorfismo: Converte a matriz para a interface genérica */
struct graph graph_as_matrix_as_graph(struct graph_as_matrix *gam);

#endif /* GRAPH_AS_MATRIX_H */