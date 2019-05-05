#ifndef log_queue_hpp
#define log_queue_hpp

#include <string>
#include <mutex>
#include <queue>

using std::string;
using std::mutex;
using std::queue;

/** @brief Queue for accumulating strings, allowing to access from multiple threads.
 */
class LogStringQueue{
public:
    LogStringQueue();
    bool IsEmpty() const;
    string Front() const;
    int Size() const;
    void ClearFront();
    void Push(string);
private:
    mutex *Mutex;
    queue <string> Queue;
};

#endif