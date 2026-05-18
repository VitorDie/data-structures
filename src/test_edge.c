#include <stdio.h>
#include <assert.h>
#include "vertex.h"
#include "graph_vertex.h"
#include "edge.h"
#include "graph_edge.h"

int main(void) {
    printf("Iniciando testes da Edge...\n");

    /* 1. Preparação: Criamos dois vértices para a aresta conectar */
    struct graph_vertex *gv0 = create_graph_vertex(10, NULL);
    struct graph_vertex *gv1 = create_graph_vertex(20, NULL);
    
    struct vertex v0 = graph_vertex_as_vertex(gv0);
    struct vertex v1 = graph_vertex_as_vertex(gv1);

    int peso_aresta = 100;

    /* 2. Criação da instância concreta */
    struct graph_edge *ge = create_graph_edge(v0, v1, &peso_aresta, true);
    assert(ge != NULL && "Falha: A aresta não deve ser nula");

    /* 3. Injeção na interface (Polimorfismo) */
    struct edge e = graph_edge_as_edge(ge);
    assert(e.object == ge && "Falha: O contexto (object) deve apontar para ge");

    /* 4. Teste de Getters simples */
    assert(e.get_weight(e.object) == &peso_aresta && "Falha: Ponteiro do peso incorreto");
    assert(*(int*)e.get_weight(e.object) == 100 && "Falha: Valor do peso incorreto");
    assert(e.is_directed(e.object) == true && "Falha: A aresta deve ser direcionada");

    /* 5. Teste de Vértices (Usamos o vertex_compare para validar) */
    assert(vertex_compare(e.get_v0(e.object), v0) == 0 && "Falha: O v0 está incorreto");
    assert(vertex_compare(e.get_v1(e.object), v1) == 0 && "Falha: O v1 está incorreto");

    /* 6. Teste do get_mate (A lógica central da Aresta) */
    assert(vertex_compare(e.get_mate(e.object, v0), v1) == 0 && "Falha: O parceiro de v0 deve ser v1");
    assert(vertex_compare(e.get_mate(e.object, v1), v0) == 0 && "Falha: O parceiro de v1 deve ser v0");

    /* Teste de comparable da aresta */
    int peso_menor = 50;
    struct graph_edge *ge_menor = create_graph_edge(v0, v1, &peso_menor, true);
    struct edge e_menor = graph_edge_as_edge(ge_menor);
    
    /* Agora usamos a e_menor de fato! 50 - 100 deve ser < 0 */
    assert(edge_compare(e_menor, e) < 0 && "Falha: Aresta com peso 50 deve ser menor que aresta com 100");
    assert(edge_compare(e, e_menor) > 0 && "Falha: Aresta com peso 100 deve ser maior que aresta com 50");
    assert(edge_compare(e, e) == 0 && "Falha: Arestas iguais devem retornar 0");

    /* 7. Limpeza (Aresta não destroi vértices, isso é responsabilidade do Grafo) */
    destroy_graph_edge(ge);
    destroy_graph_edge(ge_menor);
    destroy_graph_vertex(gv0);
    destroy_graph_vertex(gv1);

    printf("Todos os testes da Edge passaram com sucesso!\n");
    return 0;
}