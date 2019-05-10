#include "CountingQueueTest.hpp"
#include "../../CountingQueue/counting_queue.hpp"

#include "../tests.hpp"

#include <vector>
#include <string>
#include <thread>
#include <functional>

using std::vector;
using std::string;
using std::thread;

void TestOfCountTo2(){
    CountingQueue CQueue{2};

    vector <string> TestStrings {"Counting", "Queue"};
    CQueue.Push(TestStrings[0]);
    CQueue.Push(TestStrings[1]); 

    vector <string> ReturnedFirstString{CQueue.Front(), CQueue.Front()};
    vector <string> ReturnedSecondString{CQueue.Front(), CQueue.Front()};

    TEST_IF(ReturnedFirstString[0] == TestStrings[0] && ReturnedFirstString[1] == TestStrings[0]
            && ReturnedSecondString[0] == TestStrings[1] && ReturnedSecondString[1] == TestStrings[1]);

}

void CountingQueueTest(){

    PRINT_HEADER;
    TestOfCountTo2();

}
