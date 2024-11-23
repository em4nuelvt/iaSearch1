#include "bfs.hpp"
using namespace std;

Fila::Fila() : frente(nullptr), tras(nullptr) {}

void Fila::inserir(char valor) {
    No* novo = new No(valor);
    if (tras == nullptr) {
        frente = tras = novo;
    } else {
        tras->proximo = novo;
        tras = novo;
    }
}

char Fila::remover() {
    if (frente == nullptr) return '\0';
    
    char valor = frente->valor;
    No* temp = frente;
    frente = frente->proximo;
    
    if (frente == nullptr) tras = nullptr;
    
    delete temp;
    return valor;
}

bool Fila::vazia() const {
    return frente == nullptr;
}

Fila::~Fila() {
    while (frente != nullptr) {
        No* temp = frente;
        frente = frente->proximo;
        delete temp;
    }
    tras = nullptr;
}

bool buscaLargura(Grafo& grafo, char inicio, char fim, char* caminho, int& tamCaminho) {
    Fila fila;
    bool* visitado = new bool[grafo.getNumVertices()];
    char* pai = new char[grafo.getNumVertices()];
     int iteracoes = 0;
    
    for (int i = 0; i < grafo.getNumVertices(); i++) {
        visitado[i] = false;
        pai[i] = '\0';
    }
    
    fila.inserir(inicio);
    visitado[inicio - 'A'] = true;
    
    bool encontrou = false;
    while (!fila.vazia() && !encontrou) {
        iteracoes++;
        char atual = fila.remover();
        
        if (atual == fim) {
            encontrou = true;
            continue;
        }
        
        AdjNode* adj = grafo.getAdjList(atual);
        while (adj != nullptr) {
            if (!visitado[adj->nome - 'A']) {
                visitado[adj->nome - 'A'] = true;
                pai[adj->nome - 'A'] = atual;
                fila.inserir(adj->nome);
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
        for (int i = 0; i < tamCaminho/2; i++) {
            char temp = caminho[i];
            caminho[i] = caminho[tamCaminho-1-i];
            caminho[tamCaminho-1-i] = temp;
        }
        cout<<"Caminho encontrado em "<<iteracoes<<" iterações"<<endl;
    }else{
        cout<<"Caminho não encontrado. "<<iteracoes<<" iterações."<<endl;
    }
    
    delete[] visitado;
    delete[] pai;
    return encontrou;
}