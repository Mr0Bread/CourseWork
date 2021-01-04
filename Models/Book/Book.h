//
// Created by zimni on 12/24/2020.
//

#ifndef COURSEWORK_BOOK_H
#define COURSEWORK_BOOK_H
#pragma pack(push)
#pragma pack(1)

struct Book {
    int id;
    char title[50];
    int authorId;
    int yearOfRelease;
    char language[50];
    int pageQty;

    void printOut() {
        Output::print("ID: " + std::to_string(id));
        Output::print("Title: " + std::string(title));
        Output::print("Author ID: " + std::to_string(authorId));
        Output::print("Language: " + std::string(language));
        Output::print("Year of Release: " + std::to_string(yearOfRelease));
        Output::print("Page quantity: " +std::to_string(pageQty));
    }
};

#pragma pack(pop)
#endif //COURSEWORK_BOOK_H
