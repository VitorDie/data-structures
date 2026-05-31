#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "graph.h"

/* A Interface da Hash Table (A Negação da Relação) */
struct hash_table {
    struct graph base_graph; /* A Substância. Mas, desta vez, sem arestas! */
    void *object;

    /* A Lei do Mapeamento: Guardar, Recuperar, Apagar */
    void (*put)(void *object, int key, int value);
    int (*get)(void *object, int key);
    void (*remove_key)(void *object, int key);
    
    /* Verifica se uma chave existe */
    bool (*contains)(void *object, int key);
};

#endif /* HASH_TABLE_H */