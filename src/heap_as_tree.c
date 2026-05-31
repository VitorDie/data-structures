#include <stdlib.h>
#include "heap_as_tree.h"
#include "tree_as_graph.h"
#include "tree.h"

/* A Matéria do Heap */
struct heap_as_tree {
    struct tree motor_arvore;                /* A Árvore herdada (A Substância) */
    struct tree_as_graph *instancia_concreta;
    
    /* A matemática da meritocracia (Forma Completa) */
    int values[50];                          /* A representação abstrata da árvore binária */
    int size;                                /* Quantidade de súbditos */
};

/* --- A Lei da Indiferença (Bubble Up / Heapify Down) --- */

static int peek_max_impl(void *object) {
    struct heap_as_tree *hat = (struct heap_as_tree *)object;
    return hat->values[0]; /* O Rei está sempre na Raiz (índice 0) */
}

static void insert_impl(void *object, int value) {
    struct heap_as_tree *hat = (struct heap_as_tree *)object;
    
    /* 1. O recém-chegado entra na base da hierarquia (última folha) */
    int i = hat->size;
    hat->values[i] = value;
    hat->size++;
    
    /* 2. A Suprassunção Ontológica (A Matéria Física)
       Registamos o nó fisicamente na Árvore ANTES de mexer nos valores.
       A Árvore cresce obedecendo à geometria estrita de uma Árvore Binária.
       O pai de qualquer índice 'i' numa árvore binária perfeita é '(i - 1) / 2'. */
    if (i > 0) {
        int parent_value = hat->values[(i - 1) / 2];
        struct tree t = hat->motor_arvore;
        t.add_child(t.object, parent_value, value);
    }
    
    /* 3. O Julgamento do Valor (Bubble Up)
       Agora que a matéria existe no Grafo de forma legal, o Heap é livre 
       para fazer a sua matemática e fazer o Rei subir ao trono! */
    while (i != 0 && hat->values[(i - 1) / 2] < hat->values[i]) {
        int temp = hat->values[i];
        hat->values[i] = hat->values[(i - 1) / 2];
        hat->values[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

static int extract_max_impl(void *object) {
    struct heap_as_tree *hat = (struct heap_as_tree *)object;
    if (hat->size <= 0) return -1;
    
    /* 1. Guardamos o valor do Rei para devolver */
    int root = hat->values[0];
    
    /* 2. O último camponês da base assume temporariamente o Trono */
    hat->values[0] = hat->values[hat->size - 1];
    hat->size--;
    
    /* 3. O Rebaixamento do Impostor (Heapify Down)
       Ele desce na hierarquia até encontrar súbditos mais fracos que ele. */
    int i = 0;
    while ((2 * i + 1) < hat->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        
        if (left < hat->size && hat->values[left] > hat->values[largest])
            largest = left;
        if (right < hat->size && hat->values[right] > hat->values[largest])
            largest = right;
            
        if (largest != i) {
            int temp = hat->values[i];
            hat->values[i] = hat->values[largest];
            hat->values[largest] = temp;
            i = largest;
        } else {
            break; /* O equilíbrio foi restaurado */
        }
    }
    
    return root;
}

/* --- Construtores e Polimorfismo --- */

struct heap_as_tree *create_heap_as_tree(int initial_value) {
    struct heap_as_tree *hat = malloc(sizeof(struct heap_as_tree));
    if (hat != NULL) {
        hat->instancia_concreta = create_tree_as_graph(initial_value);
        hat->motor_arvore = tree_as_graph_as_tree(hat->instancia_concreta);
        
        hat->values[0] = initial_value;
        hat->size = 1;
    }
    return hat;
}

void destroy_heap_as_tree(struct heap_as_tree *hat) {
    if (hat != NULL) {
        destroy_tree_as_graph(hat->instancia_concreta);
        free(hat);
    }
}

struct heap heap_as_tree_as_heap(struct heap_as_tree *hat) {
    struct heap h;
    h.base_tree = hat->motor_arvore;
    h.object = hat;
    h.insert = insert_impl;
    h.extract_max = extract_max_impl;
    h.peek_max = peek_max_impl;
    return h;
}