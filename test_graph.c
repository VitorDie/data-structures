#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "graph_as_matrix.h"

int main(void) {
    printf("Iniciando testes do Graph (As Matrix)...\n");

    /* 1. Criação do Grafo Direcionado */
    struct graph_as_matrix *gam = create_graph_as_matrix(true);
    assert(gam != NULL && "Falha: O grafo não deve ser nulo");

    /* 2. Injeção na interface genérica (Polimorfismo) */
    struct graph g = graph_as_matrix_as_graph(gam);
    
    /* 3. Teste de Estado Inicial */
    assert(g.get_number_of_vertices(g.object) == 0 && "Falha: Grafo deve nascer vazio");
    assert(g.get_number_of_edges(g.object) == 0 && "Falha: Grafo deve nascer sem arestas");
    assert(g.is_directed(g.object) == true && "Falha: Grafo deve ser direcionado");

    /* 4. Adicionando Vértices */
    g.add_vertex(g.object, 0);
    g.add_vertex(g.object, 1);
    g.add_vertex(g.object, 2);
    assert(g.get_number_of_vertices(g.object) == 3 && "Falha: Devem existir 3 vértices");

    /* 5. Adicionando Arestas (0->1 e 1->2) */
    g.add_edge(g.object, 0, 1);
    g.add_edge(g.object, 1, 2);
    assert(g.get_number_of_edges(g.object) == 2 && "Falha: Devem existir 2 arestas");

    /* 6. Verificando Conexões (Lógica Direcionada) */
    assert(g.is_edge(g.object, 0, 1) == true && "Falha: A aresta 0->1 deve existir");
    assert(g.is_edge(g.object, 1, 0) == false && "Falha: A aresta 1->0 NÃO deve existir (direcionado)");
    assert(g.is_edge(g.object, 0, 2) == false && "Falha: A aresta 0->2 NÃO deve existir");

    /* 7. Limpeza */
    destroy_graph_as_matrix(gam);

    printf("Todos os testes do Graph passaram com sucesso!\n");
    return 0;
}