#include <stdlib.h>
#include "graph_edge.h"

/* Estado interno da Aresta, guardando as interfaces dos vértices [cite: 331-335] */
struct graph_edge {
    struct vertex v0;
    struct vertex v1;
    void *weight;
    bool directed;
};

/* --- Métodos Privados --- */
static struct vertex get_v0_impl(void *object) {
    struct graph_edge *ge = (struct graph_edge *)object;
    return ge->v0;
}

static struct vertex get_v1_impl(void *object) {
    struct graph_edge *ge = (struct graph_edge *)object;
    return ge->v1;
}

static void *get_weight_impl(void *object) {
    struct graph_edge *ge = (struct graph_edge *)object;
    return ge->weight;
}

static bool is_directed_impl(void *object) {
    struct graph_edge *ge = (struct graph_edge *)object;
    return ge->directed;
}

static struct vertex get_mate_impl(void *object, struct vertex v) {
    struct graph_edge *ge = (struct graph_edge *)object;
    
    /* Se v for igual a v0, retorna v1. Se for v1, retorna v0. */
    if (vertex_compare(v, ge->v0) == 0) {
        return ge->v1;
    } else if (vertex_compare(v, ge->v1) == 0) {
        return ge->v0;
    }
    
    /* Se o vértice não pertence à aresta, retorna uma interface "nula" */
    struct vertex null_vertex = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    return null_vertex;
}

/* --- API Pública Concreta --- */

struct graph_edge *create_graph_edge(struct vertex v0, struct vertex v1, void *weight, bool directed) {
    struct graph_edge *ge = malloc(sizeof(struct graph_edge));
    if (ge != NULL) {
        ge->v0 = v0;
        ge->v1 = v1;
        ge->weight = weight;
        ge->directed = directed;
    }
    return ge;
}

void destroy_graph_edge(struct graph_edge *ge) {
    if (ge != NULL) {
        free(ge);
    }
}

/* Polimorfismo: Preenche a vtable [cite: 1053-1057] */
struct edge graph_edge_as_edge(struct graph_edge *ge) {
    struct edge e;
    e.object = ge;
    e.get_v0 = get_v0_impl;
    e.get_v1 = get_v1_impl;
    e.get_weight = get_weight_impl;
    e.is_directed = is_directed_impl;
    e.get_mate = get_mate_impl;
    return e;
}

/* --- Comparable --- */
int edge_compare(struct edge e1, struct edge e2) {
    if (e1.object == NULL || e2.object == NULL) return 0;
    
    /* Em algoritmos de grafos (Kruskal, Prim), arestas são comparadas pelo peso.
     * Assumimos aqui que o peso é um (int *) para simplificar. 
     * Uma implementação de produção exigiria um callback de comparação no create_graph_edge. */
    void *w1 = e1.get_weight(e1.object);
    void *w2 = e2.get_weight(e2.object);
    
    if (w1 != NULL && w2 != NULL) {
        return (*(int *)w1) - (*(int *)w2);
    }
    return 0; /* Se não há peso, consideramos iguais */
}