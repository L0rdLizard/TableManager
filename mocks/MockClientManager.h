#include "gmock/gmock.h"
#include "ClientManager.h"

class MockClientManager : public ClientManager {
public:
    MockClientManager() : ClientManager() {}

    MOCK_METHOD(bool, isClientInside, (const std::string& clientName), (const, override));
    MOCK_METHOD(void, registerClient, (const std::string& clientName), (override));
    MOCK_METHOD(void, unregisterClient, (const std::string& clientName, const TimeUtil& departureTime), (override));
    MOCK_METHOD(void, seatClient, (const std::string& clientName, unsigned int tableID), (override));
    MOCK_METHOD(std::vector<std::string>, getAllClientNames, (), (const, override));
    MOCK_METHOD(Client, getClient, (const std::string& clientName), (const, override));
};
