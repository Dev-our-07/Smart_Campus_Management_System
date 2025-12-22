#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Logger.h"
using namespace std;

struct Book
{
    string bookId;
    string title;
    string author;
    int copies;
};

class LibraryManager
{
private:
    map<string, Book> books;
    string filename;
    Logger logger;

public:
    LibraryManager(string file = "books.txt", string logFile = "transaction.log");

    void addBook();
    void issueBook();
    void returnBook();
    void viewBooks();
    void saveBooks();
    void loadBooks();
    void issueBook();
    void returnBook();
};

#endif
