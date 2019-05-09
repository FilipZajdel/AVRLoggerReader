#ifndef counting_queue_hpp
#define counting_queue_hpp

#include <string>
#include <mutex>
#include <queue>

#include "../LogQueue/log_queue.hpp"

#include <cstdint>

using std::string;
using std::mutex;
using std::queue;

/** @brief Queue for being read by fixed times. After fixed times of reading it destroys front element by itself.
 */
class CountingQueue : public LogStringQueue{
public:
    CountingQueue(int MaxCount);
    virtual string Front();
private:
    const int MaxCount;
    int CountTimes;
};

#endif