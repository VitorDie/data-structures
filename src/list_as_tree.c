#include <stdlib.h>
#include "list_as_tree.h"
#include "tree_as_graph.h"
#include "tree.h"

/* A Matéria da Lista */
struct list_as_tree {
    struct tree motor_arvore;                 /* A interface da árvore herdada */
    struct tree_as_graph *instancia_concreta; /* A matéria da árvore */
    int head_id;                              /* O Gênesis (Início da linha) */
    int tail_id;                              /* O Fronteira (Fim da linha) */
};

/* --- A Implementação da Lei (Negação da Ramificação) --- */

static int get_head_impl(void *object) {
    return ((struct list_as_tree *)object)->head_id;
}

static int get_tail_impl(void *object) {
    return ((struct list_as_tree *)object)->tail_id;
}

static void append_impl(void *object, int value) {
    struct list_as_tree *lat = (struct list_as_tree *)object;
    
    /* A Mágica do Estrangulamento:
       Nós pegamos a interface da árvore e dizemos: 
       "Adicione um filho à CAUDA ATUAL". 
       O usuário perdeu a liberdade de escolher o pai. */
    struct tree t = lat->motor_arvore;
    t.add_child(t.object, lat->tail_id, value);
    
    /* A linha avançou, a cauda agora é o novo valor */
    lat->tail_id = value;
}

/* --- Construtores e Polimorfismo --- */

struct list_as_tree *create_list_as_tree(int initial_value) {
    struct list_as_tree *lat = malloc(sizeof(struct list_as_tree));
    if (lat != NULL) {
        /* A Lista nasce de uma Árvore */
        lat->instancia_concreta = create_tree_as_graph(initial_value);
        lat->motor_arvore = tree_as_graph_as_tree(lat->instancia_concreta);
        
        /* No nascimento, com 1 elemento, a cabeça e a cauda são o mesmo nó */
        lat->head_id = initial_value;
        lat->tail_id = initial_value;
    }
    return lat;
}

void destroy_list_as_tree(struct list_as_tree *lat) {
    if (lat != NULL) {
        destroy_tree_as_graph(lat->instancia_concreta);
        free(lat);
    }
}

struct list list_as_tree_as_list(struct list_as_tree *lat) {
    struct list l;
    l.base_tree = lat->motor_arvore;
    l.object = lat;
    l.append = append_impl;
    l.get_head = get_head_impl;
    l.get_tail = get_tail_impl;
    return l;
}