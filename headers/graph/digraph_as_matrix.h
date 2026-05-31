#ifndef DIGRAPH_AS_MATRIX_H
#define DIGRAPH_AS_MATRIX_H

#include "digraph.h"

/* Estrutura opaca */
struct digraph_as_matrix;

/* Construtor (inerentemente direcionado) e Destrutor */
struct digraph_as_matrix *create_digraph_as_matrix(void);
void destroy_digraph_as_matrix(struct digraph_as_matrix *dgam);

/* Polimorfismo: Converte a matriz para a interface do Digraph */
struct digraph digraph_as_matrix_as_digraph(struct digraph_as_matrix *dgam);

#endif /* DIGRAPH_AS_MATRIX_H */