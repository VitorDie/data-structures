#include <stdio.h>
#include <assert.h>
#include "vertex.h"
#include "graph_vertex.h"

int main(void) {
    printf("Iniciando testes do Vertex...\n");

    int peso_teste = 42;
    
    /* 1. Testa a criação da instância concreta */
    struct graph_vertex *gv1 = create_graph_vertex(10, &peso_teste);
    assert(gv1 != NULL && "Falha: O vértice não deveria ser nulo");

    /* 2. Testa a injeção na interface (Polimorfismo) */
    struct vertex v1 = graph_vertex_as_vertex(gv1);
    assert(v1.object == gv1 && "Falha: O contexto (object) deve apontar para a instância gv1");

    /* 3. Testa os comportamentos através da interface */
    assert(v1.get_number(v1.object) == 10 && "Falha: O número deve ser 10");
    assert(v1.get_weight(v1.object) == &peso_teste && "Falha: O ponteiro de peso está errado");
    assert(*(int*)v1.get_weight(v1.object) == 42 && "Falha: O valor do peso deve ser 42");

    /* 4. Testa stubs de relacionamentos (devem retornar NULL inicialmente) */
    assert(v1.get_incident_edges(v1.object) == NULL && "Falha: Relacionamentos devem iniciar nulos");

    /* 5. Testa o Comparable */
    struct graph_vertex *gv2 = create_graph_vertex(20, NULL);
    struct vertex v2 = graph_vertex_as_vertex(gv2);
    assert(vertex_compare(v1, v2) < 0 && "Falha: Vértice 10 deve ser menor que vértice 20");

    /* Limpeza */
    destroy_graph_vertex(gv1);
    destroy_graph_vertex(gv2);

    printf("Todos os testes do Vertex passaram com sucesso!\n");
    return 0;
}