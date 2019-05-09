set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(TESTS_SOURCES  ${CURRENT_PATH}/ArgumentParserTest/ArgumentParserTest.cpp 
                   ${CURRENT_PATH}/ConfiguratorTest/ConfiguratorTest.cpp
                   ${CURRENT_PATH}/LogQueueTest/LogQueueTest.cpp
                   ${CURRENT_PATH}/CsvWriterTest/CsvWriterTest.cpp
                   PARENT_SCOPE)

set(TEST_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp PARENT_SCOPE)