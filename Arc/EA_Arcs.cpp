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
int** cacheSubir;
int** cacheDescer;

int mod_abs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
    return mod_add(a, -b, mod);
}

void printCacheSubir() {
    cout << "CacheSubir:" << endl;
    for (int y = H - 1; y >= 0; y--) {
        for (int x = 0; x < n; x++) {
            cout << cacheSubir[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void printCacheDescer() {
    cout << "CacheDescer:" << endl;
    for (int y = H - 1; y >= 0; y--) {
        for (int x = 0; x < n; x++) {
            cout << cacheDescer[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void zeroCache() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < H; y++) {
            cacheSubir[x][y] = 0;
            cacheDescer[x][y] = 0;
            /*if (y < h) {
                cacheDir[x][y] = 1;
            }*/
        }
    }
    for (int i = n - 1; i > 1; i--)
    {
        cacheDescer[i][h - 1] = 1;
    }
    // Prepara a matriz de subida (esquerda) com o nº de combinacoes possiveis para subir até determinada coordenada
    cacheSubir[0][h - 1] = 1;
}

bool possivelDescer(int altura, int pos) { // Retorna true se for possivel descer e tocar no solo
    int restantesdir = n - (pos + 1);
    int melhorCasodir = altura - (restantesdir * (h - 1));
    int restantesesq = pos;
    int melhorCasoesq = altura - (restantesesq * (h - 1));
    return (melhorCasodir <= h && (melhorCasoesq <= h));
}

int calculaLimiares(int Hmax) {
    // Funcao que calcula os valores min e maximo que podemos subir e tocar (ou nao) no teto, contando que é sempre possível retornar ao solo.

    int alturaAtual = h;
    int i;
    for (i = 1; i < n; i++) {
        if ((alturaAtual + (h - 1) < Hmax) && (possivelDescer(alturaAtual + (h - 1), i))) {
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

    return i;
}

void arcV3esq() {


    for (int i = 1; i < n - 1; i++)
    {
        for (int j = h; j < H; j++) //Avanca ao longo da matriz
        {
            if (j > ((i + 1) * (h - 1)))
                break;
            // Esq
            cacheSubir[i][j] = mod_sub(cacheSubir[i][j - 1], cacheSubir[i - 1][j - h], MODULO);
            cacheSubir[i][j] = mod_add(cacheSubir[i][j], cacheSubir[i - 1][j - 1], MODULO);

            // Dir
            int inv_i = n - (i + 1);
            if(j - 1 != h - 1)
                cacheDescer[inv_i][j] = mod_sub(cacheDescer[inv_i][j - 1], cacheDescer[inv_i + 1][j - h], MODULO);
            cacheDescer[inv_i][j] = mod_add(cacheDescer[inv_i][j], cacheDescer[inv_i + 1][j - 1], MODULO);
        }
    }

    //printCacheDescer();
    //printCacheSubir();

    for (int i = h + 1; i <= H; i++)
    {
        int limiar = calculaLimiares(i);
        for (int j = limiar; j < n - limiar; j++)
        {
            if (j > ((i + 1) * (h - 1)))
                break;
            long long e = cacheSubir[j][i - 1];
            long long d = cacheDescer[j][i - 1];
            int res = int((e * d) % MODULO);
            possibilidades = mod_add(possibilidades, res, MODULO);
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
            possibilidades = 0;
            
            // Cria caches
            cacheSubir = new int* [n];
            cacheDescer = new int* [n];
            for (int i = 0; i < n; ++i) {
                cacheSubir[i] = new int[H];
                cacheDescer[i] = new int[H];
            }
            zeroCache();
            arcV3esq();
            solution.push_back(mod_abs(possibilidades, MODULO));
        }
        else
            solution.push_back(0);
    }

    // Cleanup das caches
    for (int i = 0; i < n; ++i)
    {
        delete[] cacheSubir[i];
        delete[] cacheDescer[i];
    }
    delete[] cacheSubir;
    delete[] cacheDescer;

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

    return 0;
}