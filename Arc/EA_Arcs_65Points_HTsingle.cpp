//      EA   |   2020/2021   |   FCTUC
//
// Autores:     Nuno Silva      2018285621
//              Pedro Marques   2018285632
//
// ________________________________________
//| ------ Problem B - ARChitecture ------ |

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

#define MODULO 1000000007

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

// Variaveis Globais
// n -> Comprimento da sala | h -> Altura dos blocos | H -> Altura da sala
int n, h, H;
int possibilidades;
int** cache;
unordered_map <string, int> cacheHT; // Chave é [x, y]
unordered_map <string, int>::iterator it;
int** cacheDir;
int countCache;

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
    for (int y = H - 1; y >= 0; y--) {
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
            cache[x][y] = -1;
            cacheDir[x][y] = -1;
        }
    }
}

bool possivelDescer(int altura, int pos) { // Retorna true se for possivel descer e tocar no solo
    int restantesdir = n - (pos + 1);
    int melhorCasodir = altura - (restantesdir * (h - 1));
    int restantesesq = pos;
    int melhorCasoesq = altura - (restantesesq * (h - 1));
    return (melhorCasodir <= h && (melhorCasoesq <= h));
}

bool possivelDescerV2(int altura, int pos) { // Retorna true se for possivel descer e tocar no solo
    int restantesdir = n - (pos + 1);
    int melhorCasodir = altura - (restantesdir * (h - 1));
    bool possivelEsq = false;
    for (int j = pos; j <= ((h - 1) * (pos)); j++) {       // Pode ter descido destas formas diferentes                      
        int alturaAtual = altura - j;
        if (alturaAtual == h) {
            possivelEsq = true;
            break;
        }
    }

    //int melhorCasoesq = altura - (restantesesq * (h - 1));
    return ((melhorCasodir <= h) && (possivelEsq));
}

bool possivelDescerEsq(int altura, int pos) {
    for (int j = pos; j <= ((h - 1) * (pos)); j++) {       // Pode ter descido destas formas diferentes                      
        int alturaAtual = altura - j;
        if (alturaAtual == h) {
            return true;
        }
    }
    return false;
}

int calculaLimiares(int Hmax) {
    // Funcao que calcula os valores min e maximo que podemos subir e tocar (ou nao) no teto, contando que é sempre possível retornar ao solo.
    //int limiares[2];

    // Limiar Inferior
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
    //limiares[0] = i;

    // Limiar Superior
    /*int auxLimiar = n - limiares[0];
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

    limiares[1] = min(auxLimiar, i);*/

    //cout << "Limiar Inferior: " << limiares[0] << endl;
    //cout << "Limiar Superior: " << limiares[1] << endl;

    //return limiares;
}

int calculaDegraus(int x, int y) {
    if (x < 0 || y < 0)
        return 0;

    if (y == h - 1 && x == 0) {
        return 1;
    }

    if (x == 0 && y != h - 1) {
        return 0;
    }

    /*if (cache[x][y] != -1) {
        countCache++;
        return cache[x][y]; // memoization
    }


    int aux = 0;
    for (int i = 1; i < h; i++) {
        aux += calculaDegraus(x - 1, y - i);
    }
    cache[x][y] = aux;
    return cache[x][y];*/

    //it = cacheHT.find({x, y});
    string nome = to_string(x) + " " + to_string(y);
    //cout << nome << endl;
    it = cacheHT.find(nome);
    if (it != cacheHT.end()) { //Existe
        countCache++;
        return it->second;
    }
    int aux = 0;
    for (int i = 1; i < h; i++) {
        aux += calculaDegraus(x - 1, y - i);
    }
    //int aux2[2] = {x, y};
    cacheHT.emplace(nome, aux );
    return aux;
}

int calculaDegrausDirV0(int x, int y) {
    if (x < 0 || y < 0)
        return 0;

    if (y == h - 1) {
        return 1;
    }

    if (y != h - 1 && x == 0) {
        return 0;
    }

    if (cacheDir[x][y] != -1) {
        countCache++;
        return cacheDir[x][y]; // memoization
    }
    int aux = 0;
    for (int i = 1; i < h; i++) {
        aux += calculaDegrausDirV0(x - 1, y - i);
    }
    cacheDir[x][y] = aux;
    return cacheDir[x][y];
}

int calculaDegrausDir(int x, int y) {
    x = n - x - 1;
    int combinacoes = 0;
    for (int i = x; i >= 0; i--)
    {
        combinacoes += calculaDegraus(i, y);
    }
    return combinacoes;
}

/*int calculaDegrausEsqBU(int x, int y) {
    int aux = 0;
    for (int i = 0; i < x; i++) {
        break;
    }
    return aux;
}*/

