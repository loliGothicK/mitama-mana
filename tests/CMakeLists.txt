cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(mana-test VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic-errors")

add_library(test_main ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

find_package(Boost 1.70.0 REQUIRED)

include_directories(
  PUBLIC ${Boost_INCLUDE_DIRS}
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/catch2/single_include
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include
)

enable_testing()

# Listing test targets
file(GLOB targets RELATIVE ${CMAKE_CURRENT_LIST_DIR} *-tests/*.cpp)
foreach(target ${targets})
  get_filename_component(test_name ${target} DIRECTORY)
  message(${test_name})
  if(NOT TARGET ${test_name})
    file(GLOB source RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${test_name}/*.cpp)
    add_executable(${test_name} ${source})
    target_link_libraries(${test_name} test_main ${OpenCASCADE_LIBRARIES})
    add_test(NAME ${test_name} COMMAND ${test_name})
  endif()
endforeach()
