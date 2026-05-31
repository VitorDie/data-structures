#include <stdlib.h>
#include "tree_as_graph.h"
#include "graph.h"
#include "graph_as_matrix.h"

struct tree_as_graph {
    struct graph motor_grafo;
    struct graph_as_matrix *instancia_concreta;
    int root_id;
};

/* --- Métodos Exclusivos da Árvore --- */

static int get_root_impl(void *object) {
    return ((struct tree_as_graph *)object)->root_id;
}

static int get_parent_impl(void *object, int child) {
    struct tree_as_graph *tag = (struct tree_as_graph *)object;
    struct graph g = tag->motor_grafo;
    
    // Na nossa matriz, a coluna representa o "Destino" (o filho). 
    // Então procuramos qual linha (o pai) tem uma aresta apontando para essa coluna.
    // Como limitamos a 50 na matriz atual, varremos até 50.
    for (int i = 0; i < 50; i++) {
        if (g.is_edge(g.object, i, child)) {
            return i;
        }
    }
    return -1; // Retorna -1 se não encontrar (ex: a própria raiz não tem pai)
}

static void add_child_impl(void *object, int parent, int child) {
    struct tree_as_graph *tag = (struct tree_as_graph *)object;
    struct graph g = tag->motor_grafo;
    
    /* A LEI DA ÁRVORE:
       1. O pai DEVE já existir na árvore.
       2. O filho NÃO PODE existir na árvore (se já existir, ele já tem pai, ou é a raiz).
       Garantindo isso, nós proibimos matematicamente a criação de ciclos. */
       
    bool parent_exists = (g.get_vertex(g.object, parent).object != NULL);
    bool child_exists = (g.get_vertex(g.object, child).object != NULL);

    if (parent_exists && !child_exists) {
        g.add_vertex(g.object, child);
        g.add_edge(g.object, parent, child);
    }
}

/* --- API Pública --- */

struct tree_as_graph *create_tree_as_graph(int root_id) {
    struct tree_as_graph *tag = malloc(sizeof(struct tree_as_graph));
    if (tag != NULL) {
        /* A Árvore baseia-se num digrafo (as conexões são de Pai -> Filho) */
        tag->instancia_concreta = create_graph_as_matrix(true);
        tag->motor_grafo = graph_as_matrix_as_graph(tag->instancia_concreta);
        tag->root_id = root_id;
        
        /* O "Fiat Lux" (Faça-se a Luz): A árvore já nasce com a sua raiz */
        tag->motor_grafo.add_vertex(tag->motor_grafo.object, root_id);
    }
    return tag;
}

void destroy_tree_as_graph(struct tree_as_graph *tag) {
    if (tag != NULL) {
        destroy_graph_as_matrix(tag->instancia_concreta);
        free(tag);
    }
}

struct tree tree_as_graph_as_tree(struct tree_as_graph *tag) {
    struct tree t;
    t.base_graph = tag->motor_grafo;
    t.object = tag;
    t.get_root = get_root_impl;
    t.get_parent = get_parent_impl;
    t.add_child = add_child_impl;
    return t;
}