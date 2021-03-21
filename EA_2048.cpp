//      EA   |   2020/2021   |   FCTUC
//
// Autores:     Nuno Silva      2018285621
//              Pedro Marques   2018285632
//
// ________________________________________
//| ----- Problem A - 2048 clean up! ----- |

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define ESQ 1
#define DIR 2
#define UP 3
#define DWN 4

using namespace std;
int N, M, limiar, best;

void imprimeTabuleiro(vector<int> tabuleiro) {      // Funcao utilizada para imprimir o tabuleiro
    int paragrafo = 0;
    cout << "_______________________" << endl;
    for (int i = 0; i < N * N; i++) {
        if (paragrafo == N) {
            paragrafo = 0;
            cout << endl;
        }
        paragrafo++;
        cout << tabuleiro[i] << " ";
    }
    cout << endl << "_______________________" << endl;
}

vector<int> swipeRight(vector<int> vec) { 
    vector<int>::iterator inicio_linha;
    bool flag, modificado = false;

    for (int i = 0; i < N; i++)         //  Avança a linha do tabuleiro
    {
        inicio_linha = vec.begin() + (i * N);
        flag = true;
        while (flag)
        {
            flag = false;
            for (vector<int>::iterator it = inicio_linha + N - 1; it != inicio_linha; it--) // Vai ordenar a linha [4][0][0][4] -> [0][0][4][4]
            {
                if ((*it == 0) && (*(it - 1) != 0))
                {
                    *it = *(it - 1);                                                //  [4][0][0][4] -> [4][4][0][4]
                    *(it - 1) = 0;                                                  //  [4][4][0][4] -> [0][4][0][4]
                    flag = true;                                                    //  Repete iterativamente até a linha ficar ordenada
                    modificado = true;
                }
            }
        }
        for (vector<int>::iterator it = inicio_linha + N - 1; it > inicio_linha; it--) //it varia do fim da linha até ao index 1 (não chega ao 1º elemento da linha)
        {
            if ((*it == *(it - 1)) && (*it != 0))
            {
                *it = *it * 2;          //  [0][0][2][2] -> [0][0][2][4]           [2][2][0][4] -> [2][4][0][4]
                //*(it - 1) = 0;          //  [0][0][2][4] -> [0][0][0][4]           [2][4][0][4] -> [0][4][0][4]

                //ANDAR O RESTO DA LINHA UMA CASA PARA A DIREITA
                for (vector<int>::iterator aux = it - 1; aux > inicio_linha; aux--)
                {
                    if (*aux != 0)
                    {
                        *aux = *(aux - 1);
                    }
                    else
                    {
                        break;
                    }
                }
                *inicio_linha = 0;

                modificado = true;
            }
        }
    }
    if (!modificado) {
        //memo.emplace(vec, DIR);
        vec[0] = -1;
        return vec;
    }
    return vec;
}

vector<int> swipeLeft(vector<int> vec) { 
    vector<int>::iterator fim_linha;
    bool flag, modificado = false;

    for (int i = 0; i < N; i++)         //  Avança a linha do tabuleiro
    {
        fim_linha = vec.begin() + (i * N) + (N - 1);
        flag = true;
        while (flag)
        {
            flag = false;
            for (vector<int>::iterator it = fim_linha - (N - 1); it < fim_linha; it++) // Vai ordenar a linha [4][0][0][4] -> [4][4][0][0]
            {
                if ((*it == 0) && (*(it + 1) != 0))
                {
                    *it = *(it + 1);                                                //  [4][0][0][4] -> [4][0][4][4]
                    *(it + 1) = 0;                                                  //  [4][0][4][4] -> [4][0][4][0]
                    flag = true;                                                    //  Repete iterativamente até a linha ficar ordenada
                    modificado = true;
                }
            }
        }
        for (vector<int>::iterator it = fim_linha - (N - 1); it < fim_linha; it++) //it varia do inicio da linha até ao index N (não chega ao ultimo elemento da linha)
        {
            if ((*it == *(it + 1)) && (*it != 0))
            {
                *it = *it * 2;          //  [2][2][0][0] -> [4][2][0][0]           [4][0][2][2] -> [4][0][4][2]
                //*(it + 1) = 0;          //  [4][2][0][0] -> [4][0][0][0]           [4][0][4][2] -> [4][0][4][0]

                for (vector<int>::iterator aux = it + 1; aux < fim_linha; aux++)
                {
                    if (*aux != 0)
                    {
                        *aux = *(aux + 1);
                    }
                    else
                    {
                        break;
                    }
                }
                *fim_linha = 0;

                modificado = true;
            }
        }
        flag = true;

    }
    if (!modificado) {
        vec[0] = -1;
        return vec;
    }
    return vec;
}

