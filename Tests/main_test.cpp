#include "ArgumentParserTest/ArgumentParserTest.hpp"
#include "AppConfiguratorTest/AppConfiguratorTest.hpp"
#include "LogQueueTest/LogQueueTest.hpp"
#include "CsvWriterTest/CsvWriterTest.hpp"

int main(){

    ArgumentParserTest();
    ConfiguratorTest();
    LogQueueTest();
    CsvWriterTest();

    return 0;
}