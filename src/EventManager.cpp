#include "../include/EventManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

EventManager::EventManager(TableManager& tableManager) : tableManager(tableManager) {}

bool isValidEventType(int id) {
    return (id >= 1 && id <= 4) || id == 11 || id == 12 || id == 13;
}

bool EventManager::loadEvents(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ' ')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 3 || tokens.size() > 4) {
            std::cerr << "Invalid event format: " << line << std::endl;
            std::exit(1);
        }

        try {
            TimeUtil time(tokens[0]);
            int event_id = std::stoi(tokens[1]);

            if (!isValidEventType(event_id)) {
                std::cerr << "Invalid event format: " << line << std::endl;
                std::exit(1);
            }

            events.push_back({time, static_cast<EventType>(event_id), tokens[2]});
        } catch (const std::exception& e) {
            std::cerr << "Error processing event: " << line << std::endl;
            std::exit(1);
        }
    }
    return true;
}

void EventManager::registerEventHandlers() {
    eventHandlers[EventType::CLIENT_ARRIVAL] = [this](const Event& event) { handleClientArrival(event); };
    eventHandlers[EventType::CLIENT_SEAT] = [this](const Event& event) { handleClientSeat(event); };
    eventHandlers[EventType::CLIENT_WAIT] = [this](const Event& event) { handleClientWait(event); };
    eventHandlers[EventType::CLIENT_LEAVE] = [this](const Event& event) { handleClientLeave(event); };
}

void EventManager::handleEvent(const Event& event) {
    auto handler = eventHandlers.find(event.id);
    if (handler != eventHandlers.end()) {
        handler->second(event);
    } else {
        
    }
}