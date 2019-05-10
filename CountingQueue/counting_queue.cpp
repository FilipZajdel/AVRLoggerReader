#include "counting_queue.hpp"

CountingQueue::CountingQueue(int MaxCount) : MaxCount(MaxCount){
    CountTimes = 0; 
} 

string CountingQueue::Front(){

    std::lock_guard <mutex> LockGuard(*Mutex);
    
    if(CountTimes == MaxCount){
        Queue.pop();
        CountTimes = 0;
    } else {
        CountTimes++;
    }

    return Queue.front();
}
