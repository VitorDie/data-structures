#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "directory_as_tree.h"
#include "tree_as_graph.h"
#include "tree.h"
#include "graph.h"

#define MAX_NODES 50

/* A Matéria do File System (VFS) */
struct directory_as_tree {
    struct tree motor_arvore;                  /* A Substância Herdada */
    struct tree_as_graph *instancia_concreta;
    
    /* Os Metadados (i-nodes) */
    char names[MAX_NODES][64];                 /* Os nomes dos ficheiros e pastas */
    node_type types[MAX_NODES];                /* A classe: FILE ou FOLDER */
};

/* --- A Implementação das Leis do SO --- */

static bool mkdir_impl(void *object, int parent_id, int new_id, const char *name) {
    struct directory_as_tree *dat = (struct directory_as_tree *)object;
    
    /* A Lei da Esterilidade: O pai TEM de ser uma Pasta! */
    if (dat->types[parent_id] != NODE_FOLDER) {
        return false; /* Acesso negado! Operários não podem ter filhos. */
    }
    
    /* Delegamos a criação física para a matemática da Árvore */
    struct tree t = dat->motor_arvore;
    t.add_child(t.object, parent_id, new_id);
    
    /* Registamos os metadados (O batismo do novo i-node) */
    dat->types[new_id] = NODE_FOLDER;
    strncpy(dat->names[new_id], name, 63);
    dat->names[new_id][63] = '\0'; /* Garantir terminação da string */
    
    return true;
}

static bool touch_impl(void *object, int parent_id, int new_id, const char *name) {
    struct directory_as_tree *dat = (struct directory_as_tree *)object;
    
    /* A Lei da Esterilidade */
    if (dat->types[parent_id] != NODE_FOLDER) {
        return false; /* Acesso negado! */
    }
    
    /* Criação física no Grafo */
    struct tree t = dat->motor_arvore;
    t.add_child(t.object, parent_id, new_id);
    
    /* Registamos os metadados como Ficheiro (Esterilidade decretada para este nó) */
    dat->types[new_id] = NODE_FILE;
    strncpy(dat->names[new_id], name, 63);
    dat->names[new_id][63] = '\0';
    
    return true;
}

static void ls_impl(void *object, int folder_id) {
    struct directory_as_tree *dat = (struct directory_as_tree *)object;
    
    if (dat->types[folder_id] != NODE_FOLDER) {
        printf("ls: impossivel aceder a '%s': Nao e uma pasta\n", dat->names[folder_id]);
        return;
    }

    /* O Sistema abre a interface do Grafo para ler a Matriz de Adjacência */
    struct graph g = dat->motor_arvore.base_graph;
    
    int count = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        /* Se existir uma aresta dirigida do folder_id para i, significa que 'i' é um filho! */
        if (g.is_edge(g.object, folder_id, i)) {
            if (dat->types[i] == NODE_FOLDER) {
                printf("[DIR]  %s\n", dat->names[i]);
            } else {
                printf("[FILE] %s\n", dat->names[i]);
            }
            count++;
        }
    }
    
    if (count == 0) {
        printf("(pasta vazia)\n");
    }
}

/* --- Construtores e Polimorfismo --- */

struct directory_as_tree *create_directory_as_tree(int root_id, const char *root_name) {
    struct directory_as_tree *dat = malloc(sizeof(struct directory_as_tree));
    if (dat != NULL) {
        /* O SO arranca montando a raiz física na Árvore */
        dat->instancia_concreta = create_tree_as_graph(root_id);
        dat->motor_arvore = tree_as_graph_as_tree(dat->instancia_concreta);
        
        /* Configuração do "Superbloco" / Raiz */
        dat->types[root_id] = NODE_FOLDER;
        strncpy(dat->names[root_id], root_name, 63);
        dat->names[root_id][63] = '\0';
    }
    return dat;
}

void destroy_directory_as_tree(struct directory_as_tree *dat) {
    if (dat != NULL) {
        destroy_tree_as_graph(dat->instancia_concreta);
        free(dat);
    }
}

struct directory directory_as_tree_as_directory(struct directory_as_tree *dat) {
    struct directory dir;
    dir.base_tree = dat->motor_arvore;
    dir.object = dat;
    dir.mkdir = mkdir_impl;
    dir.touch = touch_impl;
    dir.ls = ls_impl;
    return dir;
}