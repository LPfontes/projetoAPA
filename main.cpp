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
    
    // Exemplo de acesso direto usando os ponteiros retornados pelos getters
    if (dados.getN() > 1) {
        int** matriz_c = dados.getC();
        std::cout << "\nAcessando diretamente c[1][2]: " << matriz_c[1][2] << std::endl;
    }

    // Ao final da função main, a variável 'dados' sai de escopo
    // e o destrutor ~InputReader() é chamado AUTOMATICAMENTE,
    // liberando toda a memória que foi alocada.

    return 0;
}