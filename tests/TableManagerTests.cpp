#include "TableManager.h"
#include "gtest/gtest.h"

class TableManagerTests : public testing::Test {
protected:
    TableManager tableManager;

    void SetUp() override {
        tableManager = TableManager(3, 100);
    }
};

TEST_F(TableManagerTests, GetTables) {
    std::vector<TableManager::Table> tables = tableManager.getTables();
    EXPECT_EQ(tables.size(), 3);
}

TEST_F(TableManagerTests, GetTable) {
    TableManager::Table table = tableManager.getTable(1);
    EXPECT_EQ(table.id, 1);
}

TEST_F(TableManagerTests, OccupyTable) {
    tableManager.occupyTable("client1", 1, TimeUtil(0, 0));
    TableManager::Table table = tableManager.getTable(1);
    EXPECT_TRUE(table.isOccupied);
    EXPECT_EQ(table.occupiedBy, "client1");
}

TEST_F(TableManagerTests, ReleaseTable) {
    tableManager.occupyTable("client1", 1, TimeUtil(0, 0));
    tableManager.releaseTable("client1", TimeUtil(0, 0));
    TableManager::Table table = tableManager.getTable(1);
    EXPECT_FALSE(table.isOccupied);
    EXPECT_EQ(table.occupiedBy, "");
}

TEST_F(TableManagerTests, AddToQueue) {
    tableManager.addToQueue("client1");
    EXPECT_EQ(tableManager.getQueueSize(), 1);
}

TEST_F(TableManagerTests, GetNextInQueue) {
    tableManager.addToQueue("client1");
    EXPECT_EQ(tableManager.getNextInQueue(), "client1");
}

TEST_F(TableManagerTests, FinalizeDailyReport) {
    tableManager.occupyTable("client1", 1, TimeUtil(1, 0));
    tableManager.finalizeDailyReport(TimeUtil(11, 0));
    TableManager::Table table = tableManager.getTable(1);
    EXPECT_EQ(table.revenue, 1000);
}