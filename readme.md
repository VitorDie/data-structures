# Data Structures

Este projeto é uma biblioteca de estruturas de dados desenvolvida em C puro.

A premissa fundamental da arquitetura é que o Grafo é a estrutura de dados universal. A partir de um motor genérico de grafos e restrições topológicas/temporais rigorosas, todas as demais estruturas da biblioteca são deduzidas e especializadas:

- Árvore (Tree): Um grafo direcionado, acíclico e conexo.
- Lista (List): Uma árvore restrita com grau de saída máximo igual a 1.
- Fila / Pilha (Queue / Stack): Listas ligadas com restrições de acesso temporal (FIFO / LIFO).

## Influências e Paradigmas

- Arquitetura: Inspirada no modelo clássico de Bruno R. Preiss (Estruturas de Dados e Algoritmos).
- Implementação: Padrão de Orientação a Objetos em C puro baseado nas técnicas de Cristiano Silva (Faz em C).
- Metodologia: Desenvolvido estritamente sob Test-Driven Development (TDD) para garantir previsibilidade em sistemas embarcados, e modelado usando conceitos de Domain-Driven Design (DDD), onde as interfaces do domínio foram consolidadas antes de qualquer implementação de hardware.

## Topologia do Dominio

```
graph/
├── digraph
├── hash table
└── tree
    ├── directory
    ├── heap
    └── list
        ├── queue
        └── stack
```

# Requisitos e Como Instalar

Para compilar a arquitetura e rodar a suíte de testes locais, você precisará do cmake, make e dos compiladores nativo e cruzado (para o alvo de 16-bits).

Abra o terminal e execute:

```
sudo apt update
sudo apt install -y build-essential cmake
```

# Como Executar o Projeto

```
# 1. Entre no diretório do projeto e crie a pasta de build
mkdir -p build && cd build

# 2. Gere os arquivos de configuração do ecossistema
cmake ..

# 3. Compile e gere os executáveis de teste
make

# 4. Execute a suíte de validação automatizada (TDD)
./test_graph
# ou
./test_digraph
```
