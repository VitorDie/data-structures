#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "tree.h"
#include <stdbool.h>

/* A Desigualdade de Classes (Nobreza vs Operários) */
typedef enum {
    NODE_FILE,
    NODE_FOLDER
} node_type;

/* A Interface do File System (VFS) */
struct directory {
    struct tree base_tree; /* A Substância Suprassumida (A Árvore) */
    void *object;

    /* Os Comandos de Sistema Operativo */
    bool (*mkdir)(void *object, int parent_id, int new_id, const char *name);
    bool (*touch)(void *object, int parent_id, int new_id, const char *name);
    
    /* A Visão */
    void (*ls)(void *object, int folder_id);
};

#endif /* DIRECTORY_H */