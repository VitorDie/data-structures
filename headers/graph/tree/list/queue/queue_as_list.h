#ifndef QUEUE_AS_LIST_H
#define QUEUE_AS_LIST_H

#include "queue.h"

struct queue_as_list;

struct queue_as_list *create_queue_as_list(int initial_value);
void destroy_queue_as_list(struct queue_as_list *qal);

struct queue queue_as_list_as_queue(struct queue_as_list *qal);

#endif /* QUEUE_AS_LIST_H */