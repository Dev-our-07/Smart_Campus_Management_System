#include "../include/Library.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "logger.h"

LibraryManager::LibraryManager(string file, string logFile) 
 
{
    filename = file;
    loadBooks();
   logger = Logger(logFile);
}

void LibraryManager::addBook()
{
    Book b;
    cout << "Enter Book ID: ";
    cin >> b.bookId;
    cout << "Enter Title: ";
    cin >> ws;
    getline(cin, b.title);
    cout << "Enter Author: ";
    getline(cin, b.author);
    cout << "Enter Copies: ";
    cin >> b.copies;

    books[b.bookId] = b;
    cout << "Book added successfully!\n";
    logger.log("INFO", "LibraryManager", "Added book: " + b.bookId);
    saveBooks();
}

void LibraryManager::issueBook()
{
    string bookId, studentId;
    cout << "Enter Book ID: ";
    cin >> bookId;
    cout << "Enter Student ID: ";
    cin >> studentId;

    if (books.find(bookId) == books.end())
    {
        cout << "Book not found!\n";
        return;
    }
    if (books[bookId].copies <= 0)
    {
        cout << "No copies available!\n";
        logger.log("WARNING", "LibraryManager", "Issue failed (no copies): " + bookId);
        return;
    }

    books[bookId].copies--;
    cout << "Book issued successfully!\n";
    logger.log("INFO", "LibraryManager", "Issued book: " + bookId + " to " + studentId);
    saveBooks();
}

void LibraryManager::returnBook()
{
    string bookId, studentId;
    cout << "Enter Book ID: ";
    cin >> bookId;
    cout << "Enter Student ID: ";
    cin >> studentId;

    if (books.find(bookId) == books.end())
    {
        cout << "Book not found!\n";
        return;
    }

    books[bookId].copies++;
    cout << "Book returned successfully!\n";
    logger.log("INFO", "LibraryManager", "Returned book: " + bookId + " from " + studentId);
    saveBooks();
}

void LibraryManager::viewBooks()
{
    if (books.empty())
    {
        cout << "No books available.\n";
        return;
    }
    for (auto &b : books)
    {
        cout << "Book ID: " << b.second.bookId
             << " | Title: " << b.second.title
             << " | Author: " << b.second.author
             << " | Copies: " << b.second.copies << endl;
    }
    logger.log("INFO", "LibraryManager", "Viewed all books");
}

void LibraryManager::saveBooks()
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cout << "Cannot open file!\n";
        return;
    }

    for (auto &b : books)
    {
        out << b.second.bookId << " " << b.second.title << " "
            << b.second.author << " " << b.second.copies << endl;
    }
    out.close();
}

void LibraryManager::loadBooks()
{
    ifstream in(filename);
    if (!in.is_open())
        return;

    books.clear();
    string bookId, title, author;
    int copies;
    while (in >> bookId >> ws && getline(in, title, ' ') && getline(in, author, ' ') && in >> copies)
    {
        Book b;
        b.bookId = bookId;
        b.title = title;
        b.author = author;
        b.copies = copies;
        books[bookId] = b;
    }
    in.close();
}
