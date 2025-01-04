#include "utils/TimeUtil.h"
#include <stdexcept>

TimeUtil::TimeUtil(const std::string& time) {
    if (time.length() != 5 || time[2] != ':') {
        throw std::invalid_argument("Invalid time format");
    }
    std::string hour_str = time.substr(0, 2);
    std::string minute_str = time.substr(3, 2);

    if (std::stoi(hour_str) > 23 || std::stoi(minute_str) > 59) {
        throw std::invalid_argument("Invalid time format");
    }

    hour = std::stoi(hour_str);
    minute = std::stoi(minute_str);
}

TimeUtil::TimeUtil(int hour, int minute) : hour(hour), minute(minute) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        throw std::out_of_range("Time values out of range.");
    }
}

TimeUtil::TimeUtil() : hour(0), minute(0) {}

bool TimeUtil::operator<(const TimeUtil& other) const {
    if (hour < other.hour) {
        return true;
    } else if (hour == other.hour) {
        return minute < other.minute;
    } else {
        return false;
    }
}

TimeUtil TimeUtil::operator+(const TimeUtil& other) const {
    int newHour = hour + other.hour;
    int newMinute = minute + other.minute;

    if (newMinute >= 60) {
        newMinute -= 60;
        newHour += 1;
    }

    // if (newHour >= 24) {
    //     newHour -= 24;
    // }

    return TimeUtil(newHour, newMinute);
}

TimeUtil TimeUtil::operator-(const TimeUtil& other) const {
    int newHour = hour - other.hour;
    int newMinute = minute - other.minute;

    if (newMinute < 0) {
        newMinute += 60;
        newHour -= 1;
    }

    // if (newHour < 0) {
    //     newHour += 24;
    // }

    return TimeUtil(newHour, newMinute);
}

std::string TimeUtil::toString() const {
    return (hour < 10 ? "0" : "") + std::to_string(hour) + ":" +
        (minute < 10 ? "0" : "") + std::to_string(minute);
}


std::ostream& operator<<(std::ostream& os, const TimeUtil& time) {
    os << time.toString();
    return os;
}

int TimeUtil::getRoundTime() const {
    return hour + (minute >= 1 ? 1 : 0);
}

TimeUtil::~TimeUtil() {}