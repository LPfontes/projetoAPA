#include <istream>
#include <iostream>
#include <fstream>
#include "InputReader.h"
int main() {

    // Abrindo o arquivo de entrada
    std::ifstream arquivo("teste.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo entrada.txt" << std::endl;
        return 1;
    }

    // Cria o objeto. O construtor lê os dados e aloca a memória.
    InputReader dados(arquivo);
    arquivo.close();

    // Usa os dados através dos getters
    std::cout << "Dados lidos do arquivo usando a classe com ponteiros:" << std::endl;
    dados.printData();
    

    return 0;
}