//
// Created by zimni on 12/24/2020.
//

#pragma once
#ifndef COURSEWORK_BOOKMENU_H
#define COURSEWORK_BOOKMENU_H

#include "../../Storage/Book/BookStorage.cpp"
#include "../../../Models/Book/Book.cpp"

class BookMenu {
private:
    static bool isRunning;

    static void findById();

    static void findByTitle();

    static void findByAuthorId();

    static int getAuthorId();

public:
    static void run();

    static void exit();

    static void printOptions();

    static void chooseOperation();

    static void showAll();

    static void add();

    static void remove();

    static void find();

    static void findByYearOfRelease();

    static void findByLanguage();

    static void findByPageQuantity();

    static int assignExistingAuthorId();

    static int assignIdOfNewAuthor();
};


#endif //COURSEWORK_BOOKMENU_H
