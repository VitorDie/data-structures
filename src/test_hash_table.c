#include <stdio.h>
#include <assert.h>
#include "hash_table.h"
#include "hash_table_as_graph.h"
#include "graph.h"

int main(void) {
    printf("Iniciando testes da Hash Table (A Negação da Relação)...\n");

    struct hash_table_as_graph *htag = create_hash_table_as_graph();
    struct hash_table ht = hash_table_as_graph_as_hash_table(htag);

    /* 1. Mapeamento Direto (Put / Get) */
    ht.put(ht.object, 105, 9999); /* Chave 105 guarda o valor 9999 */
    ht.put(ht.object, 42, 7777);  /* Chave 42 guarda o valor 7777 */

    assert(ht.contains(ht.object, 105) == true && "Falha: A chave 105 deveria existir");
    assert(ht.get(ht.object, 105) == 9999 && "Falha: O valor da chave 105 deveria ser 9999");
    assert(ht.get(ht.object, 42) == 7777 && "Falha: O valor da chave 42 deveria ser 7777");
    assert(ht.contains(ht.object, 99) == false && "Falha: A chave 99 não deveria existir");

    /* 2. Remoção (Isolamento apagado) */
    ht.remove_key(ht.object, 42);
    assert(ht.contains(ht.object, 42) == false && "Falha: A chave 42 deveria ter sido removida");

    /* 3. A AUDITORIA ONTOLÓGICA (O Vazio Relacional) */
    struct graph g = ht.base_graph;
    
    /* Inserimos duas chaves e removemos uma. O Grafo deve ter apenas 1 Vértice ativo */
    assert(g.get_number_of_vertices(g.object) == 1 && "Falha: Deveria haver apenas 1 Vértice físico ocupado");
    
    /* A Prova de Fogo: A Destruição das Arestas! */
    assert(g.get_number_of_edges(g.object) == 0 && "Falha Crítica: Uma Hash Table pura NÃO pode ter arestas. A relação foi negada!");

    destroy_hash_table_as_graph(htag);
    printf("Testes da Hash Table passaram! O Isolamento e o Mapeamento O(1) imperam.\n");
    return 0;
}