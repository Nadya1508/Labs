#include "book.h"

void copyStr(char* dest, const char* src, int max) {
    int i = 0;
    while (i < max - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int strLen(const char* str) {
    int l = 0;
    while (str[l] != '\0') {
        l++;
    }
    return l;
}

bool strEq(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i++;
    }
    return s1[i] == '\0' && s2[i] == '\0';
}

void getLastName(const char* author, char* lastName) {
    int i = 0;
    while (author[i] != '\0' && author[i] != ' ') {
        lastName[i] = author[i];
        i++;
    }
    lastName[i] = '\0';
}

int getIntInput(const char* prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите целое число.\n";
        } else if (value < min || value > max) {
            cout << "Ошибка! Число должно быть от " << min << " до " << max << ".\n";
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

void getDateInput(Date& date) {
    date.day = getIntInput("День: ", 1, 31);
    date.month = getIntInput("Месяц: ", 1, 12);
    date.year = getIntInput("Год: ", 0, 2100);
}

Publisher getPubChoice() {
    int c; 
    cout << "\nИздательство: 1.Эксмо 2.АСТ 3.Проспект 4.Наука 5.Другое\n";
    c = getIntInput("Выбор: ", 1, 5);
    return c==1 ? PUB_EKSMO : c==2 ? PUB_AST : c==3 ? PUB_PROSPEKT : c==4 ? PUB_NAUKA : PUB_UNKNOWN;
}

const char* pubToStr(Publisher p) {
    const char* names[] = {"Другое","Эксмо","АСТ","Проспект","Наука"};
    return names[p];
}

// 1. Функция формирования массива (3 способа ввода)
BookArray createBooks(int& size) {
    cout << "\n=== СОЗДАНИЕ КАТАЛОГА ===\n";
    cout << "Способ: 1.Заданное количество 2.До признака 3.С подтверждением\n";
    int mode = getIntInput("Выбор: ", 1, 3);
    
    BookArray books = new Book[100];
    size = 0;
    int targetSize = 100; 
    
    if (mode == 1) {
        targetSize = getIntInput("Сколько книг? ", 1, 100);
    }
    
    do {
        cout << "\n=== Книга " << size + 1 << " ===\n";
        
        cout << "Тип номера: 1.Числовой 2.Буквенный\n";  
        int t = getIntInput("Выбор: ", 1, 2);  
        books[size].isNumReg = (t == 1);
        
        if (t == 1) { 
            books[size].reg.numeric = getIntInput("Числовой номер: ", 0, 1000000);
        } else {  
            cout << "Буквенный номер: "; 
            cin >> books[size].reg.alpha;
            cin.ignore(10000, '\n');
        }
        
        cout << "Автор (Фамилия Имя): "; 
        char auth[100]; 
        cin.getline(auth, 100);
        copyStr(books[size].author, auth, 50);
        
        if (mode == 2 && strEq(auth, "СТОП")) {
            cout << "Ввод завершен по признаку 'СТОП'\n";
            break;
        }
        
        cout << "Название: "; 
        char title[150]; 
        cin.getline(title, 150);
        copyStr(books[size].title, title, 100);
        
        books[size].year = getIntInput("Год издания: ", 0, 2100);
        
        if (mode == 2 && books[size].year == 0) {
            cout << "Ввод завершен по признаку 'год издания = 0'\n";
            break;
        }
        
        books[size].publisher = getPubChoice();
        
        books[size].pages = getIntInput("Количество страниц: ", 1, 5000);
        
        cout << "Дата поступления:\n";
        getDateInput(books[size].date);
        
        // Автоматическое определение доступности 
        books[size].available = (books[size].year > 2000 && books[size].pages < 500);
        cout << "Статус: " << (books[size].available ? "доступна" : "недоступна") 
             << " (определено автоматически)\n";
        
        size++;
        
        if (mode == 3 && size < 100) {
            cout << "Добавить еще одну книгу? (y/n): "; 
            char answer;
            cin >> answer;
            cin.ignore(10000, '\n');
            
            if (answer != 'y' && answer != 'Y') {
                break;
            }
        }
        
    } while ((mode == 1 && size < targetSize) || mode == 2 || mode == 3);
    
    BookArray result = new Book[size];
    for (int i = 0; i < size; i++) {
        result[i] = books[i];
    }
    delete[] books;
    
    cout << "\nКаталог создан. Всего книг: " << size << endl;
    return result;
}

// 2. Функция просмотра
void showBooks(BookArray books, int size) {
    if (!books || size == 0) { 
        cout << "Каталог книг пуст.\n"; 
        return; 
    }
    
    cout << "\n=== КАТАЛОГ КНИГ (" << size << " книг) ===\n";
    for (int i = 0; i < size; i++) {
        cout << "\n" << i + 1 << ". ";
        
        if (books[i].isNumReg) {
            cout << "[№" << books[i].reg.numeric << "] ";
        } else {
            cout << "[" << books[i].reg.alpha << "] ";
        }
        
        cout << books[i].author << " \"" << books[i].title << "\" (" 
             << books[i].year << ") " << pubToStr(books[i].publisher)
             << ", " << books[i].pages << " стр., "
             << books[i].date.day << "." << books[i].date.month << "." << books[i].date.year
             << ", " << (books[i].available ? "Доступна" : "Недоступна") << endl;
    }
}

// 3. Функция дополнения
void addBooks(BookArray& books, int& size, int count) {
    if (count <= 0) {
        cout << "Ошибка: количество должно быть больше 0.\n";
        return;
    }
    
    BookArray newBooks = new Book[size + count];
    for (int i = 0; i < size; i++) {
        newBooks[i] = books[i];
    }
    
    for (int i = 0; i < count; i++) {
        cout << "\n=== Новая книга " << i + 1 << " из " << count << " ===\n";
        
        cout << "Тип номера: 1.Числовой 2.Буквенный\n";
        int t = getIntInput("Выбор: ", 1, 2);
        newBooks[size + i].isNumReg = (t == 1);
        
        if (t == 1) { 
            newBooks[size + i].reg.numeric = getIntInput("Числовой номер: ", 0, 1000000);
        } else { 
            cout << "Буквенный номер: "; 
            cin >> newBooks[size + i].reg.alpha;
            cin.ignore(10000, '\n');
        }
        
        cout << "Автор (Фамилия Имя): "; 
        char auth[100]; 
        cin.getline(auth, 100);
        copyStr(newBooks[size + i].author, auth, 50);
        
        cout << "Название: "; 
        char title[150]; 
        cin.getline(title, 150);
        copyStr(newBooks[size + i].title, title, 100);
        
        newBooks[size + i].year = getIntInput("Год издания: ", 0, 2100);
        newBooks[size + i].publisher = getPubChoice();
        newBooks[size + i].pages = getIntInput("Количество страниц: ", 1, 5000);
        
        cout << "Дата поступления:\n";
        getDateInput(newBooks[size + i].date);
        
        newBooks[size + i].available = (newBooks[size + i].year > 2000);
    }
    
    delete[] books;
    books = newBooks;
    size += count;
    cout << "\nДобавлено " << count << " книг. Всего в каталоге: " << size << endl;
}

// 4. Функция поиска
void findBooksAfterYear(BookArray books, int size, int year) {
    if (!books || size == 0) { 
        cout << "Каталог книг пуст.\n"; 
        return; 
    }
    
    BookArray found = new Book[size];
    int foundCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (books[i].year > year) {
            found[foundCount] = books[i];
            foundCount++;
        }
    }
    
    if (foundCount == 0) {
        cout << "\nКниг, изданных после " << year << " года, не найдено.\n";
        delete[] found;
        return;
    }
    
    // Сортировка Шелла по году 
    for (int gap = foundCount / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < foundCount; i++) {
            Book temp = found[i];
            int j = i;
            while (j >= gap && found[j - gap].year > temp.year) {
                found[j] = found[j - gap];
                j -= gap;
            }
            found[j] = temp;
        }
    }
    
    cout << "\n=== КНИГИ, ИЗДАННЫЕ ПОСЛЕ " << year << " ГОДА ===\n";
    cout << "(показаны только фамилии авторов, отсортировано по году)\n\n";
    for (int i = 0; i < foundCount; i++) {
        char lastName[50];
        getLastName(found[i].author, lastName);
        cout << i + 1 << ". " << lastName << " - \"" 
             << found[i].title << "\" (" << found[i].year << "), "
             << found[i].pages << " стр., "
             << pubToStr(found[i].publisher) << ", "
             << (found[i].available ? "Доступна" : "Недоступна") << "\n";
    }
    cout << "\nВсего найдено: " << foundCount << " книг\n";
    
    delete[] found;
}

