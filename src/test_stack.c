#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include "stack_as_list.h"
#include "graph.h"
#include "tree.h"

int main(void) {
    printf("Iniciando testes da Stack (A Negação do Acesso - LIFO)...\n");

    /* 1. O Gênesis LIFO */
    struct stack_as_list *sal = create_stack_as_list(10);
    struct stack s = stack_as_list_as_stack(sal);

    assert(s.peek(s.object) == 10 && "Falha: O topo inicial deve ser 10");

    /* 2. Empilhando (Push) */
    s.push(s.object, 20);
    s.push(s.object, 30);

    assert(s.peek(s.object) == 30 && "Falha: O novo topo deve ser 30");

    /* 3. Desempilhando (Pop - A viagem no tempo) */
    int topo_removido = s.pop(s.object);
    assert(topo_removido == 30 && "Falha: O pop deveria ter retornado 30");
    assert(s.peek(s.object) == 20 && "Falha: Após o pop de 30, o topo deve voltar a ser 20");

    /* 4. A AUDITORIA ONTOLÓGICA (Inspecionando a matéria profunda) */
    // A Pilha expõe a Lista, que expõe a Árvore, que expõe o Grafo!
    struct list l = s.base_list;
    struct tree t = l.base_tree;
    struct graph g = t.base_graph;

    /* Embora tenhamos dado pop no 30 (logicamente removido), a nossa matéria 
       foi criada com 3 vértices ao todo. (A nossa deleção física ou lógica 
       será tratada na implementação). */
    assert(g.get_number_of_vertices(g.object) >= 2 && "Falha: A matéria base do grafo deve estar intacta ou atualizada");
    
    // Verificamos se a linha reta geométrica (10 -> 20) foi preservada
    assert(g.is_edge(g.object, 10, 20) == true && "Falha: Aresta estrutural 10->20 desapareceu");

    destroy_stack_as_list(sal);
    printf("Testes da Stack passaram! O LIFO impera sobre a Lista.\n");
    return 0;
}