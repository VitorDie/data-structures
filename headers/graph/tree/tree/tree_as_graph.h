#ifndef TREE_AS_GRAPH_H
#define TREE_AS_GRAPH_H

#include "tree.h"

struct tree_as_graph;

/* O construtor de uma árvore sempre exige a definição do 'Gênesis' (a Raiz) */
struct tree_as_graph *create_tree_as_graph(int root_id);
void destroy_tree_as_graph(struct tree_as_graph *tag);

struct tree tree_as_graph_as_tree(struct tree_as_graph *tag);

#endif /* TREE_AS_GRAPH_H */