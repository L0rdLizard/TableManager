#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include <string>

class TimeUtil {
private:
    int hour;
    int minute;

public:
    TimeUtil(const std::string& time);
    TimeUtil(int hour, int minute);

    bool operator<(const TimeUtil& other) const;

    TimeUtil operator+(const TimeUtil& other) const;
    TimeUtil operator-(const TimeUtil& other) const;

    bool operator>(const TimeUtil& other) const { return other < *this; }
    bool operator<=(const TimeUtil& other) const { return !(other < *this); }
    bool operator>=(const TimeUtil& other) const { return !(*this < other); }
    bool operator==(const TimeUtil& other) const { return !(*this < other) && !(other < *this); }
    bool operator!=(const TimeUtil& other) const { return !(*this == other); }

    ~TimeUtil();
};

#endif