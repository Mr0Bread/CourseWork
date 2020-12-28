//
// Created by zimni on 12/25/2020.
//

#pragma once
#ifndef COURSEWORK_BOOKSTORAGE_H
#define COURSEWORK_BOOKSTORAGE_H

#include "../../../Models/Book/Book.cpp"
#include <vector>
#include <fstream>
#include <functional>

#define BOOK_FILE_NAME "books.dat"

class BookStorage {
private:
    static int counter;
    static int idToUse;
public:
    static void init();

    static std::vector<Book> loadAll();

    static void add(Book book);

    static void saveToStorage(std::vector<Book> books);

    static void remove(int id);

    static int getSizeOfBookStruct();

    static int getBooksFileSize();

    static int getQtyOfBooksInFile();

    static bool doesMatch(Book book);

    static void findById(int id, std::function<bool(Book, int)> func);

    static void findByTitle(const std::string& title);

    static void findByAuthorId(int authorId);

    static void findReleasedExactly(int yearOfRelease);

    static void findReleasedAfter(int yearOfRelease);

    static void findReleasedBefore(int yearOfRelease);

    static void findByLanguage(const std::string& language);

    static void findByPagesExactly(int pageQty);

    static void findByPagesMoreThan(int pageQty);

    static void findByPagesLessThan(int pageQty);
};


#endif //COURSEWORK_BOOKSTORAGE_H
