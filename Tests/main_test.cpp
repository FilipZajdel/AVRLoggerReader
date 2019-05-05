#include "ArgumentParserTest/ArgumentParserTest.hpp"
#include "ConfiguratorTest/ConfiguratorTest.hpp"
#include "LogQueueTest/LogQueueTest.hpp"
#include "relog_app.hpp"

int main(){

    ArgumentParserTest();
    ConfiguratorTest();
    LogQueueTest();

    return 0;
}