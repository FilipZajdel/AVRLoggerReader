#ifndef timestamp_hpp
#define timestamp_hpp

#include <string>

using std::string;

class Timestamp{
public:
    /** @brief Returns time since epoch */
    string GetTimestamp();
    /** @brief Returns current time in UTC format */
    string GetCurrentTime();
};

#endif