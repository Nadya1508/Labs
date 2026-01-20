#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

class MagicSquare {
private:
    int** square;
    int size;
    
    void createOddMagicSquare();
    void createDoublyEvenMagicSquare();
    void createSinglyEvenMagicSquare();
    
public:
    MagicSquare(int n);
    ~MagicSquare();
    bool isMagicSquare() const;
    void printSquare() const;
    int getMagicSum() const;
    int getSize() const { return size; }
};

// Функции для работы с меню и вводом
void showContextMenu();
void showInstructions();
int getValidatedInput(const char* prompt, int minVal, int maxVal);
void clearInputBuffer();
void printMainMenu();

#endif