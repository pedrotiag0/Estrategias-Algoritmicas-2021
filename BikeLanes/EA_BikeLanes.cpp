#include <iostream>
#include <vector>
#include <array>

#define MAXPOI 1000

using namespace std;

int n;                                              // Numero Pontos de Interesse
int m;                                              // Numero de conexões entre Pontos de Interesse
int q;                                              // Numero de perguntas (1-4)

array <vector<array<int,2>>, MAXPOI> adj;           // Lista de adjacencia

void cleanup() {
    for (int i = 0; i < MAXPOI; i++) {
        adj[i].clear();
    }
}

void bikeLanes() { // Tarjan
    int* low = new int[m];
    int* dfs = new int[m];
}

int main() {
    // Ler de maneira eficiente
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    vector<int> solution;                           // Solucao

    int total;                                      // Numero de casos de teste
    cin >> total;

    for (int i = 0; i < total; i++) {
        cin >> n >> m >> q;
        for (int j = 0; j < m; j++) {
            int x, y, d;
            cin >> x >> y >> d;
            adj[x].push_back({ y, d });
            adj[y].push_back({ x, d });
        }
        // chamar funcao magica de 200 pontos
        cleanup();
    }

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

    return 0;
}