vector<int> swipeUp(vector<int> vec) { 
    vector<int>::iterator inicio_coluna;
    bool flag, modificado = false;

    for (int i = 0; i < N; i++)         //  Avança a coluna do tabuleiro
    {
        inicio_coluna = vec.begin() + i;
        flag = true;
        while (flag)
        {
            flag = false;
            for (vector<int>::iterator it = inicio_coluna; it < inicio_coluna + (N * (N - 1)); it += N)
            {
                if ((*it == 0) && (*(it + N) != 0))
                {
                    *it = *(it + N);
                    *(it + N) = 0;
                    flag = true;                                                    //  Repete iterativamente até a coluna ficar ordenada
                    modificado = true;
                }
            }
        }
        for (vector<int>::iterator it = inicio_coluna; it < inicio_coluna + (N * (N - 1)); it += N) //it varia do inicio da coluna até ao final da mesma (não chega ao ultimo elemento da coluna)
        {
            if ((*it == *(it + N)) && (*it != 0))
            {
                *it = *it * 2;
                //*(it + N) = 0;

                for (vector<int>::iterator aux = it + N; aux < inicio_coluna + (N * (N - 1)); aux += N)
                {
                    if (*aux != 0)
                    {
                        *aux = *(aux + N);
                    }
                    else
                    {
                        break;
                    }
                }
                *(inicio_coluna + (N * (N - 1))) = 0;

                modificado = true;
            }
        }
    }
    if (!modificado) {
        vec[0] = -1;
        return vec;
    }
    return vec;
}

vector<int> swipeDown(vector<int> vec) {
    vector<int>::iterator fim_coluna;
    bool flag, modificado = false;
    for (int i = 0; i < N; i++)         //  Avança a coluna do tabuleiro
    {

        fim_coluna = vec.begin() + i + (N * (N - 1));
        flag = true;
        while (flag)
        {
            flag = false;
            for (vector<int>::iterator it = fim_coluna; it > fim_coluna - (N * (N - 1)); it -= N)
            {
                if ((*it == 0) && (*(it - N) != 0))
                {
                    *it = *(it - N);
                    *(it - N) = 0;
                    flag = true;                                                    //  Repete iterativamente até a coluna ficar ordenada
                    modificado = true;
                }
            }
        }
        for (vector<int>::iterator it = fim_coluna; it > fim_coluna - (N * (N - 1)); it -= N) //it varia do final da coluna até ao inicio da mesma (não chega ao ultimo elemento da coluna)
        {
            if ((*it == *(it - N)) && (*it != 0))
            {
                *it = *it * 2;

                for (vector<int>::iterator aux = it - N; aux > fim_coluna - (N * (N - 1)); aux -= N)
                {
                    if (*aux != 0)
                    {
                        *aux = *(aux - N);
                    }
                    else
                    {
                        break;
                    }
                }
                *(fim_coluna - (N * (N - 1))) = 0;

                modificado = true;
            }
        }
    }
    if (!modificado) {
        vec[0] = -1;
        return vec;
    }
    return vec;
}

vector<int> swipeRightBestCaseScenario(vector<int> vec)
{
    int max = (N / (int)2) * N;
    int count = 0;
    vector<int>::iterator end = vec.end() - 1;
    vector<int>::iterator begin = vec.begin();
    for (vector<int>::iterator it = end; it > begin; it--)
    {
        if (count > max)
        {
            break;
        }
        if ((*it == *(it - 1)) && (*it != 0))
        {
            count++;

            *it = *it * 2;

            //ANDAR O RESTO DA LINHA UMA CASA PARA A DIREITA
            for (vector<int>::iterator aux = it - 1; aux > begin; aux--)
            {
                if (*aux != 0)
                {
                    *aux = *(aux - 1);
                }
                else
                {
                    break;
                }
            }
            *begin = 0;
        }
    }
    return vec;
}

int bestCaseScenario(vector<int> vec) // Encontra um nr minimo de swipes que devem ser feitos para resolver o problema
{
    sort(vec.begin(), vec.end());
    int jogadas = 0;

    while (*(vec.end() - 2) != 0)
    {
        vec = swipeRightBestCaseScenario(vec);
        jogadas++;
    }
    return jogadas;
}

