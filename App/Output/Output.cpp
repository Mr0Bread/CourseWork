//
// Created by zimni on 12/27/2020.
//

#include "Output.h"

void Output::print(const std::string& text = "") {
    std::cout << text << std::endl;
}

void Output::print(int numToPrint) {
    std::cout << std::to_string(numToPrint) << std::endl;
}
