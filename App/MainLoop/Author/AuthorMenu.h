//
// Created by zimni on 12/24/2020.
//

#pragma once
#ifndef COURSEWORK_AUTHORMENU_H
#define COURSEWORK_AUTHORMENU_H

#include "../../Storage/Author/AuthorStorage.cpp"
#include "../../../Models/Author/Author.cpp"

class AuthorMenu {
private:
    static bool isRunning;
public:
    static void run();

    static void exit();

    static void printOptions();

    static void chooseOperation();

    static void showAll();

    static void add();

    static void remove();

    static void find();

    static void findById();

    static void findByName();

    static void findBySurname();

    static void findByYearOfBirth();

    static void findByPlaceOfBirth();

    static void edit();

    static int getIdOfAuthorToEdit();

    static void editName(Author* pAuthor);

    static void editSurname(Author* pAuthor);

    static void editYearOfBirth(Author* pAuthor);

    static void editPlaceOfBirth(Author* pAuthor);

    static void saveChanges(Author* pAuthor);
};


#endif //COURSEWORK_AUTHORMENU_H
