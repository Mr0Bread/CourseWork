//
// Created by zimni on 12/24/2020.
//

#ifndef COURSEWORK_AUTHOR_H
#define COURSEWORK_AUTHOR_H
#pragma pack(push)
#pragma pack(1)

struct Author {
    int id;
    char name[50];
    char surname[50];
    int yearOfBirth;
    char placeOfBirth[50];

    void printOut() {
        Output::print("ID: " + std::to_string(id));
        Output::print("Name: " + std::string(name));
        Output::print("Surname: " + std::string(surname));
        Output::print("Year of birth: " + std::to_string(yearOfBirth));
        Output::print("Place of Birth: " + std::string(placeOfBirth));
    }
};

#pragma pack(pop)
#endif //COURSEWORK_AUTHOR_H
