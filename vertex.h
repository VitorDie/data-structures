#ifndef VERTEX_H
#define VERTEX_H

/* Forward declarations de dependências */
struct enumeration; 

/* Declaração da estrutura opaca */
struct vertex;

/* Construtor e Destrutor */
struct vertex *create_vertex(int number, void *weight);
void destroy_vertex(struct vertex *v);

/* Métodos da interface Vertex */
int vertex_get_number(struct vertex *v);
void *vertex_get_weight(struct vertex *v);
struct enumeration *vertex_get_incident_edges(struct vertex *v);
struct enumeration *vertex_get_emanating_edges(struct vertex *v);
struct enumeration *vertex_get_predecessors(struct vertex *v);
struct enumeration *vertex_get_successors(struct vertex *v);

/* Equivalente ao Comparable.compareTo do Java */
int vertex_compare(struct vertex *v1, struct vertex *v2);

#endif /* VERTEX_H */