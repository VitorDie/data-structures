#ifndef STACK_AS_LIST_H
#define STACK_AS_LIST_H

#include "stack.h"

struct stack_as_list;

/* O construtor da matéria da Pilha */
struct stack_as_list *create_stack_as_list(int initial_value);
void destroy_stack_as_list(struct stack_as_list *sal);

/* Polimorfismo */
struct stack stack_as_list_as_stack(struct stack_as_list *sal);

#endif /* STACK_AS_LIST_H */