bool verificaVitoria(vector<int> tabuleiro) { // Verifica se o tabuleiro ja foi resolvido
    bool vitoria = false;
    for (int i = 0; i < N * N; i++) {
        if ((tabuleiro[i] != 0) && (vitoria == false))
            vitoria = true;
        else if ((tabuleiro[i] != 0) && (vitoria == true))
            return false;
    }
    return vitoria;
}

bool verificaPossibilidade(vector<int> tabuleiro) { // verifica se o tabuleiro tem, de facto, solucao
    sort(tabuleiro.begin(), tabuleiro.end()); // ordena tabuleiro
    int i = 0;
    int aux;
    int count = 0;
    for (vector<int>::iterator it = tabuleiro.begin(); it != tabuleiro.end(); ++it) {
        if ((it + 1) == tabuleiro.end()) {
            return true;
        }
        if ((*it != 0) && (*(it + 1) != 0) && (*it != *(it + 1))) {
            return false;
        }
        else if (*it == *(it + 1) && (*it != 0)) {
            i = 2;
            *(it + 1) = *it * 2;
            *it = 0;
            count++;
            while ((it + i) != tabuleiro.end()) { // ordena com selection sort
                if (*(it + i - 1) <= *(it + i)) {
                    break;
                }
                aux = *(it + i - 1);
                *(it + i - 1) = *(it + i);
                *(it + i) = aux;
                i++;
            }
        }
    }
    return true;
}

class Node {
public:
    int path;
    int nivel;
    vector<int> tabuleiro_inicial;

    Node(int nivel, vector<int> tabuleiro_inicial, int path) //CONSTRUTOR
    {

        this->nivel = nivel;

        if (this->nivel >= limiar)
        {
            this->path = path;
            return;
        }

        if (this->nivel == 0)
        {
            this->path = 0;
        }
        else
        {
            this->path = path;
        }

        switch (path)
        {
        case ESQ:
            this->tabuleiro_inicial = swipeLeft(tabuleiro_inicial);
            break;
        case DIR:
            this->tabuleiro_inicial = swipeRight(tabuleiro_inicial);
            break;
        case UP:
            this->tabuleiro_inicial = swipeUp(tabuleiro_inicial);
            break;
        case DWN:
            this->tabuleiro_inicial = swipeDown(tabuleiro_inicial);
            break;
        default:
            this->tabuleiro_inicial = tabuleiro_inicial;
            break;
        }


        if (this->tabuleiro_inicial[0] != -1) { //Nao houve alteracoes no tabuleiro, logo nao e preciso continuar
            
            if (bestCaseScenario(this->tabuleiro_inicial) > (M - nivel)) {
                return;
            }

            if (verificaVitoria(this->tabuleiro_inicial))
            {
                limiar = this->nivel;
            }
            else if (this->nivel < limiar - 1) {
                //CRIAR OS FILHOS
                Node filho_down(this->nivel + 1, this->tabuleiro_inicial, DWN);
                Node filho_left(this->nivel + 1, this->tabuleiro_inicial, ESQ);
                Node filho_right(this->nivel + 1, this->tabuleiro_inicial, DIR);
                Node filho_up(this->nivel + 1, this->tabuleiro_inicial, UP);
            }
        }
    }
};

string jogo_2048(vector<int> vec) {


    if (!verificaPossibilidade(vec)) {
        return "no solution";
    }

    best = bestCaseScenario(vec);

    if (best > M) {
        return "no solution";
    }
    
    // Creation of tree
    Node root(0, vec, 0);
    
    if (limiar > M) {
        return "no solution";
    }
    return to_string(limiar);
}

int main()
{
    // Ler de maneira eficiente
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<string> solution;                        // Solucao

    vector<int> tabuleiro_2048;                     // Tabuleiro do jogo
    int tabuleiro_elem;

    int total;                                      // Numero de casos de teste
    cin >> total;

    for (int i = 0; i < total; i++) {              // Le e processa cada caso de teste
        cin >> N >> M;
        limiar = M + 1;
        cin.ignore();
        tabuleiro_2048.clear();
        for (int j = 0; j < N * N; j++) {
            cin >> tabuleiro_elem;
            tabuleiro_2048.push_back(tabuleiro_elem);
        }
        solution.push_back(jogo_2048(tabuleiro_2048));
    }
    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }
}