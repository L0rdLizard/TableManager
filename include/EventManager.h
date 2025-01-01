#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
#include <vector>
#include "TableManager.h"
#include <functional>
#include <memory>

enum class EventType { 
    CLIENT_ARRIVAL = 1,
    CLIENT_SEAT = 2,
    CLIENT_WAIT = 3,
    CLIENT_LEAVE = 4,
    CLIENT_LEAVE_FINAL = 11,
    CLIENT_SEAT_FIRST = 12,
    ERROR = 13
};

struct Event {
    TimeUtil time;
    EventType id;
    std::string clientName;
    unsigned int tableID;

    Event(TimeUtil t, EventType et, const std::string& name, unsigned int table = 0)
        : time(t), id(et), clientName(name), tableID(table) {}
};

class EventManager {
public:
    
    using EventHandler = std::function<void(const Event&)>;

    EventManager(const std::string& configFilePath);

    void registerEventHandlers();

    bool loadEvents(const std::string& filePath);

    void processEvents();

    std::vector<Event> getEventLog() const;

    void printEventLog() const;

private:
    // TableManager& tableManager;
    std::unique_ptr<TableManager> tableManager{nullptr};
    std::unordered_map<EventType, EventHandler> eventHandlers;
    std::vector<Event> events;
    std::vector<Event> eventLog;

    void handleEvent(const Event& event);

    void handleClientArrival(const Event& event);
    void handleClientSeat(const Event& event);
    void handleClientWait(const Event& event);
    void handleClientLeave(const Event& event);

    void logEvent(const TimeUtil& time, int id, const std::string& data);
};

#endif
