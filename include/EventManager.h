#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
#include <vector>
#include "TableManager.h"
#include "ClientManager.h"
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

class EventManager {
public:
    struct Event {
        TimeUtil time;
        EventType id;
        std::string clientName;
        unsigned int tableID;

        Event(TimeUtil t, EventType et, const std::string& name, unsigned int table = 0)
            : time(t), id(et), clientName(name), tableID(table) {}
    };
    
    using EventHandler = std::function<void(const Event&)>;

    EventManager(const std::string& path);

    EventManager(const std::string& path, TableManager* tableManager, ClientManager* clientManager, 
            int tableCount, int hourlyRate, const TimeUtil& start, const TimeUtil& end);

    void registerEventHandlers();

    std::vector<std::string> readLinesFromFile() const;
    bool loadEvents(const std::vector<std::string>& eventLines);

    void processEvents();

    std::vector<Event> getEventLog() const;

    void printEventLog() const;

    void printEventLogToFile() const;

private:
    std::string filePath;
    std::unique_ptr<TableManager> tableManager{nullptr};
    std::unique_ptr<ClientManager> clientManager{nullptr};

    int tableCount = 0;
    int hourlyRate = 0;

    TimeUtil timeStart = TimeUtil();
    TimeUtil timeEnd = TimeUtil();

    std::unordered_map<EventType, EventHandler> eventHandlers;
    std::vector<Event> events;
    std::vector<Event> eventLog;

    void handleEvent(const Event& event);

    void handleClientArrival(const Event& event);
    void handleClientSeat(const Event& event);
    void handleClientWait(const Event& event);
    void handleClientLeave(const Event& event);

    void printBilling() const;

    void logEvent(const TimeUtil& time, int id, const std::string& data, unsigned int table = 0);
};

#endif
