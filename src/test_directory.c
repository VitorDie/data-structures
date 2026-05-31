#include <stdio.h>
#include <assert.h>
#include "directory.h"
#include "directory_as_tree.h"
#include "graph.h"

int main(void) {
    printf("Iniciando testes do File System (A Aplicação da Árvore)...\n");

    /* 1. O Gênesis (A montagem da raiz '/' com ID 0) */
    struct directory_as_tree *dat = create_directory_as_tree(0, "/");
    struct directory dir = directory_as_tree_as_directory(dat);

    /* 2. Criando o ambiente de utilizador (mkdir) */
    bool res1 = dir.mkdir(dir.object, 0, 1, "home");
    assert(res1 == true && "Falha: Deveria ser possível criar a pasta /home");

    bool res2 = dir.mkdir(dir.object, 1, 2, "vitordie");
    assert(res2 == true && "Falha: Deveria ser possível criar a pasta /home/vitordie");

    /* 3. Programando o núcleo (touch) */
    bool res3 = dir.touch(dir.object, 2, 3, "minix_kernel.c");
    assert(res3 == true && "Falha: Deveria ser possível criar o ficheiro minix_kernel.c");

    /* 4. A Lei da Esterilidade (O Teste de Defesa) */
    printf("Testando a Lei da Esterilidade: tentando criar diretórios dentro de um ficheiro...\n");
    
    // O ID 3 é o 'minix_kernel.c'. Não pode ser pai de ninguém!
    bool res4 = dir.mkdir(dir.object, 3, 4, "pasta_ilegal");
    assert(res4 == false && "Falha: O Sistema permitiu criar uma pasta dentro de um ficheiro!");

    bool res5 = dir.touch(dir.object, 3, 5, "virus.exe");
    assert(res5 == false && "Falha: O Sistema permitiu criar um ficheiro dentro de outro ficheiro!");

    /* 5. A Auditoria Ontológica (Temos a Árvore Física e o Grafo Intactos?) */
    struct tree t = dir.base_tree;
    struct graph g = t.base_graph;

    /* IDs criados com sucesso: 0, 1, 2, 3 = 4 vértices reais */
    assert(g.get_number_of_vertices(g.object) == 4 && "Falha: Deveriam existir exatamente 4 vértices reais (i-nodes)");
    
    // Verificamos a hierarquia física: vitordie(2) -> minix_kernel.c(3)
    assert(g.is_edge(g.object, 2, 3) == true && "Falha: O Grafo perdeu a ligação entre vitordie e minix_kernel.c");

    /* 6. A Visão do Utilizador (ls) */
    printf("\n--- ls /home/vitordie (ID: 2) ---\n");
    dir.ls(dir.object, 2);
    printf("----------------------------------\n\n");

    destroy_directory_as_tree(dat);
    printf("Testes do Diretório passaram! O primeiro fôlego do MINIX.\n");
    return 0;
}