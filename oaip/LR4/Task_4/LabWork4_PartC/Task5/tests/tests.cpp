#include <gtest/gtest.h>

class TestMinesweeper {
private:
    int n, m;
    char** field;

public:
    TestMinesweeper(int rows, int cols) : n(rows), m(cols) {
        field = new char*[n];
        for (int i = 0; i < n; i++) {
            field[i] = new char[m];
            for (int j = 0; j < m; j++) {
                field[i][j] = '.';
            }
        }
    }

    ~TestMinesweeper() {
        for (int i = 0; i < n; i++) {
            delete[] field[i];
        }
        delete[] field;
    }

    void setMine(int i, int j) {
        if (i >= 0 && i < n && j >= 0 && j < m) {
            field[i][j] = '*';
        }
    }

    char getCell(int i, int j) {
        if (i >= 0 && i < n && j >= 0 && j < m) {
            return field[i][j];
        }
        return '\0';
    }

    int countMinesAround(int i, int j) {
        int count = 0;
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di == 0 && dj == 0) continue;
                int ni = i + di;
                int nj = j + dj;
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && field[ni][nj] == '*') {
                    count++;
                }
            }
        }
        return count;
    }

    void fillNumbers() {
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
};

TEST(MinesweeperTest, NoMines) {
    TestMinesweeper game(3, 3);
    game.fillNumbers();
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(game.getCell(i, j), '.');
        }
    }
}

TEST(MinesweeperTest, SingleMine) {
    TestMinesweeper game(3, 3);
    game.setMine(1, 1);
    game.fillNumbers();
    
    EXPECT_EQ(game.getCell(0, 0), '1');
    EXPECT_EQ(game.getCell(0, 1), '1');
    EXPECT_EQ(game.getCell(0, 2), '1');
    EXPECT_EQ(game.getCell(1, 0), '1');
    EXPECT_EQ(game.getCell(1, 1), '*');
    EXPECT_EQ(game.getCell(1, 2), '1');
    EXPECT_EQ(game.getCell(2, 0), '1');
    EXPECT_EQ(game.getCell(2, 1), '1');
    EXPECT_EQ(game.getCell(2, 2), '1');
}

TEST(MinesweeperTest, MultipleMines) {
    TestMinesweeper game(3, 3);
    game.setMine(0, 0);
    game.setMine(2, 2);
    game.fillNumbers();
    
    EXPECT_EQ(game.getCell(0, 0), '*');
    EXPECT_EQ(game.getCell(0, 1), '1');
    EXPECT_EQ(game.getCell(1, 0), '1');
    EXPECT_EQ(game.getCell(1, 1), '2');
    EXPECT_EQ(game.getCell(2, 2), '*');
}

TEST(MinesweeperTest, MineInCorner) {
    TestMinesweeper game(2, 2);
    game.setMine(0, 0);
    game.fillNumbers();
    
    EXPECT_EQ(game.getCell(0, 0), '*');
    EXPECT_EQ(game.getCell(0, 1), '1');
    EXPECT_EQ(game.getCell(1, 0), '1');
    EXPECT_EQ(game.getCell(1, 1), '1');
}

TEST(MinesweeperTest, AllMines) {
    TestMinesweeper game(2, 2);
    game.setMine(0, 0);
    game.setMine(0, 1);
    game.setMine(1, 0);
    game.setMine(1, 1);
    game.fillNumbers();
    
    EXPECT_EQ(game.getCell(0, 0), '*');
    EXPECT_EQ(game.getCell(0, 1), '*');
    EXPECT_EQ(game.getCell(1, 0), '*');
    EXPECT_EQ(game.getCell(1, 1), '*');
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}