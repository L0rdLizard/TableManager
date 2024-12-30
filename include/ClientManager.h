#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <string>
#include <vector>

class ClientManager {
public:
    struct Client {
        std::string name;
        int arrivalTime;
    };

    ClientManager();
};

#endif
