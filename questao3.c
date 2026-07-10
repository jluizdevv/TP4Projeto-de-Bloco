#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

class GrafoLabirinto {
private:
    int num_vertices;
    vector<vector<int>> adj;

public:
    GrafoLabirinto(int n) {
        num_vertices = n;
        adj.resize(n);
    }

    void adicionarAresta(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> resolverDFS(int inicio, int fim) {
        stack<int> pilha;
        vector<bool> visitado(num_vertices, false);
        vector<int> pai(num_vertices, -1);

        pilha.push(inicio);
        visitado[inicio] = true;

        while (!pilha.empty()) {
            int atual = pilha.top();
            pilha.pop();

            if (atual == fim) break;

            for (int vizinho : adj[atual]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    pai[vizinho] = atual;
                    pilha.push(vizinho);
                }
            }
        }

        vector<int> caminho;
        if (!visitado[fim]) return caminho;

        for (int v = fim; v != -1; v = pai[v]) {
            caminho.push_back(v);
        }
        reverse(caminho.begin(), caminho.end());
        return caminho;
    }

    vector<int> resolverBFS(int inicio, int fim) {
        queue<int> fila;
        vector<bool> visitado(num_vertices, false);
        vector<int> pai(num_vertices, -1);

        fila.push(inicio);
        visitado[inicio] = true;

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();

            if (atual == fim) break;

            for (int vizinho : adj[atual]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    pai[vizinho] = atual;
                    fila.push(vizinho);
                }
            }
        }

        vector<int> caminho;
        if (!visitado[fim]) return caminho;

        for (int v = fim; v != -1; v = pai[v]) {
            caminho.push_back(v);
        }
        reverse(caminho.begin(), caminho.end());
        return caminho;
    }
};

void imprimirCaminho(string nome, vector<int>& caminho) {
    cout << "Caminho " << nome << ": ";
    if (caminho.empty()) {
        cout << "Nenhum caminho encontrado." << endl;
        return;
    }
    for (size_t i = 0; i < caminho.size(); i++) {
        cout << caminho[i];
        if (i < caminho.size() - 1) cout << " -> ";
    }
    cout << " (Tamanho: " << caminho.size() - 1 << " passos)" << endl;
}

int main() {
    GrafoLabirinto labirinto(15);

    labirinto.adicionarAresta(0, 1);
    labirinto.adicionarAresta(1, 2);
    labirinto.adicionarAresta(1, 5);
    labirinto.adicionarAresta(2, 3);
    labirinto.adicionarAresta(3, 4);
    labirinto.adicionarAresta(4, 14);
    labirinto.adicionarAresta(5, 6);
    labirinto.adicionarAresta(5, 8);
    labirinto.adicionarAresta(6, 7);
    labirinto.adicionarAresta(8, 9);
    labirinto.adicionarAresta(9, 10);
    labirinto.adicionarAresta(9, 11);
    labirinto.adicionarAresta(11, 12);
    labirinto.adicionarAresta(12, 13);
    labirinto.adicionarAresta(13, 14);

    int entrada = 0;
    int saida = 14;

    cout << "--- Resolucao do Labirinto ---" << endl;

    vector<int> caminhoDFS = labirinto.resolverDFS(entrada, saida);
    imprimirCaminho("DFS (Busca em Profundidade)", caminhoDFS);

    vector<int> caminhoBFS = labirinto.resolverBFS(entrada, saida);
    imprimirCaminho("BFS (Busca em Largura)", caminhoBFS);

    return 0;
}