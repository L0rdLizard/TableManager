#include "MockTableManager.h"
#include "MockClientManager.h"
#include "EventManager.h"
#include "gtest/gtest.h"

TEST(EventManagerTest, TestLoadEvents) {
    int tableCount = 3;
    int hourlyRate = 10;
    TimeUtil startTime(9, 0);
    TimeUtil endTime(19, 0);

    MockTableManager* mockTableManager = new MockTableManager(tableCount, hourlyRate);
    MockClientManager* mockClientManager = new MockClientManager();

    EventManager eventManager(
        "test_file.txt",
        mockTableManager,
        mockClientManager,
        tableCount, 
        hourlyRate, 
        startTime, 
        endTime
    );

    std::vector<std::string> eventLines = {
        "3",
        "09:00 19:00",
        "10",
        "09:41 1 client1",
        "09:54 2 client1 1",
        "12:33 4 client1"
    };

    bool result = eventManager.loadEvents(eventLines);
    EXPECT_TRUE( result );
}

TEST (EventManagerTest, TestProcessEvents) {
    int tableCount = 3;
    int hourlyRate = 10;
    TimeUtil startTime(9, 0);
    TimeUtil endTime(19, 0);

    MockTableManager* mockTableManager = new MockTableManager(tableCount, hourlyRate);
    MockClientManager* mockClientManager = new MockClientManager();

    EXPECT_CALL(*mockClientManager, isClientInside(testing::_))
    .WillOnce(testing::Return(false))
    .WillOnce(testing::Return(true));

    EXPECT_CALL(*mockTableManager, finalizeDailyReport(testing::Eq(endTime)));

    EXPECT_CALL(*mockClientManager, getAllClientNames())
        .WillOnce(testing::Return(std::vector<std::string>{}));

    EXPECT_CALL(*mockClientManager, registerClient(testing::_));

    ClientManager::Client expectedClient;
    expectedClient.tableID = 1;
    EXPECT_CALL(*mockClientManager, getClient(testing::_))
        .WillOnce(testing::Return(expectedClient));

    EXPECT_CALL(*mockClientManager, unregisterClient(testing::_, testing::_));

    EXPECT_CALL(*mockTableManager, releaseTable(testing::_, testing::_));

    EXPECT_CALL(*mockTableManager, getNextInQueue())
        .WillOnce(testing::Return(""));

    EventManager eventManager(
        "test_file.txt",
        mockTableManager,
        mockClientManager,
        tableCount, 
        hourlyRate, 
        startTime, 
        endTime
    );

    std::vector<std::string> eventLines = {
        "3",
        "09:00 19:00",
        "10",
        "09:41 1 client1",
        "09:51 4 client1",
    };

    bool result = eventManager.loadEvents(eventLines);
    eventManager.processEvents();
    std::vector<EventManager::Event> eventLog = eventManager.getEventLog();

    int eventType = static_cast<int>(eventLog.back().id);

    EXPECT_EQ( eventType, 4 );
}

TEST (EventManagerTest, TestProcessEventsError) {
    int tableCount = 3;
    int hourlyRate = 10;
    TimeUtil startTime(9, 0);
    TimeUtil endTime(19, 0);

    MockTableManager* mockTableManager = new MockTableManager(tableCount, hourlyRate);
    MockClientManager* mockClientManager = new MockClientManager();

    EXPECT_CALL(*mockClientManager, isClientInside(testing::_))
    .WillOnce(testing::Return(false));

    EXPECT_CALL(*mockTableManager, finalizeDailyReport(testing::Eq(endTime)));

    EXPECT_CALL(*mockClientManager, getAllClientNames())
        .WillOnce(testing::Return(std::vector<std::string>{}));

    EventManager eventManager(
        "test_file.txt",
        mockTableManager,
        mockClientManager,
        tableCount, 
        hourlyRate, 
        startTime, 
        endTime
    );

    std::vector<std::string> eventLines = {
        "3",
        "09:00 19:00",
        "10",
        "08:41 1 client1",
    };

    bool result = eventManager.loadEvents(eventLines);
    eventManager.processEvents();
    std::vector<EventManager::Event> eventLog = eventManager.getEventLog();

    int eventType = static_cast<int>(eventLog.back().id);

    EXPECT_EQ( eventType, 13 );
}