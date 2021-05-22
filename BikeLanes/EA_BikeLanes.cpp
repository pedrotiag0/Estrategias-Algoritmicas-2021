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

array <vector<array<int, 2>>, MAXPOI> adj;          // Lista de adjacencia (ponto liga a pontos)
array <vector<array<int, 2>>, MAXPOI> adjLanes;     // Lista de adjacencia (usada para ver o comprimento das lanes) (pontos que se ligam ao ponto)
array <vector<array<int, 2>>, MAXPOI> adjBoth;      // Lista de adjacencia ambas direcoes

void cleanup() {
    for (int i = 0; i < n + 1; i++) {
        adj[i].clear();
        adjLanes[i].clear();
        adjBoth[i].clear();
    }
    solution = {0, 0, 0, 0};
}

int bikeLaneLen(vector<int> circuito, int raiz) {
    int len = 0;
    int auxlen, auxJ;
    bool* visited = new bool[n];
    int* visitedRaiz = new int[n];
    vector<int> visitedByRaiz;
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        visitedRaiz[i] = -1;
    }
        

    for (auto w : adj[raiz]) { // Pontos que a raiz aponta
        auxlen = -1;
        if (find(circuito.begin(), circuito.end(), w[0]) == circuito.end()) {
            continue;
        }
        int W = w[0];                   // Ponto
        int dist = w[1];                // Distancia
        if ((dist < auxlen) || (auxlen == -1)) {
            auxlen = dist;
            for (auto j1 : adjLanes[raiz]) {
                if ((j1[0] == raiz) && (j1[1] < auxlen)) {
                    auxlen = j1[1];
                }
            }
        }
        if (auxlen != -1) {
            len += auxlen;
            visitedRaiz[W] = auxlen;
            visitedByRaiz.push_back(W);
            //cout << "Ligacao [" << raiz + 1 << "]" << "[" << W + 1 << "]" << " Comprimento:" << auxlen << endl;
        }
    }

    for (auto w : adjLanes[raiz]) { // Pontos que a apontam para a raiz
        auxlen = -1;
        if (find(circuito.begin(), circuito.end(), w[0]) == circuito.end()) {
            continue;
        }
        int W = w[0];                   // Ponto
        int dist = w[1];                // Distancia
        if ((dist < auxlen) || (auxlen == -1)) {
            auxlen = dist;
            for (auto j1 : adj[raiz]) {
                if ((j1[0] == raiz) && (j1[1] < auxlen)) {
                    auxlen = j1[1];
                }
            }
        }
        if (auxlen != -1) {
            if (visitedRaiz[W] == -1) {
                len += auxlen;
                visitedByRaiz.push_back(W);
                //cout << "Ligacao [" << raiz + 1 << "]" << "[" << W + 1 << "]" << " Comprimento:" << auxlen << endl;
            }
            else if ((visitedRaiz[W] != -1) && (auxlen < visitedRaiz[W])) {
                len -= visitedRaiz[W];
                len += auxlen;
                //cout << "Ligacao [" << raiz + 1 << "]" << "[" << W + 1 << "] Replaced! " << " Comprimento:" << auxlen << endl;
            }
        }
    }

    for (auto i : circuito) {
        if ((!visited[i]) && (i != raiz)) {
        //if (true) {
            auxlen = -1;
            auxJ = -1;
            for (auto j : adjLanes[i]) {
                if (( j[0] == raiz) || (find(circuito.begin(), circuito.end(), j[0]) == circuito.end()) || (find(visitedByRaiz.begin(), visitedByRaiz.end(), j[0]) != visitedByRaiz.end() && find(visitedByRaiz.begin(), visitedByRaiz.end(), i) != visitedByRaiz.end())) {
                    continue;
                }
                int J = j[0];                   // Ponto
                int dist = j[1];                // Distancia
                if ((dist < auxlen) || (auxlen == -1)) {
                    auxlen = dist;
                    auxJ = J;
                    for (auto j1 : adj[i]) {
                        if ((j1[0] == auxJ) && (j1[1] < auxlen) && (!visited[j1[0]])) {
                            auxlen = j1[1];
                        }
                    }
                }
            }
            if (auxJ != -1) {
                len += auxlen;
                visited[i] = true;
                visited[auxJ] = true;
                //cout << "Ligacao [" << i + 1 << "]" << "[" << auxJ + 1 << "]" << " Comprimento:" << auxlen << endl;
            }
        }
    }
    
    /*
    cout << "Circuito: ";
    for (auto i : circuito)
        cout << i+1 << " ";
    cout << "LEN: " << len << endl;
    */

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
            int lenbikeLane = bikeLaneLen(auxSolution, v);
            if ((lenbikeLane > solution[3])) {
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
            adjLanes[y - 1].push_back({ x - 1, d });
            adjBoth[x - 1].push_back({ y - 1, d });
            adjBoth[y - 1].push_back({ x - 1, d });
        }
        //cout << "Caso [" << i + 1 << "]:" << endl;
        if (adj.size() < 0)
            return 0;
        bikeLanes();
        //cout << "R[";
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