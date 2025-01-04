#include <iostream>
#include "ClientManager.h"

ClientManager::ClientManager() {}

bool ClientManager::isClientInside(const std::string& clientName) const {
    auto it = clients.find(clientName);
    return it != clients.end() && it->second.isInside;
}

void ClientManager::registerClient(const std::string& clientName) {
    clients[clientName] = Client(clientName);
    clients[clientName].isInside = true;
}

void ClientManager::unregisterClient(const std::string& clientName, const TimeUtil& departureTime) {
    auto it = clients.find(clientName);
    it->second.isInside = false;
}

void ClientManager::seatClient(const std::string& clientName, unsigned int tableID) {
    auto it = clients.find(clientName);
    it->second.tableID = tableID;
}

std::vector<std::string> ClientManager::getAllClientNames() const {
    std::vector<std::string> names;
    for (const auto& client : clients) {
        names.push_back(client.first);
    }
    return names;
}

ClientManager::Client ClientManager::getClient(const std::string& clientName) const {
    auto it = clients.find(clientName);
    return it->second;
}