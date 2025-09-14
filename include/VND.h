#ifndef VND_H
#define VND_H

#include <vector>

class VND {
public:
    VND();
    ~VND();

    // Executa o algoritmo VND
    void run(std::vector<int>& solution);

private:
    // Aplica uma vizinhança específica
    void neighborhood1(std::vector<int>& solution);
    void neighborhood2(std::vector<int>& solution);
    void neighborhood3(std::vector<int>& solution);

    // Avalia a solução
    int evaluate(const std::vector<int>& solution);
};

#endif // VND_H