#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "../include/Instance.h"
#include "../include/Solution.h"



int main(int argc, char* argv[]) {

    if (argc < 2) {
        
        std::vector<int> solucoes = {
            15700, 
            14600, 
            16900, 
            13500, 
            12600,
            31443,
            29259,
            91619, 
            76999, 
            31100, 
            30300, 
            59493, 
            57476,
            120277, 
            65669, 
            48829, 
            39979, 
            388680, 
            157115,
        };

        std::vector<std::string> instancias_teste = {
            "n12_q20",
            "n12_q30",
            "n13_q30",
            "n14_q12",
            "n14_q30",
            "n17_q10",
            "n17_q20",
            "n20_q20",
            "n20_q30",
            "n26_q20",
            "n26_q30",
            "n40_q20",
            "n40_q30",
            "n54_q30",
            "n58_q30",
            "n74_q20",            
            "n79_q30",            
            "n81_q10",
            "n115_q20", 
        };
        

        for (size_t i = 0; i < solucoes.size(); i++) {

            std::cout << "\n-----------------------   " << instancias_teste[i] << " -------------------------------\n "  << std::endl;

            // Abrindo o arquivo de entrada
            std::ifstream arquivo("./input/" + instancias_teste[i] + ".txt");
            if (!arquivo.is_open()) {
                std::cerr << "Erro ao abrir o arquivo entrada.txt" << std::endl;
                return 1;
            }

            // Cria a intancia
            Instance instance(arquivo);
            arquivo.close();

            // exibe a instancia
            //instance.printData();

            //gera a solucao
            Solution solution(&instance);
            solution.GAP(solucoes[i]);
            
        }

        return 0;
        
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
    //instance.printData();

    //gera a solucao
    Solution solution(&instance);
    solution.bake();

    return 0;
}


