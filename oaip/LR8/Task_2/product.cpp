#include "product.h"

void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n') continue;
}

void initializeData(Product*& products, int& capacity, int& size) {
    if (products != nullptr) {
        delete[] products;
    }
    capacity = 5;
    size = 0;
    products = new Product[capacity];
    cout << "Динамический массив инициализирован.\n";
}

// Увеличение массива при необходимости
void resizeArray(Product*& products, int& capacity, int newCapacity) {
    Product* newProducts = new Product[newCapacity];
    for (int i = 0; i < capacity; i++) {
        newProducts[i] = products[i];
    }
    delete[] products;
    products = newProducts;
    capacity = newCapacity;
}

// Добавление записи
void addRecord(Product*& products, int& capacity, int& size) {
    if (size >= capacity) {
        resizeArray(products, capacity, capacity * 2);
    }
    
    cout << "\n=== ДОБАВЛЕНИЕ НОВОЙ ЗАПИСИ ===\n";
    cout << "Наименование продукции: ";
    clearInputBuffer();
    cin.getline(products[size].name, 50);
    
    cout << "Номер цеха: ";
    while (!(cin >> products[size].workshop) || products[size].workshop <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        clearInputBuffer();
    }
    
    cout << "Введите количество как число (1) или описание (2): ";
    char choice;
    while (!(cin >> choice) || (choice != '1' && choice != '2')) {
        cout << "Ошибка! Введите 1 или 2: ";
        clearInputBuffer();
    }
    
    if (choice == '1') {
        products[size].isCount = true;
        cout << "Количество: ";
        while (!(cin >> products[size].quantity.count) || products[size].quantity.count < 0) {
            cout << "Ошибка! Введите неотрицательное число: ";
            clearInputBuffer();
        }
    } else {
        products[size].isCount = false;
        cout << "Описание количества: ";
        clearInputBuffer();
        cin.getline(products[size].quantity.description, 20);
    }
    
    size++;
    cout << "Запись добавлена успешно!\n";
}

// Вывод одной записи
void printProduct(const Product& p, int index) {
    cout << "  " << index + 1;
    if (index + 1 < 10) cout << " "; 
    
    cout << "     " << p.name;
    int nameLen = 0;
    while (p.name[nameLen] != '\0' && nameLen < 50) nameLen++;
    
    if (nameLen < 16) cout << "\t\t";
    else if (nameLen < 24) cout << "\t";
    
    // Количество
    if (p.isCount) {
        cout << p.quantity.count << " шт.";
    } else {
        cout << p.quantity.description;
    }
    
    if (p.isCount && p.quantity.count < 1000) cout << "\t";
    cout << "\t\t";
    
    cout << "Цех №" << p.workshop << endl;
}

void viewRecords(const Product* products, int size) {
    if (size == 0) {
        cout << "Нет записей для отображения.\n";
        return;
    }
    
    cout << "\n=== СПИСОК ВСЕЙ ПРОДУКЦИИ (" << size << " записей) ===\n";
    cout << "----------------------------------------------------------------\n";
    cout << "№    Наименование\t\t\tКоличество\t\tЦех\n";
    cout << "----------------------------------------------------------------\n";
    
    for (int i = 0; i < size; i++) {
        printProduct(products[i], i);
    }
    cout << "----------------------------------------------------------------\n";
}

void deleteRecord(Product*& products, int& size, int index) {
    if (index < 0 || index >= size) {
        cout << "Неверный индекс!\n";
        return;
    }
    
    for (int i = index; i < size - 1; i++) {
        products[i] = products[i + 1];
    }
    
    size--;
    cout << "Запись удалена успешно!\n";
}

