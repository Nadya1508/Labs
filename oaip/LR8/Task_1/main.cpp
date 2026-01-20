#include "book.h"

int main() {
    BookArray books = 0;
    int size = 0;
    
    while (true) {
        cout << "\n=== БИБЛИОТЕЧНЫЙ КАТАЛОГ ===\n"
             << "1. Создать новый каталог\n"
             << "2. Показать все книги\n"
             << "3. Добавить новые книги\n"
             << "4. Найти книги после заданного года\n"
             << "5. Удалить книгу\n"
             << "6. Изменить книгу\n"
             << "7. Сортировать книги по году\n"
             << "8. Сохранить каталог в двоичный файл\n"
             << "9. Загрузить каталог из двоичного файла\n"
             << "10. Просмотреть двоичный файл\n"
             << "11. Обновить запись в двоичном файле (без полной перезаписи)\n"
             << "0. Выход из программы\n";
        
        int choice = getIntInput("Выбор: ", 0, 11);
        
        switch (choice) {
            case 1: {
                if (books) {
                    cout << "Текущий каталог будет удален. Продолжить? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    cin.ignore(10000, '\n');
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        delete[] books;
                        books = 0;
                        books = createBooks(size);
                    }
                } else {
                    books = createBooks(size);
                }
                break;
            }
                
            case 2: {
                showBooks(books, size);
                break;
            }
                
            case 3: {
                if (!books) { 
                    cout << "Ошибка: сначала создайте каталог.\n"; 
                    break; 
                }
                int c = getIntInput("Сколько книг добавить? ", 1, 100);
                addBooks(books, size, c);
                break;
            }
                
            case 4: {
                if (!books || size == 0) { 
                    cout << "Ошибка: каталог пуст.\n"; 
                    break; 
                }
                int y = getIntInput("Введите год: ", 0, 2100);
                findBooksAfterYear(books, size, y);
                break;
            }
                
            case 5: {
                if (!books || size == 0) { 
                    cout << "Ошибка: каталог пуст.\n"; 
                    break; 
                }
                deleteBook(books, size);
                break;
            }
                
            case 6: {
                if (!books || size == 0) { 
                    cout << "Ошибка: каталог пуст.\n"; 
                    break; 
                }
                editBook(books, size);
                break;
            }
                
            case 7: {
                if (!books || size < 2) { 
                    cout << "Ошибка: недостаточно книг для сортировки.\n"; 
                    break; 
                }
                sortBooks(books, size);
                cout << "\nРезультат сортировки:\n";
                showBooks(books, size);
                break;
            }
                
            case 8: {
                if (!books || size == 0) { 
                    cout << "Ошибка: каталог пуст.\n"; 
                    break; 
                }
                char fn1[50]; 
                cout << "Имя двоичного файла (.dat): "; 
                cin >> fn1;
                cin.ignore(10000, '\n');
                saveToFile(books, size, fn1);
                break;
            }
                
            case 9: {
                char fn2[50]; 
                cout << "Имя двоичного файла: "; 
                cin >> fn2;
                cin.ignore(10000, '\n');
                
                if (books) {
                    cout << "Текущий каталог будет удален. Продолжить? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    cin.ignore(10000, '\n');
                    
                    if (confirm != 'y' && confirm != 'Y') {
                        break;
                    }
                    delete[] books;
                }
                books = loadFromFile(size, fn2);
                break;
            }
                
            case 10: {
                char fn3[50];
                cout << "Имя двоичного файла для просмотра: ";
                cin >> fn3;
                cin.ignore(10000, '\n');
                viewBinaryFile(fn3);
                break;
            }
                
            case 11: {
                if (!books || size == 0) { 
                    cout << "Ошибка: каталог пуст.\n"; 
                    break; 
                }
                char fn4[50]; 
                cout << "Имя двоичного файла: "; 
                cin >> fn4;
                cin.ignore(10000, '\n');
                
                cout << "Индекс записи (0-" << (size-1) << "): ";
                int idx = getIntInput("", 0, size-1);
                
                if (updateInFile(fn4, idx, books[idx])) {
                    cout << "Запись успешно обновлена в файле БЕЗ полной перезаписи.\n";
                }
                break;
            }
                
            case 0: {
                if (books) {
                    delete[] books;
                }
                cout << "Программа завершена.\n";
                return 0;
            }
                
            default: {
                cout << "Неверный выбор.\n";
                break;
            }
        }
    }
}