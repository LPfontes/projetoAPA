#include <iostream>
#include <istream>

class InputReader {
private:
    int n;
    int m;
    int Q;

    int* d; // Ponteiro para o array d
    int** c; // Ponteiro para ponteiros para a matriz c

public:
    InputReader(std::istream& fileInput) : n(0), m(0), Q(0), d(nullptr), c(nullptr) {

        fileInput >> this->n >> this->m >> this->Q;
        
    
        if (this->n <= 0) {
            return;
        }

        
        this->d = new int[this->n];
        for (int i = 0; i < this->n; ++i) {
            fileInput >> this->d[i];
        }

        
        int matrix_size = this->n + 1;
        this->c = new int*[matrix_size];
        
        
        for (int i = 0; i < matrix_size; ++i) {
            this->c[i] = new int[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                fileInput >> this->c[i][j];
            }
        }
    }

    ~InputReader() {
        
        delete[] d;

        
        if (c != nullptr) {
            int matrix_size = this->n + 1;
            
            for (int i = 0; i < matrix_size; ++i) {
                delete[] c[i];
            }
            
            delete[] c;
        }
    }

    
    int getN() const { return n; }
    int getM() const { return m; }
    int getQ() const { return Q; }
    int* getD() const { return d; }
    int** getC() const { return c; }

    void printData() const {
        std::cout << "n: " << n << std::endl;
        std::cout << "m: " << m << std::endl;
        std::cout << "Q: " << Q << std::endl;

        if (d != nullptr) {
            std::cout << "\nArray d:" << std::endl;
            for (int i = 0; i < n; ++i) {
                std::cout << d[i] << " ";
            }
            std::cout << std::endl;
        }

        if (c != nullptr) {
            std::cout << "\nMatriz c:" << std::endl;
            int matrix_size = n + 1;
            for (int i = 0; i < matrix_size; ++i) {
                for (int j = 0; j < matrix_size; ++j) {
                    std::cout << c[i][j] << "\t";
                }
                std::cout << std::endl;
            }
        }
    }
};