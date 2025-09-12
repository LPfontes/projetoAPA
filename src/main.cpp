#include <istream>
#include <iostream>
#include <fstream>
#include "Instance.h"
#include "Solution.h"


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_do_arquivo>" << std::endl;
        return 1; // Retorna 1 para indicar erro
    }

    // Extrai o caminho do arquivo do segundo argumento (argv[1])
    std::string inputPath = argv[1];

    // Abrindo o arquivo de entrada
    std::ifstream arquivo(inputPath);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo entrada.txt" << std::endl;
        return 1;
    }

    // Cria a intancia
    Instance instance(arquivo);
    arquivo.close();

    // exibe a instancia
    instance.printData();

    //gera a solucao
    Solution solution(&instance);
    solution.bake();

    return 0;
}