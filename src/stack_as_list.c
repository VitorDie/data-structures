#include <stdlib.h>
#include "stack_as_list.h"
#include "list_as_tree.h"
#include "list.h"

/* A Matéria da Pilha */
struct stack_as_list {
    struct list motor_lista;                  /* A Lista herdada */
    struct list_as_tree *instancia_concreta;  /* A matéria da Lista */
};

/* --- A Lei do LIFO (O Acesso Restrito) --- */

static void push_impl(void *object, int value) {
    struct stack_as_list *sal = (struct stack_as_list *)object;
    /* O Push nada mais é do que forçar o dado ir para o fim da linha */
    sal->motor_lista.append(sal->motor_lista.object, value);
}

static int peek_impl(void *object) {
    struct stack_as_list *sal = (struct stack_as_list *)object;
    /* O Peek só tem permissão de olhar para a cauda da linha */
    return sal->motor_lista.get_tail(sal->motor_lista.object);
}

static int pop_impl(void *object) {
    struct stack_as_list *sal = (struct stack_as_list *)object;
    
    /* 1. Olhamos para o topo */
    int top_value = peek_impl(object);
    
    /* 2. Damos o passo atrás na linha */
    sal->motor_lista.retrocede(sal->motor_lista.object);
    
    return top_value;
}

/* --- Construtores e Polimorfismo --- */

struct stack_as_list *create_stack_as_list(int initial_value) {
    struct stack_as_list *sal = malloc(sizeof(struct stack_as_list));
    if (sal != NULL) {
        /* A Pilha nasce engolindo uma Lista */
        sal->instancia_concreta = create_list_as_tree(initial_value);
        sal->motor_lista = list_as_tree_as_list(sal->instancia_concreta);
    }
    return sal;
}

void destroy_stack_as_list(struct stack_as_list *sal) {
    if (sal != NULL) {
        destroy_list_as_tree(sal->instancia_concreta);
        free(sal);
    }
}

struct stack stack_as_list_as_stack(struct stack_as_list *sal) {
    struct stack s;
    s.base_list = sal->motor_lista;
    s.object = sal;
    s.push = push_impl;
    s.pop = pop_impl;
    s.peek = peek_impl;
    return s;
}