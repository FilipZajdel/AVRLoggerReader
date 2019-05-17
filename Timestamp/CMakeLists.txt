set(CMAKE_CXX_COMPILER g++)

set(Timestamp_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

#find_package(Boost 1.69.0 REQUIRED)

#include_directories(${Boost_INCLUDE})

add_library(timestamplib Timestamp.cpp)