// 5. Функция удаления
void deleteBook(BookArray& books, int& size) {
    if (!books || size == 0) { 
        cout << "Каталог книг пуст.\n"; 
        return; 
    }
    
    cout << "\n=== УДАЛЕНИЕ КНИГИ ===\n";
    cout << "Тип номера: 1.Числовой 2.Буквенный\n";
    int t = getIntInput("Выбор: ", 1, 2);
    
    if (t == 1) {
        int num = getIntInput("Числовой номер: ", 0, 1000000);
        
        for (int i = 0; i < size; i++) {
            if (books[i].isNumReg && books[i].reg.numeric == num) {
                cout << "Найдена книга: \"" << books[i].title 
                     << "\" (" << books[i].author << ")\n";
                
                cout << "Вы уверены, что хотите удалить? (y/n): ";
                char confirm;
                cin >> confirm;
                cin.ignore(10000, '\n');
                
                if (confirm == 'y' || confirm == 'Y') {
                    for (int j = i; j < size - 1; j++) {
                        books[j] = books[j + 1];
                    }
                    size--;
                    cout << "Книга удалена.\n";
                } else {
                    cout << "Удаление отменено.\n";
                }
                return;
            }
        }
    } else {
        char str[15]; 
        cout << "Буквенный номер: "; 
        cin >> str;
        cin.ignore(10000, '\n');
        
        for (int i = 0; i < size; i++) {
            if (!books[i].isNumReg && strEq(books[i].reg.alpha, str)) {
                cout << "Найдена книга: \"" << books[i].title 
                     << "\" (" << books[i].author << ")\n";
                
                cout << "Вы уверены, что хотите удалить? (y/n): ";
                char confirm;
                cin >> confirm;
                cin.ignore(10000, '\n');
                
                if (confirm == 'y' || confirm == 'Y') {
                    for (int j = i; j < size - 1; j++) {
                        books[j] = books[j + 1];
                    }
                    size--;
                    cout << "Книга удалена.\n";
                } else {
                    cout << "Удаление отменено.\n";
                }
                return;
            }
        }
    }
    cout << "Книга с указанным номером не найдена.\n";
}

