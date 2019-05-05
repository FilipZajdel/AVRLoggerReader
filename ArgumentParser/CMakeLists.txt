set(CMAKE_CXX_COMPILER g++)

set(ArgumentParser_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

find_package(Boost 1.69.0 REQUIRED)

include_directories(${Boost_INCLUDE})

add_library(argument_parserlib argument_parser.cpp)