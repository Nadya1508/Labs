#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>

using namespace std;

// Объединение для поля количества
union Quantity {
    int count;                 // количество как целое число
    char description[20];      // описание количества
};

// Структура для хранения информации о продукции
struct Product {
    char name[50];             // наименование продукции
    Quantity quantity;         // количество (union)
    bool isCount;              // флаг: true = count, false = description
    int workshop;              // номер цеха
};

void initializeData(Product*& products, int& capacity, int& size);
void addRecord(Product*& products, int& capacity, int& size);
void viewRecords(const Product* products, int size);
void deleteRecord(Product*& products, int& size, int index);
void editRecord(Product* products, int size, int index);
void loadFromFile(Product*& products, int& capacity, int& size, const char* filename);
void saveToFile(const Product* products, int size, const char* filename);
void editRecordInFile(const char* filename, int recordIndex);
void workshopStatistics(const Product* products, int size);
void showMenu();
void clearInputBuffer();
void printProduct(const Product& p, int index);
void printStatistics(const char names[][50], const int counts[], int size);

#endif