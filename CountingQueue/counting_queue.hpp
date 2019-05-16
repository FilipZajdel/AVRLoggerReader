#ifndef counting_queue_hpp
#define counting_queue_hpp

#include <mutex>
#include <queue>
#include <string>

#include "../LogQueue/log_queue.hpp"

#include <cstdint>

using std::mutex;
using std::queue;
using std::string;

/** @brief Queue for being read by fixed times. After fixed times of reading it
 * destroys front element by itself.
 */
class CountingQueue : public LogStringQueue {
 public:
  CountingQueue(int MaxCount);
  virtual string Front();
  virtual bool IsEmpty() const;

 private:
  const int MaxCount;
  int CountTimes;
};

#endif