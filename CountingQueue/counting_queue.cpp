#include "counting_queue.hpp"
#include "../Config/config.hpp"

#include <iostream>

CountingQueue::CountingQueue(int MaxCount) : MaxCount(CountTimes){
} 

string CountingQueue::Front(){

    std::lock_guard <mutex> LockGuard(*Mutex);
    
    if(CountTimes == 0){
        Queue.pop();
        CountTimes = MaxCount;
    } else {
        CountTimes--;
    }

    return Queue.front();
}
