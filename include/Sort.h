#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>
#include "Node.h" 

class Sorter {
public:
    // Opção 1: Ordena a matriz original 'in-place'.
    void sortInPlace(node** costMatrix, int matrixSize);

    // Opção 2: Retorna uma cópia ordenada da matriz.
    node** sortByCopy(node** costMatrix, int matrixSize);
};

#endif // SORT_H