#ifndef STACK_H
#define STACK_H

#include "list.h"

/* A Interface da Pilha (A Negação do Acesso - LIFO) */
struct stack {
    struct list base_list; /* A Substância Suprassumida (A Lista) */
    void *object;          /* O ponteiro para a instância concreta */

    /* A Nova Lei: Só se interage com o Topo */
    void (*push)(void *object, int value);
    int (*pop)(void *object);
    int (*peek)(void *object); /* Apenas olha para o topo sem o remover */
};

#endif /* STACK_H */