#ifndef DIRECTORY_AS_TREE_H
#define DIRECTORY_AS_TREE_H

#include "directory.h"

struct directory_as_tree;

/* O Sistema Operativo arranca com a montagem da raiz '/' */
struct directory_as_tree *create_directory_as_tree(int root_id, const char *root_name);
void destroy_directory_as_tree(struct directory_as_tree *dat);

struct directory directory_as_tree_as_directory(struct directory_as_tree *dat);

#endif /* DIRECTORY_AS_TREE_H */