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
array <vector<array<int, 2>>, MAXPOI> adj;          // Lista de adjacencia (ponto liga a pontos)
array <vector<array<int, 2>>, MAXPOI> adjLanes;     // Lista de adjacencia (usada para ver o comprimento das lanes) (pontos que se ligam ao ponto)
array <vector<array<int, 2>>, MAXPOI> adjBoth;      // Lista de adjacencia ambas direcoes
vector< pair<int, pair<int, int>> > adjKruskal;     // Lista de adjacencia apenas os usados em Kruskal

// Tarjan
int t;
int* low;
int* dfs;
stack<int>* S = new stack<int>();

// Kruskal
int* setKruskal;
int* rankKruskal;

void cleanup() {
    for (int i = 0; i < n + 1; i++) {
        adj[i].clear();
        adjLanes[i].clear();
        adjBoth[i].clear();
    }
    solution = {0, 0, 0, 0};
}

bool elemInVec(vector<int> v, int elem) {
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

int bikeLaneLenV2() { // Kruskal
    int len = 0;
    setKruskal = new int[n];
    rankKruskal = new int[n];

    make_setKruskal();
    sort(adjKruskal.begin(), adjKruskal.end());

    for (auto w : adjKruskal) {
        int u = w.second.first;
        int v = w.second.second;
        if (findKruskal(u) != findKruskal(v)) {
            //cout << "Ligacao [" << u + 1 << "]" << "[" << v + 1 << "]" << " Comprimento:" << w.first << endl;
            len += w.first;
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
        int W = w[0];
        if (dfs[W] == -1) {
            Tarjan(W, visited);
            low[v] = min(low[v], low[W]);
        }
        else if (visited[W]) {
            low[v] = min(low[v], dfs[W]);
        }
    }

    int w = 0;
    vector<int> auxSolution;
    if (low[v] == dfs[v]) {         // v e raiz se se verificar
        while (S->top() != v) {
            w = (int)S->top();
            //cout << w + 1 << " ";
            visited[w] = false;
            auxSolution.push_back(w);
            S->pop();
        }
        w = (int)S->top();
        //cout << w + 1 << endl;
        visited[w] = false;
        auxSolution.push_back(w);
        S->pop();
    }
    int len = auxSolution.size();
    if (len > 1) {
        solution[0]++;
        if ((q > 1) && (len > solution[1])) {
            solution[1] = len;
        }
        if (q > 2) {
            //cout << "RAIZ:" << v + 1 << endl;
            adjKruskal.clear();
            for (int i : auxSolution) {
                for (auto j : adjBoth[i]) {
                    if (elemInVec(auxSolution, j[0])) {
                        adjKruskal.push_back({ j[1], {i, j[0]} });
                    }
                }
            }
            //int lenbikeLane = bikeLaneLen(auxSolution, v);
            int lenbikeLane = bikeLaneLenV2();
            if ((lenbikeLane > solution[2])) {
                solution[2] = lenbikeLane;
            }
            if (q > 3) {
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
        //if (!visited[i]) {
            //cout << "i[" << i + 1 << "]" << endl;
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
            //adj[y - 1].push_back({ x - 1, d });
            adjLanes[y - 1].push_back({ x - 1, d });
            adjBoth[x - 1].push_back({ y - 1, d });
            adjBoth[y - 1].push_back({ x - 1, d });
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