int calculaDegrausDirBU(int x, int y) { // Nao funcional
    int aux = 0;
    int alturaAtual;
    for (int i = x; i < n; i++) {                               // Percorre ate n
        for (int j = (i - x) + 1; j <= ((h - 1) * ((i - x) + 1)); j++) {       // Pode ter descido destas formas diferentes                      
            alturaAtual = y - j;
            if (alturaAtual == h) {
                aux++;
                break;
            }
            /*for (int k = 1; k < h; k++) {
                if (alturaAtual - k == h) {                         // Verifica se toca no chao
                    // Guarda na cache
                    aux++;
                }
            }*/
        }
    }
    return aux;
}

int calculaDegrausDirBUV2(int x, int y) {
    int aux = 0;
    int alturaAtual;
    int posRestantes = n - x - 1;;
    int* alturasCache = new int[posRestantes];
    for (int i = 0; i < posRestantes; i++) {
        alturasCache[i] = -1;
    }
    for (int i = 0; i < posRestantes; i++) {                               // Percorre ate n
        for (int j = h - 1; j > 0; j--) {
            if (i > 0) {
                if (alturasCache[i - 1] > 0) {
                    alturaAtual = y - alturasCache[i - 1] - j;
                }
                else {
                    delete[] alturasCache;
                    return aux;
                }
            }
            else {
                alturaAtual = y - j;
            }
            if ((alturaAtual > h)) {
                alturasCache[i] = j; // Guarda altura para proxima iteracao
                aux += j;
                break;
            }
            else if (alturaAtual == h) {
                alturasCache[i] = j - 1;
                aux += 1;
                break;
            }
        }
    }
    delete[] alturasCache;
    return aux;
}

void rootPossibilidades(int x, int y) { // Corrigir parametros das funcoes recursivas

    //cout << "X: " << x << " | Y: " << y << endl;

    int esqPossibilidades = 0;
    int dirPossibilidades = 0;
    for (int i = 1; i < h; i++) {
        esqPossibilidades += calculaDegraus(x - 1, y - i);
        dirPossibilidades += calculaDegrausDir(x + 1, y - i);
        //dirPossibilidades += calculaDegrausDirV0(n - x - 2, y - i);

        //esqPossibilidades += calculaDegrausEsqBU(x - 1, y - i);
        //dirPossibilidades += calculaDegrausDirBU(x, y + 1);
        //cout << "esqPossibilidades ["<< i <<"]: " << esqPossibilidades << endl;
        //cout << "DirPossibilidades [" << i << "]: " << dirPossibilidades << endl;
    }
    //dirPossibilidades = calculaDegrausDirBUV2(x, y+1);

    //cout << "Esq: " << esqPossibilidades << endl;
    //cout << "Dir: " << dirPossibilidades << endl;
    //cache[x][y] = esqPossibilidades;

    possibilidades = mod_add(possibilidades, esqPossibilidades * dirPossibilidades, MODULO);

}

void arcV2() {
    //int* limiares;
    int limiares;
    // Cria M
    /*bool** M = new bool* [n];
    for (int i = 0; i < n; ++i) {
        M[i] = new bool[H];
    }*/
    //falseM(M);
    for (int i = h + 1; i <= H; i++) { // Marca a altura dos retangulos chave
        limiares = calculaLimiares(i);
        for (int j = limiares; j < n - limiares; j++) {
            if (possivelDescerV2(i, j)) { // altura, pos
                //M[j][i - 1] = true;
                rootPossibilidades(j, i - 1);
            }
        }
    }
    //printM(M);
    /*for (int x = 0; x < n; x++) {
        for (int y = 0; y < H; y++) {
            if (M[x][y]) { // Coordenadas de um retangulo chave
                rootPossibilidades(x, y);
            }
        }
    }*/
    // Destroi M
    /*for (int i = 0; i < n; ++i)
    {
        delete[] M[i];
    }
    delete[] M;*/
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
            countCache = 0;
            // Cria cache
            /*cache = new int* [n];
            cacheDir = new int* [n];
            for (int i = 0; i < n; ++i) {
                cache[i] = new int[H];
                cacheDir[i] = new int[H];
            }
            zeroCache();*/
            cacheHT.clear();
            //printCache();
            arcV2();
            //cout << "Cache acedida " << countCache << " vezes." << endl;
            //calculaLimiares(H);
            solution.push_back(mod_abs(possibilidades, MODULO));
        }
        else
            solution.push_back(0);
    }

    /*for (int i = 0; i < n; ++i)
    {
        delete[] cache[i];
        delete[] cacheDir[i];
    }
    delete[] cache;
    delete[] cacheDir;*/

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

    return 0;
}