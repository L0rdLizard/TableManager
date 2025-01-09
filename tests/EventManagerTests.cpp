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

    // EXPECT_CALL(*mockTableManager, isAnyFreeTable())
    //     .WillOnce(testing::Return(true));

    // EXPECT_CALL(*mockClientManager, registerClient("client1"));

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

    // std::vector<std::string> eventLines = {
    //     "3",
    //     "09:00 19:00",
    //     "10",
    //     "08:48 1 client1",
    //     "09:41 1 client1",
    //     "09:48 1 client2",
    //     "09:52 3 client1",
    //     "09:54 2 client1 1",
    //     "10:25 2 client2 2",
    //     "10:58 1 client3",
    //     "10:59 2 client3 3",
    //     "11:30 1 client4",
    //     "11:35 2 client4 2",
    //     "11:45 3 client4",
    //     "12:33 4 client1",
    //     "12:43 4 client2",
    //     "15:52 4 client4"
    // };

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

    EXPECT_CALL(*mockClientManager, isClientInside(testing::_))
    .WillOnce(testing::Return(false));

    EXPECT_CALL(*mockTableManager, finalizeDailyReport(testing::Eq(endTime)));

    EXPECT_CALL(*mockClientManager, getAllClientNames())
        .WillOnce(testing::Return(std::vector<std::string>{}));

    bool result = eventManager.loadEvents(eventLines);
    eventManager.processEvents();
    std::vector<EventManager::Event> eventLog = eventManager.getEventLog();

    int eventType = static_cast<int>(eventLog.back().id);

    EXPECT_EQ( eventType, 13 );
}

TEST (EventManagerTest, TestGetEventLog) {
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
        "08:41 1 client1",
    };

    EXPECT_CALL(*mockClientManager, isClientInside(testing::_))
    .WillOnce(testing::Return(false));
    
}