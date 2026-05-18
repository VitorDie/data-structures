#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "graph_as_matrix.h"
#include "digraph.h"
#include "digraph_as_matrix.h"

int main(void) {
    printf("Iniciando testes do Digraph (As Matrix)...\n");

    /* 1. Criação do Digrafo Concreto */
    struct digraph_as_matrix *dgam = create_digraph_as_matrix();
    assert(dgam != NULL && "Falha: O digrafo não deve ser nulo");

    /* 2. Injeção na interface VIP (Polimorfismo) */
    struct digraph dg = digraph_as_matrix_as_digraph(dgam);

    /* 3. Acessando os métodos HERDADOS do Graph */
    struct graph base = dg.base_graph;
    
    /* Garantindo que a restrição funcionou (ele DEVE ser direcionado) */
    assert(base.is_directed(base.object) == true && "Falha: Um Digrafo obrigatoriamente é direcionado");

    /* Populando o digrafo usando os métodos da classe mãe */
    base.add_vertex(base.object, 0);
    base.add_vertex(base.object, 1);
    base.add_edge(base.object, 0, 1);
    
    assert(base.get_number_of_edges(base.object) == 1 && "Falha: O digrafo deveria ter 1 aresta");
    assert(base.is_edge(base.object, 0, 1) == true && "Falha: Aresta 0->1 deveria existir");
    assert(base.is_edge(base.object, 1, 0) == false && "Falha: Aresta 1->0 NÃO deveria existir");

    /* 4. Testando os métodos exclusivos do Digraph (Stubs iniciais) */
    assert(dg.is_strongly_connected(dg.base_graph.object) == false && "Falha: Inicialmente, stub retorna falso");

    /* 5. Limpeza */
    destroy_digraph_as_matrix(dgam);

    printf("Todos os testes do Digraph passaram com sucesso!\n");
    return 0;
}