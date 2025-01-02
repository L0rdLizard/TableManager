#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "TimeUtil.h"

class ClientManager {
public:
    struct Client {
        std::string name;
        bool isInside;
        unsigned int tableID = 0;
        // int totalTimeSpent;
        // int totalPayment;

        // Client(const std::string& name) 
        //     : name(name), isInside(false), totalTimeSpent(0), totalPayment(0) {}

        Client(const std::string& name) 
            : name(name), isInside(false) {}
    };

    ClientManager();

    bool isClientInside(const std::string& clientName) const;

    bool registerClient(const std::string& clientName, const TimeUtil& arrivalTime);

    bool unregisterClient(const std::string& clientName, const TimeUtil& departureTime);

    void seatClient(const std::string& clientName, unsigned int tableID);

    // int getClientTimeSpent(const std::string& clientName) const;

    // int getClientTotalPayment(const std::string& clientName) const;

    // void updateClientTime(const std::string& clientName, const TimeUtil& startTime, const TimeUtil& endTime);

    std::unordered_set<std::string> getAllClients() const;

    Client getClient(const std::string& clientName) const;

private:
    std::unordered_map<std::string, Client> clients;
};

#endif
