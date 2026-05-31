#ifndef LIST_H
#define LIST_H

#include "tree.h"

/* A Interface da Lista (A Negação da Ramificação) */
struct list {
    struct tree base_tree; /* A Substância Suprassumida (A Árvore) */
    void *object;          /* O ponteiro para a instância concreta */

    /* A Nova Lei: Não há escolha geométrica. O dado vai para o fim da linha. */
    void (*append)(void *object, int value);
    
    /* Acesso às extremidades (A preparação para a Fila/Pilha que virão depois) */
    int (*get_head)(void *object);
    int (*get_tail)(void *object);
};

#endif /* LIST_H */