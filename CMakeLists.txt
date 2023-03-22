cmake_minimum_required(VERSION 3.18)
project(sgr)

add_library(sgr INTERFACE)
target_include_directories(sgr INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(
    DIRECTORY include/
    DESTINATION include)

if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    add_executable(sgr_test src/sgr.cpp)
    target_link_libraries(sgr_test sgr)
endif()

