#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include <string>

class TimeUtil {
private:
    int hour;
    int minute;

public:
    TimeUtil(const std::string& time);
    bool operator<(const TimeUtil& other) const;

    bool operator>(const TimeUtil& other) const { return other < *this; }
    bool operator<=(const TimeUtil& other) const { return !(other < *this); }
    bool operator>=(const TimeUtil& other) const { return !(*this < other); }
    bool operator==(const TimeUtil& other) const { return !(*this < other) && !(other < *this); }
    bool operator!=(const TimeUtil& other) const { return !(*this == other); }
};

#endif