#include <iostream>
#include <vector>
#include <array>
#include <stack>

#define MAXPOI 1000

using namespace std;

// Variaveis globais
int n;                                              // Numero Pontos de Interesse
int m;                                              // Numero de conexões entre Pontos de Interesse
int q;                                              // Numero de perguntas (1-4)
vector<int> solution = {0, 0, 0, 0};                // Solucao

// Tarjan
int t;
int* low;
int* dfs;
stack<int>* S = new stack<int>();

array <vector<array<int,2>>, MAXPOI> adj;           // Lista de adjacencia

void cleanup() {
    for (int i = 0; i < n + 1; i++) {
        adj[i].clear();
    }
    solution = {0, 0, 0, 0};
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
    if (low[v] == dfs[v]) {
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
        if (len > solution[1])
            solution[1] = len;
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
            //adj[y-1].push_back({ x-1, d });
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

    delete[] low;
    delete[] dfs;

    return 0;
}