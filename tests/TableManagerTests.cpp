#include "TableManager.h"
#include "gtest/gtest.h"

class TableManagerTests : public ::testing::Test {
    protected:
        TableManager tableManager;

        void SetUp() override {
            tableManager = TableManager(3, 100);
        }
};

TEST_F(TableManagerTests, GetTableStatus) {
    std::vector<TableManager::Table> tableStatus = tableManager.getTableStatus();
    EXPECT_EQ(tableStatus.size(), 3);
}

TEST_F(TableManagerTests, GetTables) {
    std::vector<TableManager::Table> tables = tableManager.getTables();
    EXPECT_EQ(tables.size(), 3);
}