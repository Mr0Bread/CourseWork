//
// Created by zimni on 12/24/2020.
//

#include "Application.h"
#include "MainLoop/MainLoop.cpp"

void Application::run() {
    BookStorage::init();
    AuthorStorage::init();
    isRunning = true;

    printGreetings();
    while (isRunning) {
        MainLoop::run();
    }
}

void Application::exit() {
    std::remove(BOOK_FILE_NAME);
    std::remove(AUTHORS_FILE_NAME);
    isRunning = false;
}

void Application::printGreetings() {
    Output::print("Hello");
}
