#include "grafo.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include <chrono>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>


using namespace std;

int main() {
    Grafo grafo;

    // Criando vértices do grafo para representar o labirinto
    int a = grafo.adicionarVertice('A');
    int b = grafo.adicionarVertice('B');
    int c = grafo.adicionarVertice('C');
    int d = grafo.adicionarVertice('D');
    int e = grafo.adicionarVertice('E');
    int f = grafo.adicionarVertice('F');
    int g = grafo.adicionarVertice('G');
    int h = grafo.adicionarVertice('H');
    int i = grafo.adicionarVertice('I');
    int j = grafo.adicionarVertice('J');
    int k = grafo.adicionarVertice('K');
    int l = grafo.adicionarVertice('L');
    int m = grafo.adicionarVertice('M');
    int n = grafo.adicionarVertice('N');
    int o = grafo.adicionarVertice('O');
    int p = grafo.adicionarVertice('P');
    int q = grafo.adicionarVertice('Q');
    int r = grafo.adicionarVertice('R');
    int s = grafo.adicionarVertice('S');
    int t = grafo.adicionarVertice('T');
    int u = grafo.adicionarVertice('U');
    int v = grafo.adicionarVertice('V');
    int x = grafo.adicionarVertice('X');
    int y = grafo.adicionarVertice('Y');
    int z = grafo.adicionarVertice('Z');    
    
    // adicionando as arestas (associação de caminhos do labirinto)
    grafo.adicionarAresta(a, b);
    grafo.adicionarAresta(a, f);
    grafo.adicionarAresta(b, a);
    grafo.adicionarAresta(c, h);
    grafo.adicionarAresta(c, d);
    grafo.adicionarAresta(d, e);
    grafo.adicionarAresta(e, j);
    grafo.adicionarAresta(f, g);
    grafo.adicionarAresta(g, h);
    grafo.adicionarAresta(h, i);
    grafo.adicionarAresta(i, n);
    grafo.adicionarAresta(n, o);
    grafo.adicionarAresta(n, m);
    grafo.adicionarAresta(m, l);
    grafo.adicionarAresta(m, r);
    grafo.adicionarAresta(l, q);
    grafo.adicionarAresta(k, p);
    grafo.adicionarAresta(p, u);
    grafo.adicionarAresta(q, v);
    grafo.adicionarAresta(r, s);
    grafo.adicionarAresta(s, t);
    grafo.adicionarAresta(t, z);
    grafo.adicionarAresta(z, y);
    grafo.adicionarAresta(y, x);
    grafo.adicionarAresta(x, v);
    grafo.adicionarAresta(v, u);

    char inicio = 'U';
    char fim = 'E';
    cout<<"Grafo 1"<<endl;
    grafo.imprimirGrafo();


    // BFS 
    cout << endl << "Algoritmo de busca em largura:" << endl;
    char* caminho = new char[grafo.getNumVertices()];
    int tamCaminho;

    auto startTime = chrono::high_resolution_clock::now();

    if (buscaLargura(grafo, inicio, fim, caminho, tamCaminho)) {
        cout << "Caminho encontrado: ";
        for (int i = 0; i < tamCaminho; i++) {
            cout << caminho[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Caminho não encontrado!" << endl;
    }

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Tempo de execução BFS: " << duration.count() << " microsegundos" << endl;

    delete[] caminho;


    // DFS 
    cout << endl << "Algoritmo de busca em profundidade:" << endl;
    caminho = new char[grafo.getNumVertices()];
    tamCaminho = 0;

    startTime = chrono::high_resolution_clock::now();

    if (buscaProfundidade(grafo, inicio, fim, caminho, tamCaminho)) {
        cout << "Caminho encontrado: ";
        for (int i = 0; i < tamCaminho; i++) {
            cout << caminho[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Caminho não encontrado!" << endl;
    }

    endTime = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Tempo de execução DFS: " << duration.count() << " microsegundos" << endl;

    delete[] caminho;
    
    return 0;
}