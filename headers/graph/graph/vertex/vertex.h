#ifndef VERTEX_H
#define VERTEX_H

/* Forward declarations */
struct enumeration;

/* Interface Vertex */
struct vertex {
    void *object; /* Contexto da implementação concreta [cite: 1004-1005] */

    int (*get_number)(void *object);
    void *(*get_weight)(void *object);
    
    struct enumeration *(*get_incident_edges)(void *object);
    struct enumeration *(*get_emanating_edges)(void *object);
    struct enumeration *(*get_predecessors)(void *object);
    struct enumeration *(*get_successors)(void *object);
};

/* Extração do Comparable.compareTo */
int vertex_compare(struct vertex v1, struct vertex v2);

#endif /* VERTEX_H */