#include <iostream>
#include "minesweeper.h"

Minesweeper::Minesweeper(int rows, int cols) : n(rows), m(cols) {
    field = new char*[n];
    for (int i = 0; i < n; i++) {
        field[i] = new char[m];
        for (int j = 0; j < m; j++) {
            field[i][j] = '.';
        }
    }
}

Minesweeper::~Minesweeper() {
    for (int i = 0; i < n; i++) {
        delete[] field[i];
    }
    delete[] field;
}

void Minesweeper::setMine(int i, int j) {
    if (isValidPosition(i, j)) {
        field[i][j] = '*';
    }
}

void Minesweeper::setEmpty(int i, int j) {
    if (isValidPosition(i, j) && field[i][j] != '*') {
        field[i][j] = '.';
    }
}

int Minesweeper::countMinesAround(int i, int j) {
    int count = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;
            int ni = i + di;
            int nj = j + dj;
            if (isValidPosition(ni, nj) && field[ni][nj] == '*') {
                count++;
            }
        }
    }
    return count;
}

void Minesweeper::fillNumbers() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] != '*') {
                int mines = countMinesAround(i, j);
                if (mines > 0) {
                    field[i][j] = '0' + mines;
                }
            }
        }
    }
}

void Minesweeper::printField() {
    std::cout << "\nРезультат:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << field[i][j];
        }
        std::cout << std::endl;
    }
}

void Minesweeper::clearField() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            field[i][j] = '.';
        }
    }
}

bool Minesweeper::isValidPosition(int i, int j) {
    return (i >= 0 && i < n && j >= 0 && j < m);
}