cmake_minimum_required(VERSION 3.1)
project(SerialHost)

set(target_name SerialHost)
set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_CXX_FLAGS "-I  ~/boost_1_69_0/ -L /usr/lib/ -lpthread")
set(CMAKE_CXX_FLAGS "-std=c++17 -I  ~/boost_1_69_0/ -L /usr/lib/ -lpthread")

add_subdirectory("SerialPort")
add_subdirectory("TcpHost")
include_directories(${SerialPort_INCLUDE} ${TcpHost_INCLUDE})

find_package(Boost 1.69.0 REQUIRED COMPONENTS thread)
set(Boost_ADDITIONAL_VERSIONS "1.69" "1.69.0")

if (Boost_FOUND)
    message(status " Boost found")
else()
    message(status " Boost couldn't be found")
endif()

add_executable(${target_name} "MainApp/serial_copy_v3.cpp")

target_link_libraries(${target_name} serialportlib tcphostlib ${Boost_LIBRARIES})


