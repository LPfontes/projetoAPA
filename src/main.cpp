#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "../include/Instance.h"
#include "../include/Solution.h"

int main(int argc, char *argv[])
{

    // Extrai o caminho do arquivo do segundo argumento (argv[1])
    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    // Abrindo o arquivo de entrada
    std::ifstream arquivo(inputPath);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo entrada.txt" << std::endl;
        return 1;
    }

    // Criar arquivo de saída específico para cada instância
    std::ofstream out(outputPath);
    if (!out.is_open())
    {
        std::cerr << "Erro ao criar arquivo de saída" << std::endl;
        return 1;
    }

    // Redireciona std::cout para o arquivo temporariamente
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    // Cria a intancia
    Instance instance(arquivo);
    arquivo.close();

    // exibe a instancia
    // instance.printData();

    // gera a solucao
    Solution solution(&instance);
    solution.bake();

    // Restaura cout para o console
    std::cout.rdbuf(coutbuf);

    return 0;
    
}
