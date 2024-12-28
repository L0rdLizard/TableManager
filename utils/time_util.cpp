#include "time_util.h"
#include <stdexcept>

TimeUtil::TimeUtil(const std::string& time) {
    std::string hour_str = time.substr(0, 2);
    std::string minute_str = time.substr(3, 2);

    if (std::stoi(hour_str) > 24 || std::stoi(minute_str) > 60) {
        throw std::invalid_argument("Invalid time format");
    }

    hour = std::stoi(hour_str);
    minute = std::stoi(minute_str);
}

bool TimeUtil::operator<(const TimeUtil& other) const {
    if (hour < other.hour) {
        return true;
    } else if (hour == other.hour) {
        return minute < other.minute;
    } else {
        return false;
    }
}