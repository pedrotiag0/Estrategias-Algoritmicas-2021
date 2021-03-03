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

vector<int> swipeRight(vector<int> vec, int N) {
    vector<int>::iterator inicio_linha;
    bool flag;

    for (int i = 0; i < N; i++) //Avança a linha do tabuleiro
    {
        inicio_linha = vec.begin() + (i * N);
        for (vector<int>::iterator it = inicio_linha + N - 1; it != inicio_linha; it--) //it varia do fim da linha até ao index 1 (não chega ao 1º elemento da linha)
        {
            if ((*it == *(it - 1)) && (*it != 0))
            {
                *it = *it * 2;          //[0][0][2][2] -> [0][0][2][4]           [2][2][0][4] -> [2][4][0][4]
                *(it - 1) = 0;          //[0][0][2][4] -> [0][0][0][4]           [2][4][0][4] -> [0][4][0][4]
                it--;
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
                    *it = *(it - 1);                                                //[4][0][0][4] -> [4][4][0][4]
                    *(it - 1) = 0;                                                  //[4][4][0][4] -> [0][4][0][4]
                    flag = true;
                }
            }
        }
    }
    return vec;
}

void imprimeTabuleiro(vector<int> tabuleiro, int N) {
    int paragrafo = 0;
    cout << "_______________________" << endl;
    for (int i = 0; i < N*N ; i++) {
        if (paragrafo == N) {
            paragrafo = 0;
            cout << endl;
        }
        cout << tabuleiro[i] <<" ";
    }
    cout << endl <<"_______________________" << endl;
}

string jogo_2048() {

    return "?";
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

    unsigned short int N = 0, M;

    for (int i = 0; i < total ; i++) {              // Le e processa cada caso de teste
        cout << "Nova leitura!" << endl;
        cin >> N >> M;
        cin.ignore();
        tabuleiro_2048.clear();
        for (int j = 0; j < N; j++) {
            getline(cin, tabuleiro_line);
            while ((pos = tabuleiro_line.find(delimiter)) != std::string::npos) {
                tabuleiro_2048.push_back(stoi(tabuleiro_line.substr(0, pos)));
                tabuleiro_line.erase(0, pos + delimiter.length());
            }
            tabuleiro_2048.push_back(stoi(tabuleiro_line));
            // Le linha de jogo (que estruturas de dados vamos usar?, criar arrays (ficam na stack) ou vetores (heap e sao dinamicos))
        }
        //solution.push_back(jogo_2048());
        imprimeTabuleiro(tabuleiro_2048, N);
    }

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

}