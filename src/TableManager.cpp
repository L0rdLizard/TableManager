#include "TableManager.h"

TableManager::TableManager(int tableCount, int hourlyRate) : tableCount(tableCount), hourlyRate(hourlyRate) {
    for (int i = 0; i < tableCount; i++) {
        tables.push_back(Table());
        tables[i].id = i + 1;
    }
}

TableManager::TableManager() : tableCount(0), hourlyRate(0) {}

void TableManager::occupyTable(const std::string& clientName, int tableId, const TimeUtil& currentTime){
    Table& table = tables[tableId - 1];
    table.isOccupied = true;
    table.occupiedBy = clientName;
    table.occupiedSince = currentTime;

    clientTableMap[clientName] = tableId;
}

void TableManager::releaseTable(const std::string& clientName, const TimeUtil& currentTime){
    auto it = clientTableMap.find(clientName);
    if (it != clientTableMap.end()) {
        int tableId = it->second;
        Table& table = tables[tableId - 1];
        table.isOccupied = false;
        table.occupiedBy = "";

        table.revenue += (currentTime - table.occupiedSince).getRoundTime() * hourlyRate;
        table.totalTime = table.totalTime + (currentTime - table.occupiedSince);

        table.occupiedSince = TimeUtil(0, 0);
        clientTableMap.erase(it);
    }
}

void TableManager::addToQueue(const std::string& clientName){
    waitingQueue.push(clientName);
}

void TableManager::finalizeDailyReport(const TimeUtil& endTime){
    for (Table& table : tables) {
        if (table.isOccupied) {
            table.revenue += (endTime - table.occupiedSince).getRoundTime() * hourlyRate;
        }
    }
}

bool TableManager::isTableOccupied(int tableId) const {
    if (tableId < 1 || tableId > tableCount) return false;
    return tables[tableId - 1].isOccupied;
}

bool TableManager::isAnyFreeTable() const {
    for (const Table& table : tables) {
        if (!table.isOccupied) return true;
    }
    return false;
}

TableManager::Table TableManager::getTable(int tableId) const {
    if (tableId < 1 || tableId > tableCount) return Table();
    return tables[tableId - 1];
}

std::string TableManager::getNextInQueue() {
    if (waitingQueue.empty()) return "";
    std::string clientName = waitingQueue.front();
    waitingQueue.pop();
    return clientName;
}

int TableManager::getQueueSize() const {
    return waitingQueue.size();
}

std::vector<TableManager::Table> TableManager::getTables() const {
    return tables;
}

// TableManager::~TableManager() {}