// 6. Функция изменения
void editBook(BookArray books, int size) {
    if (!books || size == 0) { 
        cout << "Каталог книг пуст.\n"; 
        return; 
    }
    
    cout << "\n=== РЕДАКТИРОВАНИЕ КНИГИ ===\n";
    cout << "Тип номера: 1.Числовой 2.Буквенный\n";
    int t = getIntInput("Выбор: ", 1, 2);
    int idx = -1;
    
    if (t == 1) {
        int num = getIntInput("Числовой номер: ", 0, 1000000);
        
        for (int i = 0; i < size; i++) {
            if (books[i].isNumReg && books[i].reg.numeric == num) {
                idx = i;
                break;
            }
        }
    } else {
        char str[15]; 
        cout << "Буквенный номер: "; 
        cin >> str;
        cin.ignore(10000, '\n');
        
        for (int i = 0; i < size; i++) {
            if (!books[i].isNumReg && strEq(books[i].reg.alpha, str)) {
                idx = i;
                break;
            }
        }
    }
    
    if (idx == -1) { 
        cout << "Книга с указанным номером не найдена.\n"; 
        return; 
    }
    
    cout << "\nРедактирование книги: \"" << books[idx].title << "\"\n";
    cout << "Текущий автор: " << books[idx].author << "\n";
    cout << "Новый автор (оставьте пустым чтобы не менять): "; 
    char auth[100]; 
    cin.getline(auth, 100);
    
    if (auth[0] != '\0') {
        copyStr(books[idx].author, auth, 50);
    }
    
    cout << "Текущее название: " << books[idx].title << "\n";
    cout << "Новое название (оставьте пустым чтобы не менять): "; 
    char title[150]; 
    cin.getline(title, 150);
    
    if (title[0] != '\0') {
        copyStr(books[idx].title, title, 100);
    }
    
    cout << "Текущий год: " << books[idx].year << "\n";
    int y = getIntInput("Новый год (0 чтобы не менять): ", 0, 2100);
    
    if (y > 0) {
        books[idx].year = y;
        books[idx].available = (y > 2000 && books[idx].pages < 500);
    }
    
    cout << "Книга успешно изменена.\n";
}

