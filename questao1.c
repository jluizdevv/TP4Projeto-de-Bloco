#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

struct Processo {
    int id;
    int burst_total;
    int burst_restante;
};

class MinHeap {
private:
    vector<Processo> heap;

    int pai(int i) { return (i - 1) / 2; }
    int esq(int i) { return (2 * i + 1); }
    int dir(int i) { return (2 * i + 2); }

    void heapify(int i) {
        int menor = i;
        int e = esq(i);
        int d = dir(i);

        if (e < heap.size() && heap[e].burst_restante < heap[menor].burst_restante) 
            menor = e;
        if (d < heap.size() && heap[d].burst_restante < heap[menor].burst_restante) 
            menor = d;

        if (menor != i) {
            swap(heap[i], heap[menor]);
            heapify(menor);
        }
    }

public:
    void inserir(Processo p) {
        heap.push_back(p);
        int i = heap.size() - 1;

        while (i != 0 && heap[pai(i)].burst_restante > heap[i].burst_restante) {
            swap(heap[i], heap[pai(i)]);
            i = pai(i);
        }
    }

    Processo extrairMin() {
        if (heap.empty()) return {-1, 0, 0};
        
        if (heap.size() == 1) {
            Processo raiz = heap[0];
            heap.pop_back();
            return raiz;
        }

        Processo raiz = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);

        return raiz;
    }

    bool vazia() { return heap.empty(); }
};

void imprimirLinha(int tempo, int id, string de, string para, int burst) {
    cout << left << setw(10) << tempo 
         << setw(10) << id 
         << setw(15) << de 
         << setw(15) << para 
         << setw(15) << burst << endl;
}

int main() {
    MinHeap fila_pronta;
    MinHeap fila_suspensa;
    
    int quantum = 4;
    int tempo_global = 0;

    srand(time(NULL));

    cout << left << setw(10) << "Tempo" 
         << setw(10) << "ID" 
         << setw(15) << "Estado Ant." 
         << setw(15) << "Novo Estado" 
         << setw(15) << "Burst Restante" << endl;
    cout << string(65, '-') << endl;

    for (int i = 1; i <= 10; i++) {
        Processo p;
        p.id = i;
        p.burst_total = 15 + (i * 2);
        p.burst_restante = p.burst_total;
        
        imprimirLinha(tempo_global, p.id, "Nova", "Pronta", p.burst_restante);
        fila_pronta.inserir(p);
    }
    
    cout << string(65, '-') << endl;

    while (!fila_pronta.vazia() || !fila_suspensa.vazia()) {
        if (!fila_suspensa.vazia() && (rand() % 100 < 40)) {
            Processo lib = fila_suspensa.extrairMin();
            imprimirLinha(tempo_global, lib.id, "Suspensa", "Pronta", lib.burst_restante);
            fila_pronta.inserir(lib);
        }

        if (!fila_pronta.vazia()) {
            Processo atual = fila_pronta.extrairMin();
            imprimirLinha(tempo_global, atual.id, "Pronta", "Executando", atual.burst_restante);

            int tempo_execucao = (atual.burst_restante > quantum) ? quantum : atual.burst_restante;

            for(int t = 0; t < tempo_execucao; t++) {
                this_thread::sleep_for(chrono::milliseconds(150));
                tempo_global++;
            }

            atual.burst_restante -= tempo_execucao;

            if (atual.burst_restante == 0) {
                imprimirLinha(tempo_global, atual.id, "Executando", "Terminada", 0);
            } else {
                if (rand() % 100 < 30) {
                    imprimirLinha(tempo_global, atual.id, "Executando", "Suspensa", atual.burst_restante);
                    fila_suspensa.inserir(atual);
                } else {
                    imprimirLinha(tempo_global, atual.id, "Executando", "Pronta", atual.burst_restante);
                    fila_pronta.inserir(atual);
                }
            }
        } else {
            this_thread::sleep_for(chrono::milliseconds(150));
            tempo_global++;
        }
    }

    cout << string(65, '-') << endl;
    cout << "Todos os processos concluidos no tempo " << tempo_global << "." << endl;

    return 0;
}