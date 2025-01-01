#include "../include/EventManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

EventManager::EventManager(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(file, line);
    int tableCount = atoi(line.c_str());

    std::getline(file, line);
    TimeUtil time(line);

    std::getline(file, line);
    int hourlyRate = atoi(line.c_str());

    tableManager = std::make_unique<TableManager>(tableCount, hourlyRate);
}


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
    for (int i = 0; i < 3; ++i) {
        std::getline(file, line);
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ' ')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 3 || tokens.size() > 4) {
            std::cerr << "Invalid event format (incorrect number of tokens): " << std::endl << line << std::endl;
            std::exit(1);
        }

        try {
            TimeUtil time(tokens[0]);
            int event_id = std::stoi(tokens[1]);

            if (!isValidEventType(event_id)) {
                std::cerr << "Invalid event format (invalid event type): " << std::endl << line << std::endl;
                std::exit(1);
            }

            if (tokens[2].empty()) {
                std::cerr << "Invalid event format (missing client name): " << std::endl << line << std::endl;
                std::exit(1);
            }
            
            if (event_id == 2) {
                int table_id = std::stoi(tokens[3]);
                events.emplace_back(Event( time, static_cast<EventType>(event_id), tokens[2], table_id ));
            } else {
                events.emplace_back(Event( time, static_cast<EventType>(event_id), tokens[2] ));
            }

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error processing event: " << std::endl << line << std::endl;
            std::exit(1);
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range error in event processing: " << std::endl << line << std::endl;
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
        std::cerr << "Unknown event type: " << static_cast<int>(event.id) << std::endl;
    }
}

void EventManager::processEvents() {
    for (const auto& event : events) {
        handleEvent(event);
    }
}

std::vector<Event> EventManager::getEventLog() const {
    return eventLog;
}

void EventManager::printEventLog() const {
    for (const auto& event : eventLog) {
        std::cout << event.time << " " << static_cast<int>(event.id) << " " << event.clientName << " " << event.tableID << std::endl;
    }
}

void EventManager::logEvent(const TimeUtil& time, int id, const std::string& data) {
    eventLog.emplace_back(Event(time, static_cast<EventType>(id), data));
}

void EventManager::handleClientArrival(const Event& event) {
    tableManager->occupyTable(event.clientName, event.tableID, event.time);
    logEvent(event.time, 1, event.clientName);
}