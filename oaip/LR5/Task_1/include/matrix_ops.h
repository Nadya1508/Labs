#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

class MatrixOperations {
private:
    double** matrixC;
    double** matrixD;
    int size;

    void allocateMemory();
    void freeMemory();
    void calculateMatrixC();
    void calculateMatrixD();

public:
    MatrixOperations(int k);
    ~MatrixOperations();


    double sumMainDiagonalC() const;
    double sumSecondaryDiagonalC() const;
    double sumMainDiagonalD() const;
    double sumSecondaryDiagonalD() const;
    void printResults() const;
    int getSize() const { return size; }
    double getMatrixCValue(int i, int j) const;
    double getMatrixDValue(int i, int j) const;
    
    static bool isValidSize(int size);
};

void showContextMenu();
void showInstructions();
int getValidatedInput();
bool askToContinue();
void printMainMenu();

#endif