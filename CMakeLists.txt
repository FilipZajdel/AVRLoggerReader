cmake_minimum_required(VERSION 3.1)

project(ReLog)

# Application Development
set(MAIN_FILE "MainApp/Main.cpp")

# Pass the argument using command line like: cmake .. -DBUILD_TESTS=ON
option(BUILD_TESTS “build-unit-tests” OFF)

set(target_name relog)
set(test_target_name relog_test)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-std=c++17 -pthread")

add_subdirectory("SerialPort")
add_subdirectory("TcpClient")
add_subdirectory("RelogApp")
add_subdirectory("ArgumentParser")
add_subdirectory("AppConfigurator")
add_subdirectory("LogQueue")
add_subdirectory("CsvWriter")
add_subdirectory("Timestamp")

include_directories(${SerialPort_INCLUDE} ${Configurator_INCLUDE} ${TcpHost_INCLUDE} ${ArgumentParser_INCLUDE} ${RelogApp_INCLUDE} ${LogQueue_INCLUDE} ${CsvWriter_INCLUDE} ${Timestamp_INCLUDE})

find_package(Boost 1.69.0 REQUIRED COMPONENTS thread program_options)

if(BUILD_TESTS)
    # Build Tests
    message("Building Tests")
    add_subdirectory(Tests)
    add_executable(${test_target_name} ${TEST_MAIN} ${TESTS_SOURCES})

    if (Boost_FOUND)
        message("Boost found")
        target_link_libraries(${test_target_name} serialportlib tcpclientlib relog_applib log_queuelib configuratorlib argument_parserlib csvwriterlib timestamplib ${Boost_LIBRARIES})
    else()
        message("Boost couldn't be found")
    endif()
else()  
    # Build Application
    message("Building Application")
    add_executable(${target_name} ${MAIN_FILE})

    if (Boost_FOUND)
        message("Boost found")
        target_link_libraries(${target_name} relog_applib serialportlib tcpclientlib log_queuelib configuratorlib argument_parserlib csvwriterlib timestamplib ${Boost_LIBRARIES})
    else()
        message("Boost couldn't be found")
    endif()
endif()
