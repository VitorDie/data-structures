#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "list_as_tree.h"
#include "graph.h"

int main(void) {
    printf("Iniciando testes da List (A Negação da Ramificação)...\n");

    /* 1. O Gênesis Linear */
    struct list_as_tree *lat = create_list_as_tree(10); // 10 é o valor inicial (a head/raiz)
    struct list l = list_as_tree_as_list(lat);

    assert(l.get_head(l.object) == 10 && "Falha: A cabeça da lista deve ser 10");
    assert(l.get_tail(l.object) == 10 && "Falha: Com um elemento, a cauda também é 10");

    /* 2. O Crescimento Estrangulado (Append forçando a linha reta) */
    l.append(l.object, 20);
    l.append(l.object, 30);

    assert(l.get_head(l.object) == 10 && "Falha: A cabeça nunca deve mudar no append");
    assert(l.get_tail(l.object) == 30 && "Falha: A cauda deve ser o último elemento inserido");

    /* 3. A AUDITORIA ONTOLÓGICA (Inspecionando a matéria física na memória) */
    struct tree t = l.base_tree;
    struct graph g = t.base_graph;

    assert(g.get_number_of_vertices(g.object) == 3 && "Falha: Devem existir 3 nós físicos na memória");
    assert(g.get_number_of_edges(g.object) == 2 && "Falha: 3 nós numa linha reta exigem exatamente 2 arestas");

    /* Verificando o caminho exato: 10 -> 20 -> 30 */
    assert(g.is_edge(g.object, 10, 20) == true && "Falha: 10 deveria apontar para 20");
    assert(g.is_edge(g.object, 20, 30) == true && "Falha: 20 deveria apontar para 30");
    
    /* Garantindo que não houve ramificação acidental ou ciclos */
    assert(g.is_edge(g.object, 10, 30) == false && "Falha: A Lista ramificou! Aresta ilegal detectada.");

    destroy_list_as_tree(lat);
    printf("Testes da List passaram! A ramificação da Árvore foi esmagada com sucesso.\n");
    return 0;
}