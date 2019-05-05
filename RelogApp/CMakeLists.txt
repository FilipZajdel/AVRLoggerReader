set(CMAKE_CXX_COMPILER g++)

set(RelogApp_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

set(RelogApp_SOURCES LogQueue/log_queue.cpp
                     MainLogic/main_logic.cpp)

add_library(relog_applib relog_app.cpp ${RelogApp_SOURCES})