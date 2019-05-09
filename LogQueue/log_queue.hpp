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
    virtual ~LogStringQueue(){};
    virtual bool IsEmpty() const;
    virtual string Front();
    virtual int Size() const;
    virtual void ClearFront();
    virtual void Push(string);
protected:
    mutex *Mutex;
    queue <string> Queue;
};

#endif