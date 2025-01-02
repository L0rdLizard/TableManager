#ifndef TABLE_MANAGER_H
#define TABLE_MANAGER_H

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "../utils/TimeUtil.h"
#include <functional>

class TableManager {
public:
    struct Table {
        int id;
        bool isOccupied;
        std::string occupiedBy;
        int revenue;
        // int occupiedMinutes;
        TimeUtil occupiedSince;
    };

    TableManager(int tableCount);

    bool occupyTable(const std::string& clientName, int tableId, const TimeUtil& currentTime);

    bool releaseTable(const std::string& clientName, const TimeUtil& currentTime);

    void addToQueue(const std::string& clientName);

    bool processQueue(int tableId, const TimeUtil& currentTime);

    void finalizeDailyReport(const TimeUtil& endTime);

    bool isTableOccupied(int tableId) const;

    bool isAnyFreeTable() const;

    std::vector<Table> getTableStatus() const;

    std::string getNextInQueue() const;

    int getQueueSize() const;

private:
    int tableCount;
    int hourlyRate;
    std::vector<Table> tables;
    std::queue<std::string> waitingQueue;
    std::unordered_map<std::string, int> clientTableMap;

    // int roundUpToHour(int minutes) const;
};

#endif
