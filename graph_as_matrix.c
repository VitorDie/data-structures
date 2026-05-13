#include <stdlib.h>
#include "graph_as_matrix.h"

#define MAX_VERTICES 50 /* Limite estático para simplificar o TDD inicial */

/* Estado interno oculto do Grafo em Matriz */
struct graph_as_matrix {
    int number_of_vertices;
    int number_of_edges;
    bool directed;
    
    /* 1 significa aresta existe, 0 significa não existe */
    int matrix[MAX_VERTICES][MAX_VERTICES];
    
    /* Aqui futuramente guardaremos as instâncias de 'struct vertex' e 'struct edge' reais */
};

/* --- Métodos Privados --- */

static int get_number_of_vertices_impl(void *object) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    return gam->number_of_vertices;
}

static int get_number_of_edges_impl(void *object) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    return gam->number_of_edges;
}

static bool is_directed_impl(void *object) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    return gam->directed;
}

static void add_vertex_impl(void *object, int v) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    if (v >= 0 && v < MAX_VERTICES) {
        /* Para um grafo matriz simples, apenas garantimos que a contagem acompanhe o ID do vértice */
        if (v >= gam->number_of_vertices) {
            gam->number_of_vertices = v + 1;
        }
    }
}

static void add_vertex_with_weight_impl(void *object, int v, void *weight) {
    (void)weight; /* Ignorado nesta etapa básica */
    add_vertex_impl(object, v);
}

static void add_edge_impl(void *object, int v, int w) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    
    if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
        if (gam->matrix[v][w] == 0) {
            gam->matrix[v][w] = 1;
            gam->number_of_edges++;
            
            /* Se for não-direcionado, espelhamos a aresta na matriz */
            if (!gam->directed && v != w) {
                gam->matrix[w][v] = 1;
            }
        }
    }
}

static void add_edge_with_weight_impl(void *object, int v, int w, void *weight) {
    (void)weight; /* Ignorado nesta etapa básica */
    add_edge_impl(object, v, w);
}

static bool is_edge_impl(void *object, int v, int w) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
        return gam->matrix[v][w] == 1;
    }
    return false;
}

/* --- API Pública Concreta --- */

struct graph_as_matrix *create_graph_as_matrix(bool directed) {
    struct graph_as_matrix *gam = malloc(sizeof(struct graph_as_matrix));
    if (gam != NULL) {
        gam->number_of_vertices = 0;
        gam->number_of_edges = 0;
        gam->directed = directed;
        
        /* Zera a matriz */
        for (int i = 0; i < MAX_VERTICES; i++) {
            for (int j = 0; j < MAX_VERTICES; j++) {
                gam->matrix[i][j] = 0;
            }
        }
    }
    return gam;
}

void destroy_graph_as_matrix(struct graph_as_matrix *gam) {
    if (gam != NULL) {
        free(gam);
    }
}

/* Polimorfismo: Vincula a struct concreta à interface genérica */
struct graph graph_as_matrix_as_graph(struct graph_as_matrix *gam) {
    struct graph g;
    g.object = gam;
    g.get_number_of_vertices = get_number_of_vertices_impl;
    g.get_number_of_edges = get_number_of_edges_impl;
    g.is_directed = is_directed_impl;
    g.add_vertex = add_vertex_impl;
    g.add_vertex_with_weight = add_vertex_with_weight_impl;
    g.add_edge = add_edge_impl;
    g.add_edge_with_weight = add_edge_with_weight_impl;
    g.is_edge = is_edge_impl;
    return g;
}