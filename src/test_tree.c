#include <stdio.h>
#include <assert.h>
#include "tree.h"
#include "tree_as_graph.h"

int main(void) {
    printf("Iniciando testes da Tree (A Negação do Ciclo)...\n");

    /* 1. Criando a árvore com a Raiz sendo o vértice 0 */
    struct tree_as_graph *tag = create_tree_as_graph(0);
    struct tree t = tree_as_graph_as_tree(tag);

    /* 2. Testando o Gênesis */
    // CORRIGIDO: Passando t.object para métodos da Árvore
    assert(t.get_root(t.object) == 0 && "Falha: A raiz deveria ser 0");
    
    // CORRETO: Passando t.base_graph.object para métodos do Grafo
    assert(t.base_graph.get_number_of_vertices(t.base_graph.object) == 1 && "Falha: A árvore deve nascer com 1 vértice (a raiz)");

    /* 3. O Crescimento Ordenado */
    // CORRIGIDO: Passando t.object
    t.add_child(t.object, 0, 1); // 0 é pai de 1
    t.add_child(t.object, 0, 2); // 0 é pai de 2
    t.add_child(t.object, 1, 3); // 1 é pai de 3

    assert(t.base_graph.get_number_of_vertices(t.base_graph.object) == 4 && "Falha: Devem existir 4 vértices");
    assert(t.base_graph.get_number_of_edges(t.base_graph.object) == 3 && "Falha: Uma árvore de 4 nós deve ter 3 arestas");
    
    // CORRIGIDO: Passando t.object
    assert(t.get_parent(t.object, 3) == 1 && "Falha: O pai do 3 deveria ser o 1");
    assert(t.get_parent(t.object, 1) == 0 && "Falha: O pai do 1 deveria ser o 0");

    /* 4. A LEI SENDO TESTADA (A Negação do Ciclo e do Duplo Pai) */
    printf("Testando a restrição de ciclo e multiplicidade de pais...\n");
    
    // Tentativa de criar um ciclo: 3 adota o seu avô (0)
    t.add_child(t.object, 3, 0); 
    
    // Tentativa de dar dois pais ao mesmo filho: 2 tenta adotar o 1
    t.add_child(t.object, 2, 1); 

    /* Como a árvore protege a sua essência, ela deve ter IGNORADO essas adições ilegais */
    assert(t.base_graph.get_number_of_edges(t.base_graph.object) == 3 && "Falha: A árvore permitiu a quebra da regra! (Não é mais uma árvore)");

    /* Limpeza */
    destroy_tree_as_graph(tag);

    printf("Todos os testes da Tree passaram com sucesso!\n");
    return 0;
}