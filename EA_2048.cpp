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


std::string jogo_2048() {

    return "?";
}

int main()
{
    // Ler de maneira eficiente
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    
    std::vector<std::vector<int>> tabuleiro_2048;   // Tabuleiro do jogo
    std::vector<std::string> sol;                   // Solucao

    int total;                                      // numero de casos de teste
    std::cin >> total;

    unsigned short int N, M;

    for (int i = 0; i < total ; i++) {              // Le e processa cada caso de teste
        std::cin >> N >> M;
        for (int j = 0; j < N; j++) {
                                                    // Le linha de jogo (que estruturas de dados vamos usar?, criar arrays (ficam na stack) ou vetores (heap e sao dinamicos))
        }
        sol.push_back(jogo_2048());
    }

    for (auto i : sol) {                            //Imprime output
        std::cout << i << std::endl;
    }

}