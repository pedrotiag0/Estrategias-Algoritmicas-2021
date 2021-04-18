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

int mod_abs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
    return mod_add(a, -b, mod);
}

int mustDescend(int* sala, int pos) {
    int restantes = n - (pos + 1);
    int alturaAtual = sala[pos];
    int melhorCaso = alturaAtual - restantes * (h - 1);
    if (melhorCaso == 0) // Deve descer de imediato
        return 1;
    else if (melhorCaso < 0) // Pode continuar ou entao descer
        return 0;
    else
        return -1; // Caso invalido que nao deve ser contabilizado
}

void buildArc(int* sala, int pos, bool subir) {
    // Verificacao Inicial
    if (pos == 0) {
        sala[pos] = 0;
        buildArc(sala, pos + 1, true);
    }

    if (pos >= n)
        return;

    int alturaAtual;

    if (subir) {
        // Ascendente
        alturaAtual = sala[pos - 1];
        for (int i = 1; i < h; i++) {
            if (alturaAtual + i + h <= H) {
                sala[pos] = alturaAtual + i;
                switch (mustDescend(sala, pos)) {
                case 2:
                    buildArc(sala, pos + 1, true);
                    break;
                case 1:
                    buildArc(sala, pos + 1, false);
                    break;
                case 0:
                    buildArc(sala, pos + 1, true);
                    buildArc(sala, pos + 1, false);
                    break;
                case -1:
                    return;
                }
            }
        }
    }
    else {
        // Descendente
        alturaAtual = sala[pos - 1];
        for (int i = 1; i < h; i++) {
            if (alturaAtual - i == 0) {
                possibilidades++;
            }
            else if(alturaAtual - i > 0){
                buildArc(sala, pos + 1, false);
            }
        }
    }
}

void arc(int* sala) {
    /*for (int i = 0; i < n; i++) {
        buildArc(sala, i, true);
    }*/
    buildArc(sala, 0, true);
}

int main(){
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