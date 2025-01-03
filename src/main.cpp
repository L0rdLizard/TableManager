#include "../include/EventManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string path = "../input/day1.txt";
    EventManager eventManager(path);
    eventManager.loadEvents();
    eventManager.processEvents();
    eventManager.printEventLog();
    return 0;
}