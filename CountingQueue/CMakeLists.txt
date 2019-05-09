set(CMAKE_CXX_COMPILER g++)

set(CountingQueue_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

add_library(counting_queuelib counting_queue.cpp)