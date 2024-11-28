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
    int tamanho;
    int tamanhoMax;
    No* topo;

public:
    Pilha();
    void empilhar(char valor);
    char desempilhar();
    bool vazia() const;
    ~Pilha();
    int getMaiorTamanho();
    size_t getTotalMemoryUsage() const;
};

bool buscaProfundidade(Grafo& grafo, char inicio, char fim, char* caminho, int& tamCaminho);

#endif