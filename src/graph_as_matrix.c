#include <stdlib.h>
#include "graph_as_matrix.h"
#include "graph_vertex.h"
#include "graph_edge.h"

#define MAX_VERTICES 50

/* O novo estado interno, agora com arrays para guardar as instâncias reais */
struct graph_as_matrix {
    int number_of_vertices;
    int number_of_edges;
    bool directed;
    
    /* Guarda as interfaces dos vértices instanciados */
    struct vertex array_of_vertices[MAX_VERTICES];
    
    /* Guarda as interfaces das arestas instanciadas (ou NULL no object se não existir) */
    struct edge matrix_of_edges[MAX_VERTICES][MAX_VERTICES];
};

/* --- Métodos Privados --- */

static int get_number_of_vertices_impl(void *object) {
    return ((struct graph_as_matrix *)object)->number_of_vertices;
}

static int get_number_of_edges_impl(void *object) {
    return ((struct graph_as_matrix *)object)->number_of_edges;
}

static bool is_directed_impl(void *object) {
    return ((struct graph_as_matrix *)object)->directed;
}

static void add_vertex_with_weight_impl(void *object, int v, void *weight) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    
    if (v >= 0 && v < MAX_VERTICES) {
        /* Se o vértice já existia, destruímos o antigo para evitar memory leak */
        if (gam->array_of_vertices[v].object != NULL) {
            destroy_graph_vertex(gam->array_of_vertices[v].object);
        } else {
            /* Só aumenta a contagem se for um vértice novo */
            gam->number_of_vertices++;
        }
        
        /* Instancia a implementação concreta e guarda a interface */
        struct graph_vertex *gv = create_graph_vertex(v, weight);
        gam->array_of_vertices[v] = graph_vertex_as_vertex(gv);
    }
}

static void add_vertex_impl(void *object, int v) {
    add_vertex_with_weight_impl(object, v, NULL);
}

static struct vertex get_vertex_impl(void *object, int v) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    if (v >= 0 && v < MAX_VERTICES) {
        return gam->array_of_vertices[v];
    }
    struct vertex null_v = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    return null_v;
}

static void add_edge_with_weight_impl(void *object, int v, int w, void *weight) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    
    if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
        /* Só adiciona se os vértices existirem e a aresta ainda não existir */
        if (gam->array_of_vertices[v].object != NULL && 
            gam->array_of_vertices[w].object != NULL && 
            gam->matrix_of_edges[v][w].object == NULL) {
            
            struct graph_edge *ge = create_graph_edge(gam->array_of_vertices[v], 
                                                      gam->array_of_vertices[w], 
                                                      weight, 
                                                      gam->directed);
            gam->matrix_of_edges[v][w] = graph_edge_as_edge(ge);
            gam->number_of_edges++;
            
            /* Se for não-direcionado, espelha a aresta com a mesma instância concreta */
            if (!gam->directed && v != w) {
                gam->matrix_of_edges[w][v] = gam->matrix_of_edges[v][w];
            }
        }
    }
}

static void add_edge_impl(void *object, int v, int w) {
    add_edge_with_weight_impl(object, v, w, NULL);
}

static bool is_edge_impl(void *object, int v, int w) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
        return gam->matrix_of_edges[v][w].object != NULL;
    }
    return false;
}

static struct edge get_edge_impl(void *object, int v, int w) {
    struct graph_as_matrix *gam = (struct graph_as_matrix *)object;
    if (v >= 0 && v < MAX_VERTICES && w >= 0 && w < MAX_VERTICES) {
        return gam->matrix_of_edges[v][w];
    }
    struct edge null_e = {NULL, NULL, NULL, NULL, NULL, NULL};
    return null_e;
}

/* --- API Pública Concreta --- */

struct graph_as_matrix *create_graph_as_matrix(bool directed) {
    struct graph_as_matrix *gam = malloc(sizeof(struct graph_as_matrix));
    if (gam != NULL) {
        gam->number_of_vertices = 0;
        gam->number_of_edges = 0;
        gam->directed = directed;
        
        /* Zera os arrays de objetos */
        for (int i = 0; i < MAX_VERTICES; i++) {
            gam->array_of_vertices[i].object = NULL;
            for (int j = 0; j < MAX_VERTICES; j++) {
                gam->matrix_of_edges[i][j].object = NULL;
            }
        }
    }
    return gam;
}

void destroy_graph_as_matrix(struct graph_as_matrix *gam) {
    if (gam != NULL) {
        /* O Grafo agora é o DONO da memória! Precisamos limpar tudo. */
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (gam->array_of_vertices[i].object != NULL) {
                destroy_graph_vertex(gam->array_of_vertices[i].object);
            }
            
            for (int j = 0; j < MAX_VERTICES; j++) {
                if (gam->matrix_of_edges[i][j].object != NULL) {
                    /* Evita double-free em grafos não-direcionados (onde [i][j] e [j][i] apontam pro mesmo objeto) */
                    if (gam->directed || i <= j) {
                        destroy_graph_edge(gam->matrix_of_edges[i][j].object);
                    }
                }
            }
        }
        free(gam);
    }
}

/* Polimorfismo */
struct graph graph_as_matrix_as_graph(struct graph_as_matrix *gam) {
    struct graph g;
    g.object = gam;
    g.get_number_of_vertices = get_number_of_vertices_impl;
    g.get_number_of_edges = get_number_of_edges_impl;
    g.is_directed = is_directed_impl;
    
    g.add_vertex = add_vertex_impl;
    g.add_vertex_with_weight = add_vertex_with_weight_impl;
    g.get_vertex = get_vertex_impl;
    
    g.add_edge = add_edge_impl;
    g.add_edge_with_weight = add_edge_with_weight_impl;
    g.is_edge = is_edge_impl;
    g.get_edge = get_edge_impl;
    return g;
}