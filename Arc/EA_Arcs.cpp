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
int** cache;

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

void printM(bool** M) {
    for (int y = H-1; y >= 0; y--) {
        for (int x = 0; x < n; x++) {
            cout << M[x][y] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void falseM(bool** M) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < H; y++) {
            M[x][y] = false;
        }
    }
}

void printCache() {
    for (int y = H - 1; y >= 0; y--) {
        for (int x = 0; x < n; x++) {
            cout << cache[x][y] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void zeroCache() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < H; y++) {
            cache[x][y] = false;
        }
    }
}

bool possivelDescer(int altura, int pos) { // Retorna true se for possivel descer e tocar no solo
    int restantesdir = n - (pos + 1);
    int melhorCasodir = altura - (restantesdir * (h - 1));
    int restantesesq = pos;
    int melhorCasoesq = altura - (restantesesq * (h - 1));
    return (melhorCasodir <= h && melhorCasoesq <= h);
}

int* calculaLimiares(int Hmax) {
    // Funcao que calcula os valores min e maximo que podemos subir e tocar (ou nao) no teto, contando que é sempre possível retornar ao solo.
    int limiares[2];

    // Limiar Inferior
    int alturaAtual = h;
    int i;
    for (i = 1; i < n; i++) {
        if ( (alturaAtual + (h - 1) < Hmax) && (possivelDescer(alturaAtual + (h - 1), i))) {
            alturaAtual += h - 1;
        }
        else {
            i--;
            break;
        }  
    }

    for (int j = 1; j < h; j++) { // Verifica se consegue "tocar" no teto
        if ((alturaAtual + j == Hmax) && (possivelDescer(alturaAtual + j, i + 1))) {
            i++;
            break;
        }
    }

    limiares[0] = i;

    // Limiar Superior
    int auxLimiar = n - limiares[0];
    alturaAtual = h;
    for (i = 1; i < n; i++) {
        if ((alturaAtual + 1 <= Hmax) && (possivelDescer(alturaAtual + 1, i))) {
            alturaAtual++;
        }
        else {
            i--;
            break;
        }
    }

    limiares[1] = min(auxLimiar, i);

    //cout << "Limiar Inferior: " << limiares[0] << endl;
    //cout << "Limiar Superior: " << limiares[1] << endl;

    return limiares;
}

int calculaDegraus(int x, int y) {

    if (y == h-1 && x == 0) {
        return 1;
    }

    if (x == 0 && y != h-1) {
        return 0;
    }

    if (cache[x][y]) {
        return cache[x][y];
    }

    for (int i = 1; i < h; i++) {
        cache[x][y] = calculaDegraus(x - 1, y - i);
        return cache[x][y];
    }

}

void rootPossibilidades(int x, int y) {
    int esqPossibilidades = 0;
    for (int i = 1; i < h; i++ ) {
        esqPossibilidades += calculaDegraus(x - 1, y - i);
    }

    int dirPossibilidades = 0;
    for (int i = 1; i < h; i++) {
        dirPossibilidades += calculaDegraus(n - x - 2, y - i);
    }

    possibilidades = mod_add(possibilidades, esqPossibilidades * dirPossibilidades, MODULO);

}

void arcV2() {
    int* limiares;
    // Cria M
    bool** M = new bool* [n];
    for (int i = 0; i < n; ++i) {
        M[i] = new bool[H];
    }
    falseM(M);
    for (int i = h + 1; i <= H; i++) { // Marca a altura dos retangulos chave
        limiares = calculaLimiares(i);
        for (int j = limiares[0]; j <= limiares[1]; j++) {
            if (possivelDescer(i, j)) {
                M[j][i - 1] = true;
            } 
        }
    }
    printM(M);
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < H; y++) {
            if (M[x][y]) { // Coordenadas de um retangulo chave
                rootPossibilidades(x, y);
            }
        }
    }
    // Destroi M
    for (int i = 0; i < n; ++i)
    {
        delete[] M[i];
    }
    delete[] M;
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
            // Cria M
            cache = new int* [n];
            for (int i = 0; i < n; ++i) {
                cache[i] = new int[H];
            }
            zeroCache();
            //printCache();
            arcV2();

            //calculaLimiares(H);
            solution.push_back(mod_abs(possibilidades, MODULO));
        }
        else
            solution.push_back(0);
    }

    for (int i = 0; i < n; ++i)
    {
        delete[] cache[i];
    }
    delete[] cache;

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

    return 0;
}