//
// Created by zimni on 12/25/2020.
//

#pragma once
#ifndef COURSEWORK_AUTHORSTORAGE_H
#define COURSEWORK_AUTHORSTORAGE_H

#include "../../../Models/Author/Author.cpp"
#include <vector>
#include <fstream>

#define AUTHORS_FILE_NAME "authors.dat"

class AuthorStorage {
private:
    static int counter;
    static int idToUse;

    static bool doesMatch(Author author);

public:
    static void init();

    static int getCounter();

    static std::vector<Author> loadAll();

    static void add(Author author);

    static void saveToStorage(std::vector<Author> authors);

    static void remove(int id);

    static int getSizeOfAuthorStruct();

    static int getAuthorsFileSize();

    static int getQtyOfAuthorsInFile();

    static void findById(int id);

    static void findByName(const std::string& name);

    static void findBySurname(const std::string& surname);

    static void findByYoBExactly(int yearOfBirth);

    static void findByYoBAfter(int yearOfBirth);

    static void findByYoBBefore(int yearOfBirth);

    static void findByPlaceOfBirth(const std::string& placeOfBirth);

    static void save(Author author);

    static Author loadById(int id);
};


#endif //COURSEWORK_AUTHORSTORAGE_H
