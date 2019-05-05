set(CMAKE_CXX_COMPILER g++)

set(RelogApp_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

include_directories("../LogQueue")
include_directories("../Configurator")
link_directories("../LogQueue")
link_directories("../Configurator")

#target_link_libraries(relog_app.cpp log_queuelib configuratorlib)

add_library(relog_applib relog_app.cpp)