// 7. Функция упорядочения (сортировка Шелла)
void sortBooks(BookArray books, int size) {
    if (!books || size < 2) { 
        cout << "Недостаточно книг для сортировки.\n"; 
        return; 
    }
    
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            Book temp = books[i];
            int j = i;
            while (j >= gap && books[j - gap].year > temp.year) {
                books[j] = books[j - gap];
                j -= gap;
            }
            books[j] = temp;
        }
    }
    cout << "Книги отсортированы по году издания (сортировка Шелла).\n";
}

// 8. Сохранение в ДВОИЧНЫЙ файл 
void saveToFile(BookArray books, int size, const char* filename) {
    if (!books || size == 0) { 
        cout << "Каталог пуст, нечего сохранять.\n"; 
        return; 
    }
    
    ofstream f(filename, ios::binary);  // ДВОИЧНЫЙ РЕЖИМ
    if (!f) { 
        cout << "Ошибка создания файла.\n"; 
        return; 
    }
    
    // Сохраняем в ДВОИЧНОМ формате
    f.write((char*)&size, sizeof(int));
    f.write((char*)books, sizeof(Book) * size);
    
    f.close();
    cout << "Каталог сохранен в ДВОИЧНЫЙ файл: " << filename 
         << " (" << size << " книг)\n";
}

// 9. Загрузка из ДВОИЧНОГО файла
BookArray loadFromFile(int& size, const char* filename) {
    ifstream f(filename, ios::binary);  // ДВОИЧНЫЙ РЕЖИМ
    if (!f) { 
        cout << "Ошибка открытия файла.\n"; 
        return 0; 
    }
    
    f.read((char*)&size, sizeof(int));
    
    if (size <= 0 || size > 1000) {
        cout << "Некорректный размер данных в файле.\n";
        f.close();
        return 0;
    }
    
    BookArray books = new Book[size];
    f.read((char*)books, sizeof(Book) * size);
    
    f.close();
    cout << "Загружено " << size << " книг из ДВОИЧНОГО файла: " << filename << "\n";
    return books;
}

//Обновление БЕЗ полной перезаписи файла
bool updateInFile(const char* filename, int idx, const Book& book) {
    fstream f(filename, ios::binary | ios::in | ios::out);
    if (!f) {
        cout << "Ошибка открытия файла.\n";
        return false;
    }
    
    int sz;
    f.read((char*)&sz, sizeof(int));
    
    if (idx < 0 || idx >= sz) {
        cout << "Неверный индекс записи. Допустимый диапазон: 0-" << sz-1 << "\n";
        f.close();
        return false;
    }
    
    //Перемещаемся к нужной записи и перезаписываем ТОЛЬКО ЕЕ
    f.seekp(sizeof(int) + idx * sizeof(Book), ios::beg);
    f.write((char*)&book, sizeof(Book));
    
    f.close();
    cout << "Запись #" << idx << " обновлена БЕЗ полной перезаписи файла\n";
    return true;
}

// Функция для просмотра двоичного файла в читаемом виде
void viewBinaryFile(const char* filename) {
    ifstream f(filename, ios::binary);
    if (!f) {
        cout << "Ошибка открытия файла.\n";
        return;
    }
    
    int size;
    f.read((char*)&size, sizeof(int));
    
    cout << "\n=== ПРОСМОТР ДВОИЧНОГО ФАЙЛА ===" << endl;
    cout << "Файл: " << filename << endl;
    cout << "Количество записей: " << size << endl;
    cout << "=================================" << endl;
    
    for (int i = 0; i < size; i++) {
        Book book;
        f.read((char*)&book, sizeof(Book));
        
        cout << "\n--- Запись #" << (i+1) << " ---" << endl;
        cout << "Тип номера: " << (book.isNumReg ? "числовой" : "буквенный") << endl;
        cout << "Номер: ";
        if (book.isNumReg) {
            cout << book.reg.numeric;
        } else {
            cout << book.reg.alpha;
        }
        cout << endl;
        cout << "Автор: " << book.author << endl;
        cout << "Название: " << book.title << endl;
        cout << "Год: " << book.year << endl;
        cout << "Издательство: " << pubToStr(book.publisher) << endl;
        cout << "Страниц: " << book.pages << endl;
        cout << "Дата: " << book.date.day << "." 
             << book.date.month << "." << book.date.year << endl;
        cout << "Доступность: " << (book.available ? "да" : "нет") << endl;
    }
    
    f.close();
}