void editRecord(Product* products, int size, int index) {
    if (index < 0 || index >= size) {
        cout << "Неверный индекс!\n";
        return;
    }
    
    cout << "\n=== РЕДАКТИРОВАНИЕ ЗАПИСИ №" << index + 1 << " ===\n";
    cout << "Текущие данные:\n";
    printProduct(products[index], index);
    cout << "\nВведите новые данные:\n";
    
    clearInputBuffer();
    cout << "Наименование (Enter - оставить без изменений): ";
    char input[50];
    cin.getline(input, 50);
    if (input[0] != '\0') {
        for (int i = 0; i < 50; i++) {
            products[index].name[i] = input[i];
            if (input[i] == '\0') break;
        }
    }
    
    cout << "Номер цеха (0 - оставить без изменений): ";
    int newWorkshop;
    cin >> newWorkshop;
    if (newWorkshop != 0) {
        products[index].workshop = newWorkshop;
    }
    
    cout << "Изменить количество? (1 - да, 0 - нет): ";
    int changeQty;
    cin >> changeQty;
    
    if (changeQty == 1) {
        cout << "Ввести как число (1) или описание (2)? ";
        char choice;
        cin >> choice;
        
        if (choice == '1') {
            products[index].isCount = true;
            cout << "Введите количество: ";
            cin >> products[index].quantity.count;
        } else {
            products[index].isCount = false;
            cout << "Введите описание: ";
            clearInputBuffer();
            cin.getline(products[index].quantity.description, 20);
        }
    }
    
    cout << "Запись откорректирована успешно!\n";
}

// Загрузка данных из файла
void loadFromFile(Product*& products, int& capacity, int& size, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл не найден. Будет создан новый при сохранении.\n";
        return;
    }
    
    // Освобождаем старые данные
    if (products != nullptr) {
        delete[] products;
    }
    
    // Читаем количество записей
    int fileSize;
    file >> fileSize;
    file.ignore();
    
    capacity = fileSize + 5;
    products = new Product[capacity];
    size = 0;
    
    for (int i = 0; i < fileSize; i++) {
        file.getline(products[size].name, 50);
        file >> products[size].workshop;
        
        int type;
        file >> type;
        products[size].isCount = (type == 1);
        
        if (products[size].isCount) {
            file >> products[size].quantity.count;
        } else {
            file.ignore();
            file.getline(products[size].quantity.description, 20);
        }
        
        file.ignore();
        size++;
    }
    
    file.close();
    cout << "Данные загружены из файла. Записей: " << size << "\n";
}

// Сохранение данных в файл
void saveToFile(const Product* products, int size, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка создания файла!\n";
        return;
    }
    
    file << size << endl;
    
    for (int i = 0; i < size; i++) {
        file << products[i].name << endl;
        file << products[i].workshop << endl;
        file << (products[i].isCount ? 1 : 2) << endl;
        
        if (products[i].isCount) {
            file << products[i].quantity.count;
        } else {
            file << products[i].quantity.description;
        }
        
        if (i < size - 1) {
            file << endl;
        }
    }
    
    file.close();
    cout << "Данные сохранены в файл. Записей: " << size << "\n";
}

// Корректировка записи внутри текстового файла
void editRecordInFile(const char* filename, int recordIndex) {
    Product* tempProducts = nullptr;
    int tempCapacity = 0;
    int tempSize = 0;
    
    loadFromFile(tempProducts, tempCapacity, tempSize, filename);
    
    if (tempSize == 0) {
        cout << "В файле нет записей.\n";
        return;
    }
    
    if (recordIndex < 1 || recordIndex > tempSize) {
        cout << "Неверный номер записи! Допустимые значения: 1-" << tempSize << "\n";
        if (tempProducts != nullptr) delete[] tempProducts;
        return;
    }
    
    cout << "\n=== РЕДАКТИРОВАНИЕ ЗАПИСИ В ФАЙЛЕ ===\n";
    editRecord(tempProducts, tempSize, recordIndex - 1);
    saveToFile(tempProducts, tempSize, filename);
    
    delete[] tempProducts;
    cout << "Запись в файле успешно откорректирована!\n";
}

