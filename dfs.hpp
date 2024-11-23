// dfs.hpp
#ifndef DFS_HPP
#define DFS_HPP
#include "grafo.hpp"

class Pilha {
private:
    struct No {
        char valor;
        No* proximo;
        No(char v) : valor(v), proximo(nullptr) {}
    };
    
    No* topo;

public:
    Pilha();
    void empilhar(char valor);
    char desempilhar();
    bool vazia() const;
    ~Pilha();
};

bool buscaProfundidade(Grafo& grafo, char inicio, char fim, char* caminho, int& tamCaminho);

#endif