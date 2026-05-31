# 1. Requisitos Básicos
cmake_minimum_required(VERSION 3.10)
project(Graph C)

# 2. Configurações de Qualidade do Compilador (As mesmas flags que usávamos no GCC)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# 3. A Substância: Criando a Biblioteca Central
# Aqui colocamos apenas os arquivos que FAZEM o grafo funcionar
add_library(CoreGraph 
    src/graph_vertex.c 
    src/graph_edge.c 
    src/graph_as_matrix.c 
    src/digraph_as_matrix.c
    src/tree_as_graph.c
    src/list_as_tree.c
    src/stack_as_list.c
)

# 4. A Regra de Ouro: Ensinando onde estão os Headers
# Isso permite que os arquivos .c façam #include "graph.h" sem dar erro de caminho
target_include_directories(CoreGraph PUBLIC headers
    headers
    headers/graph
    headers/graph/graph
    headers/graph/graph/edge
    headers/graph/graph/vertex
    headers/graph/digraph
    headers/graph/tree
    headers/graph/tree/tree
    headers/graph/tree/list
    headers/graph/tree/list/list
    headers/graph/tree/list/stack
)

# 5. As Determinações: Criando os Executáveis de Teste
# Para cada arquivo com um 'main()', criamos um executável separado

# Teste do Grafo Base
add_executable(test_graph src/test_graph.c)
target_link_libraries(test_graph CoreGraph)

# Teste do Digrafo
add_executable(test_digraph src/test_digraph.c)
target_link_libraries(test_digraph CoreGraph)

# Teste da Árvore
add_executable(test_tree src/test_tree.c)
target_link_libraries(test_tree CoreGraph)

# Teste da Lista
add_executable(test_list src/test_list.c)
target_link_libraries(test_list CoreGraph)

# Teste da Pilha
add_executable(test_stack src/test_stack.c)
target_link_libraries(test_stack CoreGraph)