#include "product.h"

int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8");

    const char* filename = "products.txt";
    Product* products = nullptr;
    int capacity = 0;
    int size = 0;
    int choice;
    
    initializeData(products, capacity, size);
    
    cout << "============================================\n";
    cout << "   ПРОГРАММА УЧЕТА ПРОДУКЦИИ ЗАВОДА\n";
    cout << "  Используется динамический массив структур\n";
    cout << "============================================\n";
    
    do {
        showMenu();
        if (!(cin >> choice)) {
            cout << "Ошибка ввода!\n";
            clearInputBuffer();
            continue;
        }
        
        switch (choice) {
            case 1:
                viewRecords(products, size);
                break;
                
            case 2:
                addRecord(products, capacity, size);
                break;
                
            case 3:
                if (size > 0) {
                    viewRecords(products, size);
                    cout << "Введите номер записи для удаления (1-" << size << "): ";
                    int index;
                    cin >> index;
                    if (index >= 1 && index <= size) {
                        deleteRecord(products, size, index - 1);
                    } else {
                        cout << "Неверный номер записи!\n";
                    }
                } else {
                    cout << "Нет записей для удаления.\n";
                }
                break;
                
            case 4:
                if (size > 0) {
                    viewRecords(products, size);
                    cout << "Введите номер записи для редактирования (1-" << size << "): ";
                    int index;
                    cin >> index;
                    if (index >= 1 && index <= size) {
                        editRecord(products, size, index - 1);
                    } else {
                        cout << "Неверный номер записи!\n";
                    }
                } else {
                    cout << "Нет записей для редактирования.\n";
                }
                break;
                
            case 5:
                initializeData(products, capacity, size);
                cout << "Все данные очищены. Массив переинициализирован.\n";
                break;
                
            case 6:
                loadFromFile(products, capacity, size, filename);
                break;
                
            case 7:
                saveToFile(products, size, filename);
                break;
                
            case 8:
                if (size > 0) {
                    cout << "Введите номер записи для редактирования в файле: ";
                    int recordNum;
                    cin >> recordNum;
                    editRecordInFile(filename, recordNum);
                } else {
                    cout << "Сначала загрузите данные из файла.\n";
                }
                break;
                
            case 9:
                workshopStatistics(products, size);
                break;
                
            case 0:
                cout << "Выход из программы...\n";
                break;
                
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
                break;
        }
        
        clearInputBuffer();
        
    } while (choice != 0);
    
    if (products != nullptr) {
        delete[] products;
    }
    
    cout << "Программа завершена.\n";
    return 0;
}