#include <iostream>

using namespace std;

class Minesweeper {
private:
    int n, m;
    char** field;

    bool isValidPosition(int i, int j) {
        return (i >= 0 && i < n && j >= 0 && j < m);
    }

    void clearInputBuffer() {
        int c;
        while ((c = cin.get()) != '\n' && c != EOF) {}
    }

public:
    Minesweeper(int rows, int cols) : n(rows), m(cols) {
        field = new char*[n];
        for (int i = 0; i < n; i++) {
            field[i] = new char[m];
            for (int j = 0; j < m; j++) {
                field[i][j] = '.';
            }
        }
    }

    ~Minesweeper() {
        for (int i = 0; i < n; i++) {
            delete[] field[i];
        }
        delete[] field;
    }

    void setMine(int i, int j) {
        if (isValidPosition(i, j)) {
            field[i][j] = '*';
        }
    }

    void setEmpty(int i, int j) {
        if (isValidPosition(i, j) && field[i][j] != '*') {
            field[i][j] = '.';
        }
    }

    int countMinesAround(int i, int j) {
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

    void printField() {
        cout << "\nРезультат:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << field[i][j];
            }
            cout << endl;
        }
    }

    void clearField() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                field[i][j] = '.';
            }
        }
    }

    void inputField() {
        cout << "Введите поле (" << n << " строк по " << m << " символов):\n";
        cout << "'.' - пустая клетка, '*' - мина\n";
        
        for (int i = 0; i < n; i++) {
            string line;
            bool validInput = false;
            
            while (!validInput) {
                cout << "Строка " << (i + 1) << ": ";
                cin >> line;
                
                if (cin.fail()) {
                    cin.clear();
                    clearInputBuffer();
                    cout << "Ошибка ввода! Попробуйте снова.\n";
                    continue;
                }
                
                if (line.length() != m) {
                    cout << "Ошибка: строка должна содержать ровно " << m << " символов!\n";
                    cout << "Вы ввели: " << line.length() << " символов.\n";
                    continue;
                }
                
                validInput = true;
                for (int j = 0; j < m; j++) {
                    if (line[j] == '*') {
                        setMine(i, j);
                    } else if (line[j] == '.') {
                        setEmpty(i, j);
                    } else {
                        cout << "Ошибка: недопустимый символ '" << line[j] << "'! Используйте только '.' и '*'\n";
                        validInput = false;
                        break;
                    }
                }
            }
        }
    }
};

void showContextMenu() {
    cout << "\n=== КОНТЕКСТНОЕ МЕНЮ ===" << endl;
    cout << "Задание: Игра 'Сапёр'" << endl;
    cout << "Суть: Преобразовать поле с минами в поле с числами," << endl;
    cout << "      указывающими количество мин в соседних клетках" << endl;
    cout << "Выполнила: Седельник Надежда" << endl;
    cout << "========================" << endl << endl;
}

int getValidatedInput(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            int c;
            while ((c = cin.get()) != '\n' && c != EOF) {}
            cout << "Ошибка: введите целое число!\n";
            continue;
        }
        
        int c;
        while ((c = cin.get()) != '\n') {
            if (c != ' ' && c != '\t') {
                cout << "Ошибка: введите только число без лишних символов!\n";
                while ((c = cin.get()) != '\n' && c != EOF) {}
                value = minVal - 1;
                break;
            }
        }
        
        if (value < minVal || value > maxVal) {
            cout << "Ошибка: введите число от " << minVal << " до " << maxVal << "!\n";
        } else {
            return value;
        }
    }
}

char getValidatedCharInput(const string& prompt, const string& validChars) {
    char choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            int c;
            while ((c = cin.get()) != '\n' && c != EOF) {}
            cout << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }
        
        int c;
        while ((c = cin.get()) != '\n' && c != EOF) {}
        
        bool isValid = false;
        for (size_t i = 0; i < validChars.length(); i++) {
            if (choice == validChars[i]) {
                isValid = true;
                break;
            }
        }
        
        if (isValid) {
            return choice;
        } else {
            cout << "Ошибка: допустимые символы - ";
            for (size_t i = 0; i < validChars.length(); i++) {
                cout << "'" << validChars[i] << "'";
                if (i < validChars.length() - 1) cout << ", ";
            }
            cout << "\n";
        }
    }
}

void demonstrateErrorHandling() {
    cout << "\n--- Демонстрация обработки ошибок ---" << endl;
    cout << "Программа обрабатывает следующие ошибки ввода:" << endl;
    cout << "1. Нечисловой ввод для размеров поля" << endl;
    cout << "2. Числа вне допустимого диапазона" << endl;
    cout << "3. Лишние символы после числа" << endl;
    cout << "4. Неправильная длина строк поля" << endl;
    cout << "5. Недопустимые символы в поле" << endl;
    cout << "6. Ошибочный ввод для подтверждения повтора" << endl;
    cout << "-------------------------------------" << endl;
}

int main() {
    showContextMenu();
    demonstrateErrorHandling();
    
    char choice;
    do {
        cout << "\n=== ГЕНЕРАТОР ПОЛЯ ДЛЯ САПЁРА ===" << endl;
        
        int n = getValidatedInput("Введите количество строк (1-20): ", 1, 20);
        int m = getValidatedInput("Введите количество столбцов (1-20): ", 1, 20);
        
        Minesweeper game(n, m);
        game.inputField();
        game.fillNumbers();
        game.printField();
        
        choice = getValidatedCharInput("\nХотите создать новое поле? (y/n): ", "yYnN");
        
    } while (choice == 'y' || choice == 'Y');
    
    cout << "\nЗавершение работы прораммы." << endl;
    return 0;
}