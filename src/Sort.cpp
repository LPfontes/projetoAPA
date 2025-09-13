#include "../include/Sort.h"

// ordenação sem copia.
void Sorter::sortInPlace(node** costMatrix, int matrixSize) {
    for (int i = 0; i < matrixSize; ++i) {
        std::sort(costMatrix[i] + 1, costMatrix[i] + matrixSize, [](const node& a, const node& b) {
            return a.cost < b.cost;
        });
    }
}

// ordenação que retorna uma cópia.
node** Sorter::sortByCopy(node** costMatrix, int matrixSize) {

    node** sortedMatrix = new node*[matrixSize];
    for (int i = 0; i < matrixSize; ++i) {
        sortedMatrix[i] = new node[matrixSize];
    }

    // Copia os dados da matriz original para a nova matriz.
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            sortedMatrix[i][j] = costMatrix[i][j];
        }
    }

    // Ordena cada linha da matriz copiada.
    for (int i = 0; i < matrixSize; ++i) {
        std::sort(sortedMatrix[i] + 1, sortedMatrix[i] + matrixSize, [](const node& a, const node& b) {
            return a.cost < b.cost;
        });
    }

    // Retorna a nova matriz ordenada.
    return sortedMatrix;
}