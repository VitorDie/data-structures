#include <stdlib.h>
#include "digraph_as_matrix.h"
#include "graph_as_matrix.h"

/* O estado oculto do DigraphAsMatrix */
struct digraph_as_matrix {
    /* A substância: o motor que vai fazer o trabalho pesado [Padrão Decorator] */
    struct graph_as_matrix *motor_interno;
};

/* --- Métodos Exclusivos do Digrafo (Stubs para o TDD inicial) --- */

static bool is_strongly_connected_impl(void *object) {
    (void)object;
    /* Futuro: Implementar algoritmo de Kosaraju ou Tarjan aqui */
    return false;
}

static void topological_order_traversal_impl(void *object, struct visitor *visitor) {
    (void)object;
    (void)visitor;
    /* Futuro: Implementar ordenação topológica (Kahn ou DFS) */
}

/* --- API Pública Concreta --- */

struct digraph_as_matrix *create_digraph_as_matrix(void) {
    struct digraph_as_matrix *dgam = malloc(sizeof(struct digraph_as_matrix));
    if (dgam != NULL) {
        /* A regra de ouro: Ao instanciar o motor, FORÇAMOS ele a ser direcionado (true) */
        dgam->motor_interno = create_graph_as_matrix(true);
        
        if (dgam->motor_interno == NULL) {
            free(dgam);
            return NULL; /* Falha na alocação do motor */
        }
    }
    return dgam;
}

void destroy_digraph_as_matrix(struct digraph_as_matrix *dgam) {
    if (dgam != NULL) {
        /* Destruímos a dependência primeiro, depois o invólucro */
        destroy_graph_as_matrix(dgam->motor_interno);
        free(dgam);
    }
}

/* Polimorfismo: Montamos a Interface */
struct digraph digraph_as_matrix_as_digraph(struct digraph_as_matrix *dgam) {
    struct digraph dg;
    
    /* 1. Herança: Pegamos a interface do Grafo base gerada pelo motor */
    dg.base_graph = graph_as_matrix_as_graph(dgam->motor_interno);
    
    /* 2. Adicionamos os comportamentos VIPs do Digrafo */
    dg.is_strongly_connected = is_strongly_connected_impl;
    dg.topological_order_traversal = topological_order_traversal_impl;
    
    return dg;
}