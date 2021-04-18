//      EA   |   2020/2021   |   FCTUC
//
// Autores:     Nuno Silva      2018285621
//              Pedro Marques   2018285632
//
// ________________________________________
//| ------ Problem B - ARChitecture ------ |

#include <iostream>
#include <vector>

using namespace std;

#define MODULO 1000000007

// Variaveis Globais
// n -> Comprimento da sala | h -> Altura dos blocos | H -> Altura da sala
int n, h, H;
int possibilidades;

void printComb(int* sala) {
    cout << "Solucao " << possibilidades << ": [ ";
    for (int i = 0; i < n; i++) {
        cout << sala[i] << " ";
    }
    cout << "]" << endl;
}

int mod_abs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
    return mod_add(a, -b, mod);
}

void arc(int* sala) {
    /*for (int i = 0; i < n; i++) {
        buildArc(sala, i, true);
    }*/
    //buildArc(sala, 0, true);
    int aux;
    for (int i = 2; i < n; i++) {           // Todos os casos possiveis
        aux = (int)(pow((h-1), (i-1)));
        //cout << "AUX1: " << aux << endl;
        //possibilidades = mod_add(possibilidades, aux, MODULO);
        possibilidades += aux;
    }

    // Falta distinguir quando fazemos elevado a h-1, h-2, h-3... Ou seja, validar a altura restante que conseguimos subir.
    
    for (int i = 2; i < n; i++) {           // Subtrai a todos os casos possiveis os casos onde ultrapassa a altura maxima
        for (int j = 1; j < h ; j++) {      // Contar para todos os tamanhos do degrau que ultrapassam H
            aux = (int)(pow(j, (i - 1)));   // Por alterar
            //cout << "AUX2: " << aux << endl;
            //possibilidades = mod_sub(possibilidades, aux, MODULO);
            possibilidades -= aux;
        }
    }
}

int main() {
    // Ler de maneira eficiente
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> solution;                           // Solucao

    int total;                                      // Numero de casos de teste
    cin >> total;

    if (total > 20)
        return 0;

    for (int i = 0; i < total; i++) {               // Le e processa cada caso de teste
        cin >> n >> h >> H;
        if ((n <= 500) && (h <= 500) && (H <= 60000) && (n > 2) && (h < H)) {
            int* sala = new int[n];
            for (int j = 0; j < n; j++) {
                sala[j] = -1;
            }
            possibilidades = 0;
            arc(sala);
            solution.push_back(mod_abs(possibilidades, MODULO));
        }
        else
            solution.push_back(0);
    }

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

    return 0;
}