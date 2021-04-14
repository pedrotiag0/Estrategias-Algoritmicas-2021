#include <iostream>
#include <vector>

using namespace std;

// Variaveis Globais
int n, h, H;

int mod_abs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}
int mod_add(int a, int b, int mod) {
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}
int mod_sub(int a, int b, int mod) {
    return mod_add(a, -b, mod);
}

int arc() {
    return 0;
}

int main(){
    // Ler de maneira eficiente
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> solution;                           // Solucao

    int total;                                      // Numero de casos de teste
    cin >> total;

    for (int i = 0; i < total; i++) {               // Le e processa cada caso de teste
        cin >> n >> h >> H;
        //cin.ignore();
        //vector.clear();
        solution.push_back(arc());
    }

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }
}