void printStatistics(const char names[][50], const int counts[], int size) {
    cout << "----------------------------------------------------------------\n";
    cout << "Наименование\t\t\t\tКоличество\n";
    cout << "----------------------------------------------------------------\n";
    
    for (int i = 0; i < size; i++) {
        cout << names[i];
        
        int nameLen = 0;
        while (names[i][nameLen] != '\0' && nameLen < 50) nameLen++;
        
        if (nameLen < 8) cout << "\t\t\t\t";
        else if (nameLen < 16) cout << "\t\t\t";
        else if (nameLen < 24) cout << "\t\t";
        else cout << "\t";
        
        cout << counts[i] << " шт.\n";
    }
    cout << "----------------------------------------------------------------\n";
}

void workshopStatistics(const Product* products, int size) {
    if (size == 0) {
        cout << "Нет данных для анализа.\n";
        return;
    }
    
    int targetWorkshop;
    cout << "Введите номер цеха для анализа: ";
    cin >> targetWorkshop;
    
    const int MAX_NAMES = 100;
    char productNames[MAX_NAMES][50];
    int productQuantities[MAX_NAMES] = {0};
    int foundCount = 0;
    
    // Сбор статистики
    for (int i = 0; i < size; i++) {
        if (products[i].workshop == targetWorkshop) {
            bool found = false;
            
            // Поиск существующего наименования
            for (int j = 0; j < foundCount; j++) {
                bool equal = true;
                for (int k = 0; k < 50; k++) {
                    if (productNames[j][k] != products[i].name[k]) {
                        equal = false;
                        break;
                    }
                    if (products[i].name[k] == '\0') break;
                }
                
                if (equal) {
                    if (products[i].isCount) {
                        productQuantities[j] += products[i].quantity.count;
                    } else {
                        productQuantities[j] += 1;
                    }
                    found = true;
                    break;
                }
            }
            
            // Добавление нового наименования
            if (!found && foundCount < MAX_NAMES) {
                int k = 0;
                while (products[i].name[k] != '\0' && k < 49) {
                    productNames[foundCount][k] = products[i].name[k];
                    k++;
                }
                productNames[foundCount][k] = '\0';
                
                if (products[i].isCount) {
                    productQuantities[foundCount] = products[i].quantity.count;
                } else {
                    productQuantities[foundCount] = 1;
                }
                foundCount++;
            }
        }
    }
    
    if (foundCount == 0) {
        cout << "Для цеха №" << targetWorkshop << " нет данных о выпуске продукции.\n";
        return;
    }
    
    // Сортировка по убыванию количества (пузырьковая сортировка)
    for (int i = 0; i < foundCount - 1; i++) {
        for (int j = 0; j < foundCount - i - 1; j++) {
            if (productQuantities[j] < productQuantities[j + 1]) {
                // Обмен количествами
                int tempQty = productQuantities[j];
                productQuantities[j] = productQuantities[j + 1];
                productQuantities[j + 1] = tempQty;
                
                // Обмен наименованиями
                for (int k = 0; k < 50; k++) {
                    char temp = productNames[j][k];
                    productNames[j][k] = productNames[j + 1][k];
                    productNames[j + 1][k] = temp;
                }
            }
        }
    }
    
    cout << "\n=== СТАТИСТИКА ДЛЯ ЦЕХА №" << targetWorkshop << " ===\n";
    cout << "Количество выпущенных изделий по наименованиям\n";
    cout << "в порядке убывания количества:\n";
    printStatistics(productNames, productQuantities, foundCount);
    cout << "Всего наименований: " << foundCount << "\n";
}

void showMenu() {
    cout << "\n=========== УЧЕТ ПРОДУКЦИИ ЗАВОДА ===========\n";
    cout << "1. Просмотр всех записей\n";
    cout << "2. Добавить запись\n";
    cout << "3. Удалить запись\n";
    cout << "4. Редактировать запись\n";
    cout << "5. Инициализировать данные (очистить все)\n";
    cout << "6. Загрузить данные из файла\n";
    cout << "7. Сохранить данные в файл\n";
    cout << "8. Редактировать запись в файле\n";
    cout << "9. Статистика по цеху\n";
    cout << "0. Выход\n";
    cout << "============================================\n";
    cout << "Выберите действие: ";
}