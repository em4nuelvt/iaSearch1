#include <iostream>
#include "grafo.hpp"
// Estrutura para o nó da lista de adjacência

AdjNode::AdjNode(int v, char nome) {
    vertice = v;
    this->nome = nome;
    proximo = nullptr;
}

// VerticeNode constructor implementation
VerticeNode::VerticeNode(int identificador, char nome) {
    id = identificador;
    listaAdj = nullptr;
    proximo = nullptr;
    this->nome = nome;
}

// Grafo methods implementation
Grafo::Grafo() {
    vertices = nullptr;
    numVertices = 0;
    proximoId = 0;
}


VerticeNode* Grafo::encontrarVertice(int id) {
    VerticeNode* atual = vertices;
    while (atual != nullptr) {
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}

VerticeNode* Grafo::encontrarVerticePorNome(char nome) {
    VerticeNode* atual = vertices;
    while (atual != nullptr) {
        if (atual->nome == nome) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}
int Grafo::adicionarVertice(char nome) {
    VerticeNode* novoVertice = new VerticeNode(proximoId, nome);
    novoVertice->proximo = vertices;
    vertices = novoVertice;
    numVertices++;
    return proximoId++;
}
    
// Remove um vértice e todas as arestas conectadas a ele
bool Grafo::removerVertice(int id) {
    VerticeNode* atual = vertices;
    VerticeNode* anterior = nullptr;
    
    // Procura o vértice a ser removido
    while (atual != nullptr && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == nullptr) return false;
    
    // Remove todas as arestas que apontam para este vértice
    VerticeNode* v = vertices;
    while (v != nullptr) {
        removerAresta(v->id, id);
        v = v->proximo;
    }
    
    // Remove o vértice da lista de vértices
    if (anterior == nullptr) {
        vertices = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    // Libera a memória das arestas do vértice
    AdjNode* adj = atual->listaAdj;
    while (adj != nullptr) {
        AdjNode* proxAdj = adj->proximo;
        delete adj;
        adj = proxAdj;
    }
    
    delete atual;
    numVertices--;
    return true;
}

// Adiciona uma aresta entre dois vértices
bool Grafo::adicionarAresta(int origem, int destino) {
    VerticeNode* verticeOrigem = encontrarVertice(origem);
    VerticeNode* verticeDestino = encontrarVertice(destino);
    
    if (verticeOrigem == nullptr || verticeDestino == nullptr) {
        return false;
    }
    
    // Adiciona aresta origem -> destino
    AdjNode* novaAdj = new AdjNode(destino, verticeDestino->nome);
    novaAdj->proximo = verticeOrigem->listaAdj;
    verticeOrigem->listaAdj = novaAdj;
    
    // Adiciona aresta destino -> origem (para tornar não direcionado)
    AdjNode* novaAdjInversa = new AdjNode(origem, verticeOrigem->nome);
    novaAdjInversa->proximo = verticeDestino->listaAdj;
    verticeDestino->listaAdj = novaAdjInversa;
    
    return true;
}
// Remove uma aresta entre dois vértices
bool Grafo::removerAresta(int origem, int destino) {
    VerticeNode* verticeOrigem = encontrarVertice(origem);
    if (verticeOrigem == nullptr) return false;
    
    AdjNode* atual = verticeOrigem->listaAdj;
    AdjNode* anterior = nullptr;
    
    while (atual != nullptr && atual->vertice != destino) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == nullptr) return false;
    
    if (anterior == nullptr) {
        verticeOrigem->listaAdj = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    delete atual;
    return true;
}

// Imprime o grafo
void Grafo::imprimirGrafo() {
    VerticeNode* v = vertices;
    while (v != nullptr) {
        std::cout << "Vértice " << v->nome<< ":";
        
        AdjNode* adj = v->listaAdj;
        while (adj != nullptr) {
            std::cout << " -> " << adj->nome;
            adj = adj->proximo;
        }
        std::cout << std::endl;
        
        v = v->proximo;
    }
}

// Retorna o número atual de vértices
int Grafo::getNumVertices() {
    return numVertices;
}

AdjNode* Grafo::getAdjList(char nome) {
    VerticeNode* vertice = encontrarVerticePorNome(nome);
    if (vertice != nullptr) {
        return vertice->listaAdj;
    }
    return nullptr;
}

// Destrutor
Grafo::~Grafo() {
    while (vertices != nullptr) {
        VerticeNode* verticeAtual = vertices;
        vertices = vertices->proximo;
        
        // Libera a memória das arestas
        AdjNode* adj = verticeAtual->listaAdj;
        while (adj != nullptr) {
            AdjNode* proxAdj = adj->proximo;
            delete adj;
            adj = proxAdj;
        }
        
        delete verticeAtual;
    }
}