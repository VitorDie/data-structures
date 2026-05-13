#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <stdbool.h>
#include "graph.h"

struct visitor;

/* Declaração da estrutura opaca */
struct digraph;

/* Construtor e Destrutor */
struct digraph *create_digraph(void);
void destroy_digraph(struct digraph *dg);

/* Métodos específicos do Digraph */
bool digraph_is_strongly_connected(struct digraph *dg);
void digraph_topological_order_traversal(struct digraph *dg, struct visitor *visitor);

/* * Função de Polimorfismo/Casting Seguro:
 * Retorna o ponteiro base para que métodos de 'graph.h' possam ser usados.
 */
struct graph *digraph_as_graph(struct digraph *dg);

#endif /* DIGRAPH_H */