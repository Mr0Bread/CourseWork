//
// Created by zimni on 12/25/2020.
//

#include "BookStorage.h"

void BookStorage::init() {
    std::remove(BOOK_FILE_NAME);
    std::fstream fileToWorkWith;
    fileToWorkWith.open(BOOK_FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!fileToWorkWith) {
        fileToWorkWith.open(BOOK_FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::trunc);
    }

    fileToWorkWith.close();
}

std::vector<Book> BookStorage::loadAll() {
    int qtyOfBooksInFile = getQtyOfBooksInFile();
    std::vector<Book> booksVector;

    if (qtyOfBooksInFile == 0) {
        return booksVector;
    }

    std::ifstream booksFile(BOOK_FILE_NAME, std::ios::binary);
    auto books = new Book[qtyOfBooksInFile];

    for (int i = 0; i < qtyOfBooksInFile; ++i) {
        booksFile.read((char *) &books[i], getSizeOfBookStruct());
        booksVector.push_back(books[i]);
    }

    delete[] books;
    booksFile.close();
    return booksVector;
}

void BookStorage::add(Book book) {
    auto books = loadAll();
    book.id = counter;
    counter++;
    books.push_back(book);

    saveToStorage(books);
}

int BookStorage::getSizeOfBookStruct() {
    return sizeof(Book);
}

int BookStorage::getBooksFileSize() {
    std::ifstream booksFile(BOOK_FILE_NAME, std::ios::binary);
    booksFile.seekg(0, std::ios::end);
    int size = booksFile.tellg();
    booksFile.close();
    return size;
}

void BookStorage::remove(int id) {
    idToUse = id;
    auto books = loadAll();
    auto foundBookPos = std::find_if(books.begin(), books.end(), doesMatch);
    auto distance = std::distance(books.begin(), foundBookPos);

    if (foundBookPos != books.end()) {
        books.erase(books.begin() + distance);
        std::cout << "Record with ID " << idToUse << " has been deleted" << std::endl;
    } else {
        std::cout << "There is no record with provided ID" << std::endl;
    }

    saveToStorage(books);
}

int BookStorage::getQtyOfBooksInFile() {
    int sizeOfBookStruct = getSizeOfBookStruct();
    int booksFileSize = getBooksFileSize();

    if (booksFileSize == -1) {
        return 0;
    }

    return booksFileSize/sizeOfBookStruct;
}

void BookStorage::saveToStorage(std::vector<Book> books) {
    auto booksQty = books.size();
    auto bookArray = new Book[booksQty];

    for (int i = 0; i < booksQty; ++i) {
        bookArray[i] = books[i];
    }

    std::remove(BOOK_FILE_NAME);
    std::ofstream booksFile(BOOK_FILE_NAME, std::ios::out | std::ios::binary);

    for (int i = 0; i < booksQty; ++i) {
        booksFile.write((char *) &bookArray[i], getSizeOfBookStruct());
    }

    delete[] bookArray;
    booksFile.close();
}

bool BookStorage::doesMatch(Book book) {
    return book.id == idToUse;
}

void BookStorage::findById(int id, std::function<bool(Book, int)> func) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (func(book, id)) {
            found = true;
            book.printOut();
            Output::print();
            break;
        }
    }

    if (!found) {
        Output::print("No record found");
    }

    std::cout << "\n\n";
}

void BookStorage::findByTitle(const std::string& title) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (std::string(book.title) == title) {
            book.printOut();
            Output::print();
            found = true;
        }
    }

    if (!found) {
        Output::print("No records found");
    }

    Output::print("\n");
}

void BookStorage::findByAuthorId(int authorId) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (book.authorId == authorId) {
            book.printOut();
            Output::print();
            found = true;
        }
    }

    if (!found) {
        Output::print("No records found");
    }

    Output::print("\n");
}

void BookStorage::findReleasedExactly(int yearOfRelease) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (book.yearOfRelease == yearOfRelease) {
            found = true;
            book.printOut();
            Output::print();
        }
    }

    if (!found) {
        Output::print("No records found");
    }
}

void BookStorage::findReleasedAfter(int yearOfRelease) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (book.yearOfRelease > yearOfRelease) {
            found = true;
            book.printOut();
            Output::print();
        }
    }

    if (!found) {
        Output::print("No records found");
    }
}

void BookStorage::findReleasedBefore(int yearOfRelease) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (book.yearOfRelease < yearOfRelease) {
            found = true;
            book.printOut();
            Output::print();
        }
    }

    if (!found) {
        Output::print("No records found");
    }
}

void BookStorage::findByLanguage(const std::string& language) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (std::string(book.language) == language) {
            found = true;
            book.printOut();
            Output::print();
        }
    }

    if (!found) {
        Output::print("No records found");
    }
}

void BookStorage::findByPagesExactly(int pageQty) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (book.pageQty == pageQty) {
            found = true;
            book.printOut();
            Output::print();
        }
    }

    if (!found) {
        Output::print("No records found");
    }
}

void BookStorage::findByPagesMoreThan(int pageQty) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (book.pageQty > pageQty) {
            found = true;
            book.printOut();
            Output::print();
        }
    }

    if (!found) {
        Output::print("No records found");
    }
}

void BookStorage::findByPagesLessThan(int pageQty) {
    auto books = loadAll();
    bool found = false;

    for (auto& book : books) {
        if (book.pageQty < pageQty) {
            found = true;
            book.printOut();
            Output::print();
        }
    }

    if (!found) {
        Output::print("No records found");
    }
}
