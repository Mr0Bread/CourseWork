//
// Created by zimni on 12/24/2020.
//

#pragma once
#ifndef COURSEWORK_MAINLOOP_H
#define COURSEWORK_MAINLOOP_H

#include "Author/AuthorMenu.cpp"
#include "Book/BookMenu.cpp"

class MainLoop {
public:
    static void run();

    static void chooseMainOperation();
};


#endif //COURSEWORK_MAINLOOP_H
