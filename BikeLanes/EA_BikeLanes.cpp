//      EA   |   2020/2021   |   FCTUC
//
// Autores:     Nuno Silva      2018285621
//              Pedro Marques   2018285632
//
// ________________________________________
//| ------- Problem C - BikeLanes -------- |

#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <algorithm>    // std::sort

#define MAXPOI 1000

using namespace std;

// Variaveis globais
int n;                                              // Numero Pontos de Interesse
int m;                                              // Numero de conexões entre Pontos de Interesse
int q;                                              // Numero de perguntas (1-4)
vector<int> solution = {0, 0, 0, 0};                // Solucao
array <vector<pair<int, int>>, MAXPOI> adj;         // Lista de adjacencia (ponto i liga a uma lista de pontos (first-> ponto a que liga | second-> distancia)
vector< pair<int, pair<int, int>> > adjKruskal;     // Lista de adjacencia para as ligacoes usadas em Kruskal. {Distancia, PontoA, PontoB} (A liga a B e é bidirecional [bike lane])

// Tarjan
int t;
int* low;
int* dfs;
stack<int>* S = new stack<int>();

// Kruskal
int* setKruskal;
int* rankKruskal;

void cleanup() {    // Limpar adj e Solucao para outros casos de teste
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    solution = {0, 0, 0, 0};
}

bool elemInVec(vector<int> v, int elem) {   // Verifica se um elemento existe no vetor v
    for (int i : v) {
        if (i == elem) {
            return true;
        }
    }
    return false;
}

int findKruskal(int a) {
    if (setKruskal[a] != a)
        setKruskal[a] = findKruskal(setKruskal[a]);
    return setKruskal[a];
}

void linkKruskal(int a, int b) {
    if (rankKruskal[a] > rankKruskal[b]) {
        setKruskal[b] = a;
    }
    else {
        setKruskal[a] = b;
    }
    if (rankKruskal[a] == rankKruskal[b]) {
        rankKruskal[b]++;
    }
}

void make_setKruskal() {
    for (int i = 0; i < n; i++) {
        setKruskal[i] = i;
        rankKruskal[i] = 0;
    }
}

void unionKruskal(int a, int b) {
    linkKruskal(findKruskal(a), findKruskal(b));
}

int Kruskal() { // Kruskal
    int len = 0;
    setKruskal = new int[n];
    rankKruskal = new int[n];

    make_setKruskal();
    sort(adjKruskal.begin(), adjKruskal.end());     // sort edges into nondecreasing order by distance

    for (auto w : adjKruskal) {
        int u = w.second.first;
        int v = w.second.second;
        if (findKruskal(u) != findKruskal(v)) {
            //cout << "Ligacao [" << u + 1 << "]" << "[" << v + 1 << "]" << " Comprimento:" << w.first << endl;
            len += w.first;                         // adiciona distancia
            unionKruskal(u, v);
        }
    }
    //cout << "LEN: " << len << endl;
    return len;
}

void Tarjan(int v, bool* visited) {
    low[v] = t;
    dfs[v] = t;
    t += 1;
    S->push(v);
    visited[v] = true;

    for (auto w : adj[v]) {
        int W = w.first;
        if (dfs[W] == -1) {
            Tarjan(W, visited);
            low[v] = min(low[v], low[W]);
        }
        else if (visited[W]) {
            low[v] = min(low[v], dfs[W]);
        }
    }

    int w = 0;
    vector<int> auxSolution;        // Guarda circuito
    if (low[v] == dfs[v]) {
        while (S->top() != v) {
            w = (int)S->top();
            visited[w] = false;
            auxSolution.push_back(w);
            S->pop();
        }
        w = (int)S->top();
        visited[w] = false;
        auxSolution.push_back(w);
        S->pop();
    }
    int len = auxSolution.size();
    if (len > 1) {                                      // Cada circuito tem de ter pelo menos 2 POI
        solution[0]++;                                  // Conta mais um circuito
        if ((q > 1) && (len > solution[1])) {           // Verifica se se trata do maior circuito
            solution[1] = len;
        }
        if (q > 2) {
            adjKruskal.clear();
            for (int i : auxSolution) {
                for (auto j : adj[i]) {
                    if (elemInVec(auxSolution, j.first)) {                  // Verifica se o elemento consta no circuito atual
                        adjKruskal.push_back({ j.second, {i, j.first} });   // Constroi vetor de edges
                    }
                }
            }
            int lenbikeLane = Kruskal();            // Kruskal
            if (lenbikeLane > solution[2]) {        // Verifica se se trata da maior bike lane
                solution[2] = lenbikeLane;
            }
            if (q > 3) {                            // Atualiza comprimento total com a maior bike lane
                solution[3] += lenbikeLane;
            }
        }
    }
}

void bikeLanes() {
    low = new int[n];
    dfs = new int[n];
    bool* visited = new bool[n];
    S->empty();
    while (!S->empty()){S->pop();}                  // Limpar Stack
    t = 1;

    for (int i = 0; i < n; i++) {
        low[i] = 0;
        dfs[i] = -1;
        visited[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (dfs[i] == -1) {
            Tarjan(i, visited);
        }
    }

    delete[] visited;
}

int main() {
    // Ler de maneira eficiente
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int total;                                      // Numero de casos de teste
    cin >> total;

    for (int i = 0; i < total; i++) {
        cin >> n >> m >> q;
        for (int j = 0; j < m; j++) {
            int x, y, d;
            cin >> x >> y >> d;
            adj[x-1].push_back({ y-1, d });
        }
        //cout << "Caso [" << i + 1 << "]:" << endl;
        bikeLanes();
        //cout << "[";
        cout << solution[0];
        for (int i = 1; i < q; i++) {                        //Imprime output
            cout << " " << solution[i];
        }
        //cout << "]";
        cout << endl;
        cleanup();
    }

    // Tarjan
    delete[] low;
    delete[] dfs;

    // Kruskal
    delete[] setKruskal;
    delete[] rankKruskal;

    return 0;
}