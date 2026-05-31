#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "queue_as_list.h"
#include "graph.h"

int main(void) {
    printf("Iniciando testes da Queue (A Negação do Acesso - FIFO)...\n");

    /* 1. O Gênesis FIFO (A Fila abre com o cliente 10) */
    struct queue_as_list *qal = create_queue_as_list(10);
    struct queue q = queue_as_list_as_queue(qal);

    assert(q.peek(q.object) == 10 && "Falha: O primeiro da fila deve ser o 10");

    /* 2. Entrando na Fila (Enqueue) */
    q.enqueue(q.object, 20);
    q.enqueue(q.object, 30);

    /* O Peek não deve mudar! O 10 continua a ser o primeiro a ser atendido. */
    assert(q.peek(q.object) == 10 && "Falha: O topo da fila não deve mudar quando novos elementos entram");

    /* 3. Atendendo o cliente (Dequeue - A marcha do tempo) */
    int cliente_atendido = q.dequeue(q.object);
    assert(cliente_atendido == 10 && "Falha: O dequeue deveria ter retornado 10 (o mais antigo)");
    assert(q.peek(q.object) == 20 && "Falha: Após atender o 10, o 20 deve ser o próximo da fila");

    /* 4. A AUDITORIA ONTOLÓGICA */
    struct list l = q.base_list;
    struct tree t = l.base_tree;
    struct graph g = t.base_graph;

    /* A estrutura física (Grafo) ainda contém os vértices gerados */
    assert(g.get_number_of_vertices(g.object) >= 3 && "Falha: A matéria base do grafo deve estar intacta");
    
    // Verificamos se o caminho 10 -> 20 -> 30 foi criado corretamente
    assert(g.is_edge(g.object, 10, 20) == true && "Falha: Caminho 10->20 desapareceu");
    assert(g.is_edge(g.object, 20, 30) == true && "Falha: Caminho 20->30 desapareceu");

    destroy_queue_as_list(qal);
    printf("Testes da Queue passaram! O FIFO impera sobre a Lista.\n");
    return 0;
}