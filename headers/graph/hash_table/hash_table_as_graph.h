#ifndef HASH_TABLE_AS_GRAPH_H
#define HASH_TABLE_AS_GRAPH_H

#include "hash_table.h"

struct hash_table_as_graph;

struct hash_table_as_graph *create_hash_table_as_graph(void);
void destroy_hash_table_as_graph(struct hash_table_as_graph *htag);

struct hash_table hash_table_as_graph_as_hash_table(struct hash_table_as_graph *htag);

#endif /* HASH_TABLE_AS_GRAPH_H */