#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>

using namespace std;

enum Publisher { 
    PUB_UNKNOWN,    
    PUB_EKSMO,      
    PUB_AST,        
    PUB_PROSPEKT,   
    PUB_NAUKA       
};

struct Date { 
    int day; 
    int month; 
    int year; 
};

struct Book {
    union {                         
        int numeric;                // числовой номер
        char alpha[15];             // буквенный номер
    } reg;                          
    bool isNumReg;                  
    char author[50];                
    char title[100];                
    int year;                       
    Publisher publisher;            
    int pages;                      
    Date date;                      
    bool available;                 
};

typedef Book* BookArray;            

BookArray createBooks(int& size);
void showBooks(BookArray books, int size);
void addBooks(BookArray& books, int& size, int count);
void findBooksAfterYear(BookArray books, int size, int year);
void deleteBook(BookArray& books, int& size);
void editBook(BookArray books, int size);
void sortBooks(BookArray books, int size);

// Файловые операции (ДВОИЧНЫЕ)
void saveToFile(BookArray books, int size, const char* filename);
BookArray loadFromFile(int& size, const char* filename);
bool updateInFile(const char* filename, int idx, const Book& book);
void viewBinaryFile(const char* filename);  // для просмотра двоичного файла

Publisher getPubChoice();
const char* pubToStr(Publisher p);
void copyStr(char* dest, const char* src, int max);
int strLen(const char* str);
bool strEq(const char* s1, const char* s2);
void getLastName(const char* author, char* lastName);
int getIntInput(const char* prompt, int min = -2147483647, int max = 2147483647);
void getDateInput(Date& date);

#endif