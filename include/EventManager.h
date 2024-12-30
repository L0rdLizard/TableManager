#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
#include <vector>
#include "TableManager.h"
#include "ClientManager.h"
#include <functional>

enum class EventType { 
    CLIENT_ARRIVAL = 1,
    CLIENT_SEAT = 2,
    CLIENT_WAIT = 3,
    CLIENT_LEAVE = 4,
    CLIENT_LEAVE_FINAL = 11,
    CLIENT_SEAT_FIRST = 12,
    ERROR = 13
};

class EventManager {
public:
    struct Event {
        TimeUtil time;
        EventType id;
        std::string data;
    };

    using EventHandler = std::function<void(const Event&)>;

    EventManager(TableManager& tableManager, ClientManager& clientManager);

    void registerEventHandlers();

    bool loadEvents(const std::string& filePath);

    void processEvents();

    std::vector<Event> getEventLog() const;

private:
    TableManager& tableManager;
    ClientManager& clientManager;
    std::unordered_map<EventType, EventHandler> eventHandlers;
    std::vector<Event> events;
    std::vector<Event> eventLog;

    void handleEvent(const Event& event);

    void handleClientArrival(const Event& event);
    void handleClientSeat(const Event& event);
    void handleClientWait(const Event& event);
    void handleClientLeave(const Event& event);
    void handleClientLeaveFinal(const Event& event);
    void handleClientSeatFirst(const Event& event);
    void handleError(const Event& event);

    void logEvent(const TimeUtil& time, int id, const std::string& data);
};

#endif
