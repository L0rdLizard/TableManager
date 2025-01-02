#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../utils/TimeUtil.h"

class ClientManager {
public:
    struct Client {
        std::string name;
        bool isInside;
        int tableID = 0;

        Client(const std::string& name) 
            : name(name), isInside(false) {}
    };

    ClientManager();

    bool isClientInside(const std::string& clientName) const;

    void registerClient(const std::string& clientName);

    void unregisterClient(const std::string& clientName, const TimeUtil& departureTime);

    void seatClient(const std::string& clientName, unsigned int tableID);

    // std::unordered_set<Client> getAllClients() const;

    std::vector<std::string> getAllClientNames() const;

    Client getClient(const std::string& clientName) const;

private:
    std::unordered_map<std::string, Client> clients;
};

#endif
