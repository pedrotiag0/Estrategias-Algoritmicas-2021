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

vector<int> swipeLeft() {

}


string jogo_2048() {

    return "?";
}

int main()
{
    // Ler de maneira eficiente
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    vector<int> tabuleiro_2048;             // Tabuleiro do jogo
    vector<string> solution;                        // Solucao

    int total;                                      // numero de casos de teste
    cin >> total;

    unsigned short int N, M;

    for (int i = 0; i < total ; i++) {              // Le e processa cada caso de teste
        cin >> N >> M;
        for (int j = 0; j < N; j++) {
                                                    // Le linha de jogo (que estruturas de dados vamos usar?, criar arrays (ficam na stack) ou vetores (heap e sao dinamicos))
        }
        solution.push_back(jogo_2048());
    }

    for (auto i : solution) {                        //Imprime output
        cout << i << endl;
    }

}