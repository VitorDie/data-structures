#ifndef LIST_AS_TREE_H
#define LIST_AS_TREE_H

#include "list.h"

struct list_as_tree;

/* A lista precisa de um primeiro elemento para nascer (a 'head' que é a raiz da árvore oculta) */
struct list_as_tree *create_list_as_tree(int initial_value);
void destroy_list_as_tree(struct list_as_tree *lat);

/* O polimorfismo: extraindo a interface Lista a partir da matéria */
struct list list_as_tree_as_list(struct list_as_tree *lat);

#endif /* LIST_AS_TREE_H */