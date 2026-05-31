#include <stdlib.h>
#include <stdbool.h>
#include "hash_table_as_graph.h"
#include "graph_as_matrix.h"
#include "graph.h"

/* A Matéria da Hash Table */
struct hash_table_as_graph {
    struct graph motor_grafo;                   /* A substância (O Grafo) */
    struct graph_as_matrix *instancia_concreta;
    
    /* A memória interna do Bucket */
    int values[50];       /* Os valores guardados */
    int keys[50];         /* As chaves originais (necessário para validar colisões/existência) */
    bool occupied[50];    /* Marca se o Vértice/Bucket está habitado */
};

/* --- A Função de Dispersão (A Mágica do O(1)) --- */
static int hash_function(int key) {
    /* Mapeia qualquer número do Universo para um Vértice físico de 0 a 49 */
    return key % 50; 
}

/* --- A Lei do Isolamento (Sem Arestas) --- */

static void put_impl(void *object, int key, int value) {
    struct hash_table_as_graph *htag = (struct hash_table_as_graph *)object;
    int vertex_id = hash_function(key);
    
    /* 1. Usamos o Grafo para registar a "existência" física do dado (O Vértice) */
    struct graph g = htag->motor_grafo;
    g.add_vertex(g.object, vertex_id);
    
    /* 2. Guardamos o valor na memória local do Bucket */
    htag->keys[vertex_id] = key;
    htag->values[vertex_id] = value;
    htag->occupied[vertex_id] = true;
}

static int get_impl(void *object, int key) {
    struct hash_table_as_graph *htag = (struct hash_table_as_graph *)object;
    int vertex_id = hash_function(key);
    
    /* O acesso é telepático. Vamos direto ao endereço calculado. */
    if (htag->occupied[vertex_id] && htag->keys[vertex_id] == key) {
        return htag->values[vertex_id];
    }
    return -1; /* Não encontrado */
}

static bool contains_impl(void *object, int key) {
    struct hash_table_as_graph *htag = (struct hash_table_as_graph *)object;
    int vertex_id = hash_function(key);
    
    return htag->occupied[vertex_id] && htag->keys[vertex_id] == key;
}

static void remove_key_impl(void *object, int key) {
    struct hash_table_as_graph *htag = (struct hash_table_as_graph *)object;
    int vertex_id = hash_function(key);
    
    if (htag->occupied[vertex_id] && htag->keys[vertex_id] == key) {
        htag->occupied[vertex_id] = false;
        
        /* Removemos a "existência" física do Grafo. 
           O Vértice é desfeito e o isolamento retorna ao vazio. */
        struct graph g = htag->motor_grafo;
        g.remove_vertex(g.object, vertex_id);
    }
}

/* --- Construtores e Polimorfismo --- */

struct hash_table_as_graph *create_hash_table_as_graph(void) {
    struct hash_table_as_graph *htag = malloc(sizeof(struct hash_table_as_graph));
    if (htag != NULL) {
        htag->instancia_concreta = create_graph_as_matrix(false);
        htag->motor_grafo = graph_as_matrix_as_graph(htag->instancia_concreta);
        
        /* Inicializamos o vazio */
        for (int i = 0; i < 50; i++) {
            htag->occupied[i] = false;
        }
    }
    return htag;
}

void destroy_hash_table_as_graph(struct hash_table_as_graph *htag) {
    if (htag != NULL) {
        destroy_graph_as_matrix(htag->instancia_concreta);
        free(htag);
    }
}

struct hash_table hash_table_as_graph_as_hash_table(struct hash_table_as_graph *htag) {
    struct hash_table ht;
    ht.base_graph = htag->motor_grafo;
    ht.object = htag;
    ht.put = put_impl;
    ht.get = get_impl;
    ht.remove_key = remove_key_impl;
    ht.contains = contains_impl;
    return ht;
}