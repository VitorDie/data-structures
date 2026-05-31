#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

/* A Interface da Fila (A Justiça do Tempo - FIFO) */
struct queue {
    struct list base_list; /* A Substância Suprassumida */
    void *object;

    /* A Nova Lei: Inserir no fim, remover do início */
    void (*enqueue)(void *object, int value);
    int (*dequeue)(void *object);
    int (*peek)(void *object); /* Olha para quem está na frente da Fila (Cabeça) */
};

#endif /* QUEUE_H */