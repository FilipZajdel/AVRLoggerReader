set(CMAKE_CXX_COMPILER g++)

set(LogQueue_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

add_library(log_queuelib LogQueue.cpp)