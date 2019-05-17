#ifndef timestamp_hpp
#define timestamp_hpp

#include <string>

using std::string;

/** @brief Helps getting timestamp in needed format */
class Timestamp{
public:
    /** @brief Returns time since epoch */
    string GetTimestamp();
    /** @brief Returns current time in UTC format */
    string GetCurrentTime();
};

#endif