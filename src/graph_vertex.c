#include <stdlib.h>
#include "graph_vertex.h"

/* O verdadeiro estado do vértice, oculto do mundo externo [cite: 331-335] */
struct graph_vertex {
    int number;
    void *weight;
    /* Aqui entrarão as instâncias das listas de adjacência futuramente */
};

/* --- Métodos Privados da Classe --- */
static int get_number_impl(void *object) {
    struct graph_vertex *gv = (struct graph_vertex *)object;
    return gv->number;
}

static void *get_weight_impl(void *object) {
    struct graph_vertex *gv = (struct graph_vertex *)object;
    return gv->weight;
}

static struct enumeration *get_incident_edges_impl(void *object) {
    (void)object; /* Silencia warning de variável não usada */
    return NULL;
}

static struct enumeration *get_emanating_edges_impl(void *object) {
    (void)object;
    return NULL;
}

static struct enumeration *get_predecessors_impl(void *object) {
    (void)object;
    return NULL;
}

static struct enumeration *get_successors_impl(void *object) {
    (void)object;
    return NULL;
}

/* --- API Pública Concreta --- */

struct graph_vertex *create_graph_vertex(int number, void *weight) {
    struct graph_vertex *gv = malloc(sizeof(struct graph_vertex));
    if (gv != NULL) {
        gv->number = number;
        gv->weight = weight;
    }
    return gv;
}

void destroy_graph_vertex(struct graph_vertex *gv) {
    if (gv != NULL) {
        free(gv);
    }
}

/* Preenche a interface com os ponteiros de função desta classe concreta [cite: 1053-1057] */
struct vertex graph_vertex_as_vertex(struct graph_vertex *gv) {
    struct vertex v;
    v.object = gv;
    v.get_number = get_number_impl;
    v.get_weight = get_weight_impl;
    v.get_incident_edges = get_incident_edges_impl;
    v.get_emanating_edges = get_emanating_edges_impl;
    v.get_predecessors = get_predecessors_impl;
    v.get_successors = get_successors_impl;
    return v;
}

/* --- Comparable --- */
int vertex_compare(struct vertex v1, struct vertex v2) {
    if (v1.object == NULL || v2.object == NULL) return 0;
    
    int num1 = v1.get_number(v1.object);
    int num2 = v2.get_number(v2.object);
    
    return num1 - num2;
}