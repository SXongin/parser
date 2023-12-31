cmake_minimum_required(VERSION 3.16)
project(test_parser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/../install)

find_package(MyParser REQUIRED)

add_executable(
  test_parser
  test_token.cpp
)

target_link_libraries(
  test_parser
  PRIVATE
    MyParser::parser
)
