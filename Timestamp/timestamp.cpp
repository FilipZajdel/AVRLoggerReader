#include "timestamp.hpp"

#include <chrono>
#include <cstdint>
#include <sstream>
#include <array>

using std::array;

string Timestamp::GetCurrentTime(){
    std::time_t Now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char Buffer[100] = {0};
    std::strftime(Buffer, sizeof(Buffer), "%F %T", std::localtime(&Now));
    return string{Buffer};
}

string Timestamp::GetTimestamp(){

    uint64_t SecondsSinceEpoch =
    std::chrono::system_clock::now().time_since_epoch() / 
    std::chrono::seconds(1);

    std::stringstream TimeSinceEpoch{};
    TimeSinceEpoch << SecondsSinceEpoch;

    return TimeSinceEpoch.str();
}