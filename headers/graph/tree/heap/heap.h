#ifndef HEAP_H
#define HEAP_H

#include "tree.h"

/* A Interface do Heap (A Negação da Forma Livre e a Negação da Indiferença) */
struct heap {
    struct tree base_tree; /* A Substância Suprassumida (A Árvore) */
    void *object;

    /* A Lei do Heap: Insira o dado, e ele encontrar-lhe-á o lugar certo. */
    void (*insert)(void *object, int value);
    
    /* A Extração do Rei: Tira o maior valor e reestrutura a árvore */
    int (*extract_max)(void *object);
    
    /* Olha para a Raiz (O detentor do maior valor) */
    int (*peek_max)(void *object);
};

#endif /* HEAP_H */