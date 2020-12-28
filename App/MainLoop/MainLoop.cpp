//
// Created by zimni on 12/24/2020.
//

#include "MainLoop.h"
bool BookMenu::isRunning = false;
bool AuthorMenu::isRunning = false;

void MainLoop::run() {
    Output::print("1. Book");
    Output::print("2. Author");
    Output::print("3. Exit program");

    chooseMainOperation();
}

void MainLoop::chooseMainOperation() {
    int answer = Input::askInt();

    switch (answer) {
        case 1:
            BookMenu::run();
            break;
        case 2:
            AuthorMenu::run();
            break;
        case 3:
            Application::exit();
            break;
        default:
            break;
    }
}
