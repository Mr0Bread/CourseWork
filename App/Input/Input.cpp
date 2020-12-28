//
// Created by zimni on 12/24/2020.
//

#include "Input.h"

int Input::askInt(const std::string message) {
    Output::print(message);
    std::cout << "> ";
    int input;

    while (!(std::cin >> input)) {
        clearInputBuffer();
        Output::print("Invalid input; please re-enter");
        std::cout << "> ";
    }

    return input;
}

void Input::clearInputBuffer() {
    std::cin.clear();
    while(std::cin.get() != '\n');
}

std::string Input::askString(const std::string message) {
    clearInputBuffer();
    Output::print(message);
    std::cout << "> ";
    std::string input;

    while (!getline(std::cin, input)) {
        clearInputBuffer();
        Output::print("Invalid input; please re-enter");
        std::cout << "> ";
    }

    return input;
}
