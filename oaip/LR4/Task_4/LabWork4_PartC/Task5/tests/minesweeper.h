#ifndef MINESWEEPER_H
#define MINESWEEPER_H

class Minesweeper {
private:
    int n, m;
    char** field;

public:
    Minesweeper(int rows, int cols);
    ~Minesweeper();
    
    void setMine(int i, int j);
    void setEmpty(int i, int j);
    int countMinesAround(int i, int j);
    void fillNumbers();
    void printField();
    void clearField();
    bool isValidPosition(int i, int j);
};

#endif