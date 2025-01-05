#ifndef TABLE_MANAGER_H
#define TABLE_MANAGER_H

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "utils/TimeUtil.h"
#include <functional>

class TableManager {
public:
    struct Table {
        int id;
        bool isOccupied;
        std::string occupiedBy;
        int revenue;
        TimeUtil occupiedSince;
        TimeUtil totalTime;

        Table() : id(0), isOccupied(false), occupiedBy(""), revenue(0), occupiedSince(TimeUtil(0, 0)), totalTime(TimeUtil(0, 0) ) {}
    };

    TableManager(int tableCount, int hourlyRate);

    virtual bool occupyTable(const std::string& clientName, int tableId, const TimeUtil& currentTime);

    virtual bool releaseTable(const std::string& clientName, const TimeUtil& currentTime);

    virtual void addToQueue(const std::string& clientName);

    // bool processQueue(int tableId, const TimeUtil& currentTime);

    virtual void finalizeDailyReport(const TimeUtil& endTime);

    virtual bool isTableOccupied(int tableId) const;

    virtual bool isAnyFreeTable() const;

    virtual std::vector<Table> getTableStatus() const;

    virtual std::string getNextInQueue();

    virtual int getQueueSize() const;

    virtual std::vector<Table> getTables() const;

    virtual ~TableManager() = default;

private:
    int tableCount;
    int hourlyRate;
    std::vector<Table> tables;
    std::queue<std::string> waitingQueue;
    std::unordered_map<std::string, int> clientTableMap;

};

#endif
