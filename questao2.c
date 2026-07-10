#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct No {
    No* filhos[26];
    bool fim;

    No() {
        fim = false;
        for (int i = 0; i < 26; i++) {
            filhos[i] = nullptr;
        }
    }
};

class ArvoreTrie {
private:
    No* raiz;

    bool vazio(No* n) {
        for (int i = 0; i < 26; i++) {
            if (n->filhos[i]) return false;
        }
        return true;
    }

    bool removerAux(No* n, string pal, int prof) {
        if (!n) return false;

        if (prof == pal.size()) {
            if (n->fim) {
                n->fim = false;
            }
            return vazio(n);
        }

        int pos = pal[prof] - 'a';
        if (removerAux(n->filhos[pos], pal, prof + 1)) {
            delete n->filhos[pos];
            n->filhos[pos] = nullptr;
            return !n->fim && vazio(n);
        }

        return false;
    }

    void listarAux(No* n, string prefixo, vector<string>& lista) {
        if (!n) return;
        if (n->fim) {
            lista.push_back(prefixo);
        }
        for (int i = 0; i < 26; i++) {
            if (n->filhos[i]) {
                listarAux(n->filhos[i], prefixo + (char)('a' + i), lista);
            }
        }
    }

    int calcularDistancia(string p1, string p2) {
        int t1 = p1.size();
        int t2 = p2.size();
        vector<vector<int>> matriz(t1 + 1, vector<int>(t2 + 1));

        for (int i = 0; i <= t1; i++) matriz[i][0] = i;
        for (int j = 0; j <= t2; j++) matriz[0][j] = j;

        for (int i = 1; i <= t1; i++) {
            for (int j = 1; j <= t2; j++) {
                if (p1[i - 1] == p2[j - 1]) {
                    matriz[i][j] = matriz[i - 1][j - 1];
                } else {
                    matriz[i][j] = 1 + min({matriz[i - 1][j], matriz[i][j - 1], matriz[i - 1][j - 1]});
                }
            }
        }
        return matriz[t1][t2];
    }

public:
    ArvoreTrie() {
        raiz = new No();
    }

    void inserir(string pal) {
        No* atual = raiz;
        for (char c : pal) {
            int pos = c - 'a';
            if (!atual->filhos[pos]) {
                atual->filhos[pos] = new No();
            }
            atual = atual->filhos[pos];
        }
        atual->fim = true;
    }

    bool buscar(string pal) {
        No* atual = raiz;
        for (char c : pal) {
            int pos = c - 'a';
            if (!atual->filhos[pos]) return false;
            atual = atual->filhos[pos];
        }
        return atual != nullptr && atual->fim;
    }

    void remover(string pal) {
        removerAux(raiz, pal, 0);
    }

    vector<string> listar() {
        vector<string> lista;
        listarAux(raiz, "", lista);
        return lista;
    }

    vector<string> completar(string prefixo) {
        vector<string> lista;
        No* atual = raiz;
        for (char c : prefixo) {
            int pos = c - 'a';
            if (!atual->filhos[pos]) return lista;
            atual = atual->filhos[pos];
        }
        listarAux(atual, prefixo, lista);
        return lista;
    }

    string corrigir(string pal) {
        if (buscar(pal)) return pal;

        vector<string> todas = listar();
        string melhor = "";
        int menorErro = 9999;

        for (string p : todas) {
            int erro = calcularDistancia(pal, p);
            if (erro < menorErro) {
                menorErro = erro;
                melhor = p;
            }
        }
        return melhor;
    }
};

int main() {
    ArvoreTrie arvore;
    
    vector<string> palavras = {
        "que", "nao", "de", "um", "uma", "para", "com", "do", "da", "em",
        "no", "na", "por", "mais", "mas", "como", "eu", "ele", "ela", "isso",
        "este", "esta", "se", "me", "lhe", "quem", "qual", "quando", "onde", "muito",
        "pouco", "tudo", "nada", "ser", "estar", "ter", "haver", "fazer", "poder", "dizer",
        "ir", "ver", "dar", "saber", "querer", "ficar", "dever", "passar", "chegar", "deixar",
        "falar", "encontrar", "levar", "comecar", "partir", "pensar", "parecer", "apresentar", "olhar", "tornar",
        "sair", "voltar", "achar", "existir", "sentir", "criar", "chamar", "vir", "pedir", "viver",
        "trabalhar", "usar", "lembrar", "tentar", "mostrar", "seguir", "esperar", "buscar", "entrar", "caso",
        "tempo", "coisa", "ano", "dia", "homem", "mulher", "vida", "parte", "mundo", "lugar",
        "forma", "pessoa", "grande", "melhor", "novo", "sem", "mesmo", "aos", "seu", "sua"
    };

    for (string p : palavras) {
        arvore.inserir(p);
    }

    cout << "--- Teste da Arvore Trie ---" << endl;

    cout << "\nBusca por 'mundo': " << (arvore.buscar("mundo") ? "Achou" : "Nao achou") << endl;
    cout << "Busca por 'abacaxi': " << (arvore.buscar("abacaxi") ? "Achou" : "Nao achou") << endl;

    cout << "\nAutocompletar 'pe':" << endl;
    vector<string> listaAuto = arvore.completar("pe");
    for (string p : listaAuto) {
        cout << "- " << p << endl;
    }

    cout << "\nCorrigir 'vids' (esperado 'vida'): " << arvore.corrigir("vids") << endl;
    cout << "Corrigir 'melor' (esperado 'melhor'): " << arvore.corrigir("melor") << endl;
    cout << "Corrigir 'qanudo' (esperado 'quando'): " << arvore.corrigir("qanudo") << endl;

    cout << "\nRemovendo 'mundo'..." << endl;
    arvore.remover("mundo");
    cout << "Busca por 'mundo' apos remover: " << (arvore.buscar("mundo") ? "Achou" : "Nao achou") << endl;

    return 0;
}