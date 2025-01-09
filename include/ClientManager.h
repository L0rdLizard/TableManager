#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "utils/TimeUtil.h"

class ClientManager {
public:
    struct Client {
        std::string name;
        bool isInside;
        int tableID = 0;

        Client() : name(""), isInside(false), tableID(0) {}

        Client(const std::string& name) 
            : name(name), isInside(false) {}
    };

    ClientManager();

    virtual bool isClientInside(const std::string& clientName) const;

    virtual void registerClient(const std::string& clientName);

    virtual void unregisterClient(const std::string& clientName, const TimeUtil& departureTime);

    virtual void seatClient(const std::string& clientName, unsigned int tableID);

    virtual std::vector<std::string> getAllClientNames() const;

    virtual Client getClient(const std::string& clientName) const;

    virtual ~ClientManager() = default;

private:
    std::unordered_map<std::string, Client> clients;
};

#endif
