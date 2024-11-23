#include "grafo.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include <chrono>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fstream>


using namespace std;

// Function to get memory usage in Linux gpt que mandou
struct MemoryUsage {
    size_t vm_size;    // Changed from rss
    size_t resident;   // Changed from virtual_mem
};

MemoryUsage getMemoryUsage() {
    MemoryUsage usage;
    ifstream statm("/proc/self/statm");
    
    if (statm.is_open()) {
        size_t page_size = 4096; // Standard page size on most Linux systems
        size_t vm, resident;
        statm >> vm >> resident;
        usage.vm_size = vm * page_size;
        usage.resident = resident * page_size;
    } else {
        usage.vm_size = 0;
        usage.resident = 0;
    }
    
    return usage;
}


int main() {
    Grafo grafo;
    Grafo grafo2;


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
    
    // adicionando arestas
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

    char inicio = 'A';
    char fim = 'E';
    cout<<"Grafo 1"<<endl;
    grafo.imprimirGrafo();



 // BFS 
    cout << endl << "Algoritmo de busca em largura:" << endl;
    char* caminho = new char[grafo.getNumVertices()];
    int tamCaminho;

    // Force some memory allocation to measure
    volatile char* temp = new char[1024 * 1024];
    for(int i = 0; i < 1024 * 1024; i++) {
        temp[i] = 'x';
    }

    MemoryUsage memBefore = getMemoryUsage();
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
    MemoryUsage memAfter = getMemoryUsage();
    delete[] temp;

    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Tempo de execução BFS: " << duration.count() << " microsegundos" << endl;
    cout << "Uso de memória residente BFS: " << (memAfter.resident - memBefore.resident) / 1024.0 << " KB" << endl;
    cout << "Uso de memória virtual BFS: " << (memAfter.vm_size - memBefore.vm_size) / 1024.0 << " KB" << endl;

    delete[] caminho;

    // DFS 
    cout << endl << "Algoritmo de busca em profundidade:" << endl;
    caminho = new char[grafo.getNumVertices()];
    tamCaminho = 0;

    temp = new char[1024 * 1024];
    for(int i = 0; i < 1024 * 1024; i++) {
        temp[i] = 'x';
    }

    memBefore = getMemoryUsage();
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
    memAfter = getMemoryUsage();
    delete[] temp;

    duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    cout << "Tempo de execução DFS: " << duration.count() << " microsegundos" << endl;
   cout << "Uso de memória residente DFS: " << (memAfter.resident - memBefore.resident) / 1024.0 << " KB" << endl;
    cout << "Uso de memória virtual DFS: " << (memAfter.vm_size - memBefore.vm_size) / 1024.0 << " KB" << endl;

    delete[] caminho;
    return 0;

    /* // Adiciona alguns vértices e guarda seus IDs
    int v1 = grafo2.adicionarVertice('1');
    int v2 = grafo2.adicionarVertice('2');
    int v3 = grafo2.adicionarVertice('3');
    int v4 = grafo2.adicionarVertice('4');

    
    // Adiciona algumas arestas
    grafo2.adicionarAresta(v1, v2);
    grafo2.adicionarAresta(v1, v3);
    grafo2.adicionarAresta(v2, v3);
    grafo2.adicionarAresta(v3, v4);
    
    std::cout << "Grafo inicial:" << std::endl;
    grafo2.imprimirGrafo();
    
    // Adiciona mais um vértice
    int v5 = grafo.adicionarVertice('5');
    grafo2.adicionarAresta(v1, v5);
    grafo2.adicionarAresta(v4, v5);
    
    std::cout << "\nGrafo após adicionar um vértice:" << std::endl;
    grafo2.imprimirGrafo();
    
    // Remove um vértice
    grafo2.removerVertice(v3);
    
    std::cout << "\nGrafo após remover o vértice " << v3 << ":" << std::endl;
    grafo2.imprimirGrafo(); */
    
    return 0;
}