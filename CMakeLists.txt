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


    find_package(MPI)
    if (MPI_FOUND)
        add_executable(sgr_test_mpi src/sgr_mpi.cpp)
        target_compile_definitions(sgr_test_mpi PUBLIC -DSGR_ENABLE_MPI)
        target_link_libraries(sgr_test_mpi PUBLIC sgr MPI::MPI_CXX)
    else()
        add_executable(sgr_test_mpi src/sgr_mpi.cpp)
        target_link_libraries(sgr_test_mpi sgr)
    endif()
endif()

