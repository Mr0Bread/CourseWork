//
// Created by zimni on 12/24/2020.
//

#include "Input.h"

int Input::askInt(const std::string& message) {
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
    while (std::cin.get() != '\n');
}

std::string Input::askString(const std::string& message) {
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

std::string Input::askString(const int symbolLimit, const std::string& message) {
    bool run = true;
    auto input = askString(message);

    while (run) {
        if (input.length() > symbolLimit) {
            input = askString(
                    "Input exceeds symbol limit: "
                    + std::to_string(symbolLimit) +
                    "\n Enter one more time"
            );
        } else {
            run = false;
        }
    }

    return input;
}
