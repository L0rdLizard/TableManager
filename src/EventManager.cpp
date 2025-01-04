#include "EventManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

EventManager::EventManager(const std::string& path) : filePath(path) {
    registerEventHandlers();
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(file, line);
    tableCount = atoi(line.c_str());

    std::getline(file, line);
    std::istringstream ss(line);
    std::string time_str1, time_str2;
    if (ss >> time_str1 >> time_str2) {
        timeStart = TimeUtil(time_str1);
        timeEnd = TimeUtil(time_str2);
    } else {
        std::cerr << "Invalid time format: " << line << std::endl;
        exit(1);
    }

    std::getline(file, line);
    hourlyRate = atoi(line.c_str());

    tableManager = std::make_unique<TableManager>(tableCount, hourlyRate);
    clientManager = std::make_unique<ClientManager>();
}


bool isValidEventType(int id) {
    return (id >= 1 && id <= 4) || id == 11 || id == 12 || id == 13;
}

bool EventManager::loadEvents() {
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

    std::vector<std::string> sortedClients = clientManager->getAllClientNames();
    for (const auto& client : sortedClients) {
        if (clientManager->isClientInside(client)) {
            tableManager->releaseTable(client, timeEnd);
            logEvent(timeEnd, 11, client);
        }
    }

    tableManager->finalizeDailyReport(timeEnd);
}

std::vector<EventManager::Event> EventManager::getEventLog() const {
    return eventLog;
}

void EventManager::printEventLog() const {
    std::cout << timeStart << std::endl;
    for (const auto& event : eventLog) {
        std::cout << event.time << " " << static_cast<int>(event.id) 
            << " " << event.clientName;

        if (event.tableID != 0) {
            std::cout << " " << event.tableID;
        }

        std::cout << std::endl;
    }
    std::cout << timeEnd << std::endl;
    printBilling();
}

void EventManager::printBilling() const{
    std::vector<TableManager::Table> tables = tableManager->getTables();
    for (const auto& table : tables) {
        std::cout << table.id << " " << table.revenue << " " << table.totalTime << std::endl;
    }
}

void EventManager::logEvent(const TimeUtil& time, int id, const std::string& data, unsigned int table) {
    eventLog.emplace_back(Event(time, static_cast<EventType>(id), data, table));
}

void EventManager::printEventLogToFile() const {
    size_t inputPos = filePath.find("/input/");
    std::string outputPath = filePath;
    outputPath.replace(inputPos, 7, "/output/");

    size_t dotPos = outputPath.rfind(".txt");
    if (dotPos != std::string::npos) {
        outputPath.replace(dotPos, 4, "_report.txt");\
    }

    std::ofstream file(outputPath);
    if (file.is_open()) {
        file << timeStart << std::endl;
        for (const auto& event : eventLog) {
            file << event.time << " " << static_cast<int>(event.id) << " " << event.clientName;
            if (event.tableID != 0) {
                file << " " << event.tableID;
            }
            file << std::endl;
        }
        file << timeEnd << std::endl;
        std::vector<TableManager::Table> tables = tableManager->getTables();
        for (const auto& table : tables) {
            file << table.id << " " << table.revenue << " " << table.totalTime << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Failed to open file: " << outputPath << std::endl;
    }
}

void EventManager::handleClientArrival(const Event& event) {
    logEvent(event.time, 1, event.clientName);
    if (clientManager->isClientInside(event.clientName)) {
        logEvent(event.time, 13, "YouShallNotPass");
        return;
    }

    if (event.time < timeStart || event.time > timeEnd) {
        logEvent(event.time, 13, "NotOpenYet");
        return;
    }

    clientManager->registerClient(event.clientName);
}

void EventManager::handleClientSeat(const Event& event) {
    logEvent(event.time, 2, event.clientName, event.tableID);
    if ( tableManager->isTableOccupied(event.tableID) ) {
        logEvent(event.time, 13, "PlaceIsBusy");
        return;
    }

    if ( !clientManager->isClientInside(event.clientName) ) {
        logEvent(event.time, 13, "ClientUnknown");
        return;
    }

    if ( clientManager->getClient(event.clientName).tableID != 0 ) {
        tableManager->releaseTable(event.clientName, event.time);
    }

    tableManager->occupyTable(event.clientName, event.tableID, event.time);
    clientManager->seatClient(event.clientName, event.tableID);
}

void EventManager::handleClientWait(const Event& event) {
    logEvent(event.time, 3, event.clientName);
    if (tableManager->isAnyFreeTable()) {
        logEvent(event.time, 13, "ICanWaitNoLonger!");
        return;
    }

    if (tableManager->getQueueSize() > tableCount) {
        clientManager->unregisterClient(event.clientName, event.time);
        logEvent(event.time, 11, event.clientName);
    }

    tableManager->addToQueue(event.clientName);
}

void EventManager::handleClientLeave(const Event& event) {
    logEvent(event.time, 4, event.clientName);
    if ( !clientManager->isClientInside(event.clientName) ) {
        logEvent(event.time, 13, "ClientUnknown");
        return;
    }

    int clientTable = clientManager->getClient(event.clientName).tableID;
    clientManager->unregisterClient(event.clientName, event.time);
    tableManager->releaseTable(event.clientName, event.time);
    // tableManager->processQueue(event.tableID, event.time);

    std::string nextInQueue = tableManager->getNextInQueue();
    if (nextInQueue != "") {
        tableManager->occupyTable(nextInQueue, clientTable, event.time);
        clientManager->seatClient(nextInQueue, clientTable);

        logEvent(event.time, 12, nextInQueue, clientTable);
    }
}
