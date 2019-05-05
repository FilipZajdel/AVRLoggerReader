#include "LogQueueTest.hpp"
#include "LogQueue/log_queue.hpp"

#include "../tests.hpp"

#include <vector>
#include <string>
#include <thread>
#include <functional>

using std::vector;
using std::string;
using std::thread;

void Insert4ItemsAndCheckSize(){
    LogStringQueue logStringQueue{};
    vector<string> TestStrings {"this", "is", "LogStringQueue", "Test"};

    for(string TestString : TestStrings){
        logStringQueue.Push(TestString);
    }

    TEST_IF(TestStrings.size() == logStringQueue.Size());
}

void InsertEmptyString(){
    LogStringQueue logStringQueue{};
    logStringQueue.Push("");

    TEST_IF(logStringQueue.Front() == "");
}

void SizeDecrementAfterClearingFront(){
    LogStringQueue logStringQueue{};
    logStringQueue.Push("first");
    logStringQueue.Push("second");

    logStringQueue.ClearFront();

    TEST_IF(logStringQueue.Size() == 1);
}

void SecondElementAsFirstAfterClearingFirst(){
    LogStringQueue logStringQueue{};
    logStringQueue.Push("first");
    logStringQueue.Push("second");

    logStringQueue.ClearFront();

    TEST_IF(logStringQueue.Front() == "second");
}

void TaskCheckingEmptyQueue(LogStringQueue &Queue, bool &firstCheck, 
                bool &secondCheck){

    for(int counter = 0; counter < std::numeric_limits<int>::max()/1000; counter++){
        IsEmpty = Queue.IsEmpty();
    }
}

void TaskMakingQueueNotEmpty(LogStringQueue &Queue){

    string veryLongString;
    veryLongString.resize(45000000);
    for(char &ch : veryLongString){
        ch = 't';
    }
    Queue.Push(veryLongString);
}


void TestOfEmptyMethodFromDifferentTasks(){
    
    LogStringQueue Queue{};
    bool IsEmpty;

    thread ThrCheckEmptyQueue{TaskCheckingEmptyQueue, std::ref(Queue), std::ref(IsEmpty)};
    thread ThrMakeQueueNotEmpty{TaskMakingQueueNotEmpty, std::ref(Queue)};

    ThrCheckEmptyQueue.join();
    ThrMakeQueueNotEmpty.join();
    
    TEST_IF(IsEmpty == false);
}

void LogQueueTest(){

    PRINT_HEADER;

    Insert4ItemsAndCheckSize();
    InsertEmptyString();
    SizeDecrementAfterClearingFront();
    SecondElementAsFirstAfterClearingFirst();
    TestOfEmptyMethodFromDifferentTasks();
}
