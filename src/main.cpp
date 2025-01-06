#include "EventManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Wrong number of arguments!" << std::endl;
        return 1;
    }

    std::string relativePath = argv[1];

    std::string currentDir = "../input/";
    std::string fullPath = currentDir + relativePath;

    EventManager eventManager(fullPath);
    if ( !eventManager.loadEvents(eventManager.readLinesFromFile()) ) {
        return 1;
    }
    eventManager.processEvents();
    eventManager.printEventLog();
    eventManager.printEventLogToFile();
    return 0;
}