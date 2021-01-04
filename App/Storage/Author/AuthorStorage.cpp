//
// Created by zimni on 12/25/2020.
//

#include <algorithm>
#include "AuthorStorage.h"

void AuthorStorage::init() {
    std::remove(AUTHORS_FILE_NAME);
    std::fstream fileToWorkWith;
    fileToWorkWith.open(AUTHORS_FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!fileToWorkWith) {
        fileToWorkWith.open(AUTHORS_FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::trunc);
    }

    fileToWorkWith.close();
}

std::vector<Author> AuthorStorage::loadAll() {
    int qtyOfAuthorsInFile = getQtyOfAuthorsInFile();
    std::vector<Author> booksVector;

    if (qtyOfAuthorsInFile == 0) {
        return booksVector;
    }

    std::ifstream booksFile(AUTHORS_FILE_NAME, std::ios::binary);
    auto authors = new Author[qtyOfAuthorsInFile];

    for (int i = 0; i < qtyOfAuthorsInFile; ++i) {
        booksFile.read((char *) &authors[i], getSizeOfAuthorStruct());
        booksVector.push_back(authors[i]);
    }

    delete[] authors;
    booksFile.close();
    return booksVector;
}

int AuthorStorage::getSizeOfAuthorStruct() {
    return sizeof(Author);
}

int AuthorStorage::getAuthorsFileSize() {
    std::ifstream authorsFile(AUTHORS_FILE_NAME, std::ios::binary);
    authorsFile.seekg(0, std::ios::end);
    int size = authorsFile.tellg();
    authorsFile.close();
    return size;
}

int AuthorStorage::getQtyOfAuthorsInFile() {
    int booksFileSize = getAuthorsFileSize();

    if (booksFileSize == -1) {
        return 0;
    }

    return booksFileSize/getSizeOfAuthorStruct();
}

void AuthorStorage::add(Author author) {
    auto authors = loadAll();
    author.id = counter;
    counter++;
    authors.push_back(author);

    saveToStorage(authors);
}

void AuthorStorage::saveToStorage(std::vector<Author> authors) {
    auto authorsQty = authors.size();
    auto authorsArray = new Author[authorsQty];

    for (int i = 0; i < authorsQty; ++i) {
        authorsArray[i] = authors[i];
    }

    std::remove(AUTHORS_FILE_NAME);
    std::ofstream authorsFile(AUTHORS_FILE_NAME, std::ios::out | std::ios::binary);

    for (int i = 0; i < authorsQty; ++i) {
        authorsFile.write((char *) &authorsArray[i], getSizeOfAuthorStruct());
    }

    delete[] authorsArray;
    authorsFile.close();
}

void AuthorStorage::remove(int id) {
    idToUse = id;
    auto authors = loadAll();
    auto foundAuthorPos = std::find_if(authors.begin(), authors.end(), doesMatch);
    auto distance = std::distance(authors.begin(), foundAuthorPos);

    if (foundAuthorPos != authors.end()) {
        authors.erase(authors.begin() + distance);
        std::cout << "Record with ID " << idToUse << " has been deleted" << std::endl;
    } else {
        std::cout << "There is no record with provided ID" << std::endl;
    }

    saveToStorage(authors);
}

bool AuthorStorage::doesMatch(Author author) {
    return author.id == idToUse;
}

void AuthorStorage::findById(int id) {
    auto authors = loadAll();
    bool found = false;

    for (auto& author : authors) {
        if (author.id == id) {
            found = true;
            author.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

void AuthorStorage::findByName(const std::string& name) {
    auto authors = loadAll();
    bool found = false;

    for (auto& author : authors) {
        if (std::string(author.name) == name) {
            found = true;
            author.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

void AuthorStorage::findBySurname(const std::string& surname) {
    auto authors = loadAll();
    bool found = false;

    for (auto& author : authors) {
        if (std::string(author.surname) == surname) {
            found = true;
            author.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

void AuthorStorage::findByYoBExactly(int yearOfBirth) {
    auto authors = loadAll();
    bool found = false;

    for (auto& author : authors) {
        if (author.yearOfBirth == yearOfBirth) {
            found = true;
            author.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

void AuthorStorage::findByYoBAfter(int yearOfBirth) {
    auto authors = loadAll();
    bool found = false;

    for (auto& author : authors) {
        if (author.yearOfBirth > yearOfBirth) {
            found = true;
            author.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

void AuthorStorage::findByYoBBefore(int yearOfBirth) {
    auto authors = loadAll();
    bool found = false;

    for (auto& author : authors) {
        if (author.yearOfBirth < yearOfBirth) {
            found = true;
            author.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

void AuthorStorage::findByPlaceOfBirth(const std::string& placeOfBirth) {
    auto authors = loadAll();
    bool found = false;

    for (auto& author : authors) {
        if (std::string(author.placeOfBirth) == placeOfBirth) {
            found = true;
            author.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

int AuthorStorage::getCounter() {
    return counter;
}

void AuthorStorage::save(Author author) {
    auto authors = loadAll();

    for (auto& existingAuthor : authors) {
        if (author.id == existingAuthor.id) {
            existingAuthor.yearOfBirth = author.yearOfBirth;

            for (int i = 0; i < sizeof(existingAuthor.name); ++i) {
                existingAuthor.name[i] = author.name[i];
                existingAuthor.surname[i] = author.surname[i];
                existingAuthor.placeOfBirth[i] = author.placeOfBirth[i];
            }

            break;
        }
    }

    saveToStorage(authors);
    Output::print("Author saved");
}

Author AuthorStorage::loadById(int id) {
    auto authors = loadAll();
    Author authorToReturn{};

    for (auto& author : authors) {
        if (author.id == id) {
            authorToReturn = author;
            break;
        }
    }

    return authorToReturn;
}
