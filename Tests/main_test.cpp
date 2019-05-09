#include "ArgumentParserTest/ArgumentParserTest.hpp"
#include "ConfiguratorTest/ConfiguratorTest.hpp"
#include "LogQueueTest/LogQueueTest.hpp"
#include "CsvWriterTest/CsvWriterTest.hpp"

int main(){

    ArgumentParserTest();
    ConfiguratorTest();
    LogQueueTest();
    CsvWriterTest();

    return 0;
}