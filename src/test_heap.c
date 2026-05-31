#include <stdio.h>
#include <assert.h>
#include "heap.h"
#include "heap_as_tree.h"
#include "graph.h"

int main(void) {
    printf("Iniciando testes do Heap (A Negação da Forma Livre e da Indiferença)...\n");

    /* 1. O Gênesis do Heap (Nasce com o Rei '10') */
    struct heap_as_tree *hat = create_heap_as_tree(10);
    struct heap h = heap_as_tree_as_heap(hat);

    assert(h.peek_max(h.object) == 10 && "Falha: O maior inicial deve ser 10");

    /* 2. O Teste da Meritocracia (Insert e Bubble Up) */
    printf("Inserindo o 30. O 30 deve usurpar o trono do 10...\n");
    h.insert(h.object, 30);
    assert(h.peek_max(h.object) == 30 && "Falha: O 30 deveria ter subido para a raiz");

    /* Inserindo um súbdito e um novo Rei */
    h.insert(h.object, 20); // O 20 vai ficar abaixo do 30
    h.insert(h.object, 50); // O 50 deve subir até o topo absoluto!
    
    assert(h.peek_max(h.object) == 50 && "Falha: O 50 deve ser o rei incontestável da árvore");

    /* 3. A Decapitação do Rei (Extract Max) */
    printf("Extraindo o rei (50). O Heap deve eleger o 30 como novo rei...\n");
    int antigo_rei = h.extract_max(h.object);
    
    assert(antigo_rei == 50 && "Falha: extract_max deveria ter retornado o 50");
    assert(h.peek_max(h.object) == 30 && "Falha: O 30 deveria ter assumido o trono após a saída do 50");

    /* 4. A Auditoria Ontológica (Temos a Árvore e o Grafo intactos?) */
    struct tree t = h.base_tree;
    struct graph g = t.base_graph;
    
    /* 10, 30, 20, 50 = 4 elementos. Removemos 1 (50). Sobram 3 elementos na matéria. */
    assert(g.get_number_of_vertices(g.object) >= 3 && "Falha: O motor do grafo deve estar operante e sustentar a base");

    destroy_heap_as_tree(hat);
    printf("Testes do Heap passaram! A Meritocracia e a Forma Binária imperam.\n");
    return 0;
}