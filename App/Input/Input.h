//
// Created by zimni on 12/24/2020.
//

#pragma once
#ifndef COURSEWORK_INPUT_H
#define COURSEWORK_INPUT_H


class Input {
public:
    static int askInt(const std::string& message = "");

    static std::string askString(const std::string& message = "");

    static std::string askString(const int symbolLimit, const std::string& message = "");

    static void clearInputBuffer();
};


#endif //COURSEWORK_INPUT_H
