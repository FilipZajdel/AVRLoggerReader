#include "counting_queue.hpp"
#include <iostream>

CountingQueue::CountingQueue(int MaxCount) : MaxCount(MaxCount) {
  CountTimes = 0;
}

string CountingQueue::Front() {
  std::lock_guard<mutex> LockGuard(*Mutex);

  string DataFront = "";

  if (CountTimes >= MaxCount) {
    if (!Queue.empty()) {
      Queue.pop();
      DataFront = !Queue.empty() ? Queue.front() : "";
    }
    CountTimes = 0;
  } else {
    CountTimes++;
    DataFront = !Queue.empty() ? Queue.front() : "";
  }

  return DataFront;
}

bool CountingQueue::IsEmpty() const {
  if (CountTimes < MaxCount) {
    std::cout << CountTimes << "\n";
    std::cout << "size" << Queue.size() << "\n";
    return LogStringQueue::IsEmpty();
  } else {
    std::cout << CountTimes << "\n";
    std::cout << "size" << Queue.size() << "\n";
    return (Queue.size() < 2);
  }
}