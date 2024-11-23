#ifndef BFS_HPP
#define BFS_HPP

#include "grafo.hpp"

class Fila {
private:
    struct No {
        char valor;
        No* proximo;
        No(char v) : valor(v), proximo(nullptr) {}
    };
    
    No *frente, *tras;

public:
    Fila();
    void inserir(char valor);
    char remover();
    bool vazia() const;
    ~Fila();
};

bool buscaLargura(Grafo& grafo, char inicio, char fim, char* caminho, int& tamCaminho);

#endif