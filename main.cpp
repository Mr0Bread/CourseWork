#include <iostream>
#include "App/Output/Output.cpp"
#include "App/Input/Input.cpp"
#include "App/Application.cpp"

bool Application::isRunning = false;

int main() {
    Application::run();
    return 0;
}
