#include "log_queue.hpp"
#include <thread>

LogStringQueue::LogStringQueue(){
    Mutex = new mutex{};
}

void LogStringQueue::Push(string NewString){
    std::lock_guard <mutex> LockGuard(*Mutex);
    Queue.push(NewString);
}

int LogStringQueue::Size() const{
    std::lock_guard <mutex> LockGuard(*Mutex);
    return Queue.size();
}

string LogStringQueue::Front() const{
    std::lock_guard <mutex> LockGuard(*Mutex);
    return Queue.front();
}

void LogStringQueue::ClearFront(){
    std::lock_guard <mutex> LockGuard(*Mutex);
    Queue.pop();
}

bool LogStringQueue::IsEmpty() const {
    std::lock_guard<std::mutex> LockGuard{*this->Mutex};
    return Queue.empty();
}