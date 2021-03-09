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

using namespace std;

int N, limiar;

vector<int> swipeRight(vector<int> vec, int N) { // Done
    vector<int>::iterator inicio_linha;
    bool flag;

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
                }
            }
        }
        for (vector<int>::iterator it = inicio_linha + N - 1; it > inicio_linha; it--) //it varia do fim da linha até ao index 1 (não chega ao 1º elemento da linha)
        {
            if ((*it == *(it - 1)) && (*it != 0)  )
            {
                *it = *it * 2;          //  [0][0][2][2] -> [0][0][2][4]           [2][2][0][4] -> [2][4][0][4]
                *(it - 1) = 0;          //  [0][0][2][4] -> [0][0][0][4]           [2][4][0][4] -> [0][4][0][4]
                //it--;                   //  Pode ser ainda mais otimizado
            }
        }
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
                }
            }
        }
    }
    return vec;
}

vector<int> swipeLeft(vector<int> vec, int N) { // Done
    vector<int>::iterator fim_linha;
    bool flag;

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
                }
            }
        }
        for (vector<int>::iterator it = fim_linha - (N - 1); it < fim_linha; it++) //it varia do inicio da linha até ao index N (não chega ao ultimo elemento da linha)
        {
            if ((*it == *(it + 1)) && (*it != 0))
            {
                *it = *it * 2;          //  [2][2][0][0] -> [4][2][0][0]           [4][0][2][2] -> [4][0][4][2]
                *(it + 1) = 0;          //  [4][2][0][0] -> [4][0][0][0]           [4][0][4][2] -> [4][0][4][0]
                //it++;                   //  Pode ser ainda mais otimizado !WARNING!
            }
        }
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
                }
            }
        }
    }
    return vec;
}

vector<int> swipeUp(vector<int> vec, int N) { // Done
    vector<int>::iterator inicio_coluna;
    bool flag;

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
                }
            }
        }
        for (vector<int>::iterator it = inicio_coluna ; it < inicio_coluna + (N*(N - 1)); it += N) //it varia do inicio da coluna até ao final da mesma (não chega ao ultimo elemento da coluna)
        {
            if ((*it == *(it + N)) && (*it != 0))
            {
                *it = *it * 2;          
                *(it + N) = 0;          
                //it--;                   //  Pode ser ainda mais otimizado
            }
        }
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
                }
            }
        }
    }
    return vec;
}

vector<int> swipeDown(vector<int> vec, int N) { // Done
    vector<int>::iterator fim_coluna;
    bool flag;

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
                }
            }
        }
        for (vector<int>::iterator it = fim_coluna; it > fim_coluna - (N * (N - 1)); it -= N) //it varia do final da coluna até ao inicio da mesma (não chega ao ultimo elemento da coluna)
        {
            if ((*it == *(it - N)) && (*it != 0))
            {
                *it = *it * 2;
                *(it - N) = 0;
                //it--;                   //  Pode ser ainda mais otimizado
            }
        }
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
                }
            }
        }
    }
    return vec;
}

bool verificaVitoria(vector<int> tabuleiro, int N) {
    bool vitoria = false;
    for (int i = 0; i < N * N; i++) {
        if ((tabuleiro[i] != 0) && (vitoria == false))
            vitoria = true;
        else if ((tabuleiro[i] != 0) && (vitoria == true))
            return false;
        else
            continue;
    }
    return vitoria;
}

void imprimeTabuleiro(vector<int> tabuleiro, int N) {
    int paragrafo = 0;
    cout << "_______________________" << endl;
    for (int i = 0; i < N*N ; i++) {
        if (paragrafo == N) {
            paragrafo = 0;
            cout << endl;
        }
        paragrafo++;
        cout << tabuleiro[i] <<" ";
    }
    cout << endl <<"_______________________" << endl;
}

string jogo_2048(int M, int N, vector<int> vec) {

    // Creation of tree


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
    string tabuleiro_line;                          // Linha a ser lida
    size_t pos = 0;
    string delimiter = " ";

    int total;                                      // Numero de casos de teste
    cin >> total;

    int M;

    for (int i = 0; i < total ; i++) {              // Le e processa cada caso de teste
        cin >> N >> M;
        limiar = M + 1;
        cin.ignore();
        tabuleiro_2048.clear();
        for (int j = 0; j < N; j++) {
            getline(cin, tabuleiro_line);
            while ((pos = tabuleiro_line.find(delimiter)) != std::string::npos) {
                tabuleiro_2048.push_back(stoi(tabuleiro_line.substr(0, pos)));
                tabuleiro_line.erase(0, pos + delimiter.length());
            }
            tabuleiro_2048.push_back(stoi(tabuleiro_line));
        }


        solution.push_back(jogo_2048(M, N, tabuleiro_2048));


        //imprimeTabuleiro(tabuleiro_2048, N);
        //tabuleiro_2048 = swipeRight(tabuleiro_2048, N);
        //tabuleiro_2048 = swipeLeft(tabuleiro_2048, N);
        //tabuleiro_2048 = swipeUp(tabuleiro_2048, N);
        //tabuleiro_2048 = swipeDown(tabuleiro_2048, N);
        imprimeTabuleiro(tabuleiro_2048, N);
    }

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

}