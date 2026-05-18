```bash
# mkdir build if this folder doesn't exist
cd build

# generate configuration files
cmake ..

# then make executables 
make

# the executables will be into build directory, thus you can run them using ./test_graph, or ./test_digraph
```

### About the source code

I made this code based on "Bruno R. Preiss, Estruturas de Dados e Algoritmos, Editora Campus, 2000." and "Cristiano Silva, Faz em C: Programação Orientada a Objetos em C, Independente, 2024.".

The software architecture I was inspired by Bruno R. Preiss, and the implemntation I was inspired by Cristiano Silva. Futhermore I used domain driven concepts, since I though the interfaces and the domain before all the rest of code, and I developed it using Test-Driven Development duo to its practicality an dobjectivity in software development. 