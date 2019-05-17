#include "LogQueueTest.hpp"
#include "../../LogQueue/LogQueue.hpp"

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

    firstCheck= Queue.IsEmpty();

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    secondCheck = Queue.IsEmpty();
}

void TaskMakingQueueNotEmpty(LogStringQueue &Queue){

    string LongString;
    LongString.resize(2500);
    for(char &ch : LongString){
        ch = 't';
    }
    Queue.Push(LongString);
}

/** @brief Checks whether one task returns good check result, whilst another one
 * changes queue size
 */
void TestOfEmptyMethodFromDifferentTasks(){
    
    LogStringQueue Queue{};
    bool firstCheck = false, secondCheck = false;

    thread ThrCheckEmptyQueue{TaskCheckingEmptyQueue, std::ref(Queue), std::ref(firstCheck), std::ref(secondCheck)};
    thread ThrMakeQueueNotEmpty{TaskMakingQueueNotEmpty, std::ref(Queue)};

    ThrCheckEmptyQueue.join();
    ThrMakeQueueNotEmpty.join();
    
    TEST_IF(firstCheck == true && secondCheck == false);
}

void LogQueueTest(){

    PRINT_HEADER;

    Insert4ItemsAndCheckSize();
    InsertEmptyString();
    SizeDecrementAfterClearingFront();
    SecondElementAsFirstAfterClearingFirst();
    TestOfEmptyMethodFromDifferentTasks();
}
