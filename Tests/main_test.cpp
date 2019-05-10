#include "ArgumentParserTest/ArgumentParserTest.hpp"
#include "ConfiguratorTest/ConfiguratorTest.hpp"
#include "LogQueueTest/LogQueueTest.hpp"
#include "CsvWriterTest/CsvWriterTest.hpp"
#include "CountingQueueTest/CountingQueueTest.hpp"

int main(){

    ArgumentParserTest();
    ConfiguratorTest();
    LogQueueTest();
    CsvWriterTest();
    CountingQueueTest();

    return 0;
}