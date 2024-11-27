// dfs.cpp
#include "dfs.hpp"
using namespace std;

Pilha::Pilha() : topo(nullptr),tamanho(0),tamanhoMax(0) {}

void Pilha::empilhar(char valor) {
    No* novo = new No(valor);
    novo->proximo = topo;
    topo = novo;
    tamanho++;
    if(tamanho >= tamanhoMax) tamanhoMax = tamanho;
}

char Pilha::desempilhar() {
    if (topo == nullptr) return '\0';
    
    char valor = topo->valor;
    No* temp = topo;
    topo = topo->proximo;
    delete temp;
    tamanho--;
    return valor;
}

int Pilha::getMaiorTamanho() {
    return tamanhoMax;
}

bool Pilha::vazia() const {
    return topo == nullptr;
}

Pilha::~Pilha() {
    while (topo != nullptr) {
        No* temp = topo;
        topo = topo->proximo;
        delete temp;
    }
}

size_t Pilha::getTotalMemoryUsage() const {
    return tamanhoMax * sizeof(No);
}

bool buscaProfundidade(Grafo& grafo, char inicio, char fim, char* caminho, int& tamCaminho) {
    Pilha pilha;
    bool* visitado = new bool[grafo.getNumVertices()];
    char* pai = new char[grafo.getNumVertices()];
    int iteracoes = 0;
    
    for (int i = 0; i < grafo.getNumVertices(); i++) {
        visitado[i] = false;
        pai[i] = '\0';
    }
    
    pilha.empilhar(inicio);
    visitado[inicio - 'A'] = true;
    
    bool encontrou = false;
    while (!pilha.vazia() && !encontrou) {
        iteracoes++;
        char atual = pilha.desempilhar();
        
        if (atual == fim) {
            encontrou = true;
            continue;
        }
        
        AdjNode* adj = grafo.getAdjList(atual);
        while (adj != nullptr) {
            if (!visitado[adj->nome - 'A']) {
                pilha.empilhar(adj->nome);
                visitado[adj->nome - 'A'] = true;
                pai[adj->nome - 'A'] = atual;
            }
            adj = adj->proximo;
        }
    }
    
    if (encontrou) {
        tamCaminho = 0;
        char atual = fim;
        while (atual != inicio) {
            caminho[tamCaminho++] = atual;
            atual = pai[atual - 'A'];
        }
        caminho[tamCaminho++] = inicio;
        
        // Inverte o caminho
        for (int i = 0; i < tamCaminho / 2; i++) {
            char temp = caminho[i];
            caminho[i] = caminho[tamCaminho - 1 - i];
            caminho[tamCaminho - 1 - i] = temp;
        }
        cout<<"Caminho encontrado em "<<iteracoes<<" iterações"<<endl;
    }else{
        cout<<"Caminho não encontrado"<<iteracoes<< " iterações"<<endl;
    }
    cout<<"Maior tamanho da pilha: "<<pilha.getMaiorTamanho()<<" nós."<<endl;
    cout<<"Memória utilizada pela pilha: "<<pilha.getTotalMemoryUsage()<<" bytes."<<endl;
    
    delete[] visitado;
    delete[] pai;
    
    return encontrou;
}