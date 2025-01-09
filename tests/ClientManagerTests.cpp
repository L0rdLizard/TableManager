#include "ClientManager.h"
#include "gtest/gtest.h"

class ClientManagerTest : public testing::Test {
protected:
    ClientManager clientManager;

    void SetUp() override {
        clientManager.registerClient("client1");
        clientManager.registerClient("client2");
        clientManager.registerClient("client3");
    }
};

TEST_F (ClientManagerTest, isClientInside) {
    clientManager.registerClient("client4");
    EXPECT_TRUE(clientManager.isClientInside("client4"));
}

TEST_F (ClientManagerTest, getClient) {
    EXPECT_EQ(clientManager.getClient("client1").name, "client1");
    EXPECT_EQ(clientManager.getClient("client2").name, "client2");
    EXPECT_EQ(clientManager.getClient("client3").name, "client3");
}

TEST_F (ClientManagerTest, getAllClientNames) {
    EXPECT_EQ(clientManager.getAllClientNames(), std::vector<std::string>({"client1", "client2", "client3"}));
}

TEST_F (ClientManagerTest, unregisterClient) {
    clientManager.unregisterClient("client1", TimeUtil(10, 0));
    EXPECT_FALSE(clientManager.isClientInside("client1"));
}

TEST_F (ClientManagerTest, seatClient) {
    clientManager.seatClient("client1", 1);
    EXPECT_EQ(clientManager.getClient("client1").tableID, 1);
}
