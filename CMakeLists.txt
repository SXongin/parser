cmake_minimum_required(VERSION 3.16)
project(parser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(PARSER_BUILD_TESTS ON)
endif()
add_subdirectory(dependences EXCLUED_FROM_ALL)

add_library(
  parser
  src/token.cpp
  include/parser/lexer.h
  include/parser/scanner.h
  include/parser/token.h
)

target_include_directories(
  parser PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(PARSER_BUILD_TESTS)
add_executable(
  test_parser
  src/test_lexer.cpp
  src/test_scanner.cpp
  src/test_token.cpp
)

target_link_libraries(
  test_parser PRIVATE
  parser
  gtest_main
)
endif() # PARSER_BUILD_TESTS
