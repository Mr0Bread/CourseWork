//
// Created by zimni on 12/24/2020.
//

#pragma once
#ifndef COURSEWORK_APPLICATION_H
#define COURSEWORK_APPLICATION_H

class Application {
private:
    static bool isRunning;

public:
    static void run();

    static void exit();

    static void printGreetings();
};


#endif //COURSEWORK_APPLICATION_H
