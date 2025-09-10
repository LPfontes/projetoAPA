#include <istream>
#include <iostream>
#include <fstream>
#include "LowerCost.h"


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

    // Cria o objeto. O construtor lê os dados e aloca a memória.
    InputReader dados(arquivo);
    arquivo.close();

    // Usa os dados através dos getters
    std::cout << "Dados lidos do arquivo usando a classe com ponteiros:" << std::endl;
    dados.printData();
    LowerCost alg(dados.getVehicles(),dados.getStations(),dados.getVehicleCapacity());
    dados.getCostMatrix();
    alg.Solution(dados.getCostMatrix());

    return 0;
}