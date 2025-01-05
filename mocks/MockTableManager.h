#ifndef MOCK_TABLE_MANAGER_H
#define MOCK_TABLE_MANAGER_H

#include "TableManager.h"
#include <gmock/gmock.h>

class MockTableManager : public TableManager {
public:
    MockTableManager(int tableCount, int hourlyRate) 
        : TableManager(tableCount, hourlyRate) {}

    MOCK_METHOD(bool, occupyTable, (const std::string& clientName, int tableId, const TimeUtil& currentTime), (override));
    MOCK_METHOD(bool, releaseTable, (const std::string& clientName, const TimeUtil& currentTime), (override));
    MOCK_METHOD(void, addToQueue, (const std::string& clientName), (override));
    MOCK_METHOD(void, finalizeDailyReport, (const TimeUtil& endTime), (override));
    MOCK_METHOD(bool, isTableOccupied, (int tableId), (const, override));
    MOCK_METHOD(bool, isAnyFreeTable, (), (const, override));
    MOCK_METHOD(std::vector<Table>, getTableStatus, (), (const, override));
    MOCK_METHOD(std::string, getNextInQueue, (), (override));
    MOCK_METHOD(int, getQueueSize, (), (const, override));
    MOCK_METHOD(std::vector<Table>, getTables, (), (const, override));
};

#endif
