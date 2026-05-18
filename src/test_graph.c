#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "graph_as_matrix.h"

int main(void) {
    printf("Iniciando testes do Graph As Matrix (Refatorado)...\n");

    struct graph_as_matrix *gam = create_graph_as_matrix(true);
    struct graph g = graph_as_matrix_as_graph(gam);

    /* 1. Inserindo dados reais de domínio (Pesos) */
    int peso_v0 = 100;
    int peso_v1 = 200;
    int peso_aresta = 50;

    g.add_vertex_with_weight(g.object, 0, &peso_v0);
    g.add_vertex_with_weight(g.object, 1, &peso_v1);
    
    assert(g.get_number_of_vertices(g.object) == 2 && "Falha: Devem existir 2 vértices");

    /* 2. Recuperando o Vértice real e testando o Polimorfismo */
    struct vertex v0_recuperado = g.get_vertex(g.object, 0);
    assert(v0_recuperado.object != NULL && "Falha: O vértice retornado não deve ser nulo");
    assert(*(int*)v0_recuperado.get_weight(v0_recuperado.object) == 100 && "Falha: O peso do vértice deve ser 100");

    /* 3. Inserindo Aresta real com peso */
    g.add_edge_with_weight(g.object, 0, 1, &peso_aresta);
    
    assert(g.is_edge(g.object, 0, 1) == true && "Falha: A aresta 0->1 deve existir");
    assert(g.get_number_of_edges(g.object) == 1 && "Falha: Deve existir 1 aresta");

    /* 4. Recuperando a Aresta real e testando */
    struct edge e01_recuperada = g.get_edge(g.object, 0, 1);
    assert(e01_recuperada.object != NULL && "Falha: A aresta retornada não deve ser nula");
    assert(*(int*)e01_recuperada.get_weight(e01_recuperada.object) == 50 && "Falha: O peso da aresta deve ser 50");

    /* 5. A Limpeza (Agora o Grafo é responsável por destruir os vértices e arestas que ele criou!) */
    destroy_graph_as_matrix(gam);

    printf("Todos os testes do Graph (Refatorado) passaram com sucesso!\n");
    return 0;
}