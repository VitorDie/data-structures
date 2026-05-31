#include <stdlib.h>
#include "queue_as_list.h"
#include "list_as_tree.h"
#include "list.h"

/* A Matéria da Fila */
struct queue_as_list {
    struct list motor_lista;                  /* A Lista herdada */
    struct list_as_tree *instancia_concreta;  /* A matéria da Lista */
};

/* --- A Lei do FIFO (A Justiça do Tempo) --- */

static void enqueue_impl(void *object, int value) {
    struct queue_as_list *qal = (struct queue_as_list *)object;
    /* Entrar na fila é ir para o fim da linha (Cauda) */
    qal->motor_lista.append(qal->motor_lista.object, value);
}

static int peek_impl(void *object) {
    struct queue_as_list *qal = (struct queue_as_list *)object;
    /* Olhar para a fila é ver quem é o próximo a ser atendido (Cabeça) */
    return qal->motor_lista.get_head(qal->motor_lista.object);
}

static int dequeue_impl(void *object) {
    struct queue_as_list *qal = (struct queue_as_list *)object;
    
    /* 1. Atendemos o cliente que está na frente (Cabeça) */
    int front_value = peek_impl(object);
    
    /* 2. A fila anda (A cabeça avança para o próximo) */
    qal->motor_lista.step_forward(qal->motor_lista.object);
    
    return front_value;
}

/* --- Construtores e Polimorfismo --- */

struct queue_as_list *create_queue_as_list(int initial_value) {
    struct queue_as_list *qal = malloc(sizeof(struct queue_as_list));
    if (qal != NULL) {
        /* A Fila nasce engolindo uma Lista */
        qal->instancia_concreta = create_list_as_tree(initial_value);
        qal->motor_lista = list_as_tree_as_list(qal->instancia_concreta);
    }
    return qal;
}

void destroy_queue_as_list(struct queue_as_list *qal) {
    if (qal != NULL) {
        destroy_list_as_tree(qal->instancia_concreta);
        free(qal);
    }
}

struct queue queue_as_list_as_queue(struct queue_as_list *qal) {
    struct queue q;
    q.base_list = qal->motor_lista;
    q.object = qal;
    q.enqueue = enqueue_impl;
    q.dequeue = dequeue_impl;
    q.peek = peek_impl;
    return q;
}