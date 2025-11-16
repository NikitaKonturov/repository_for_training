cmake_minimum_required(VERSION 3.12)
project(A5_1_project)

add_subdirectory(LSFR)

add_executable(encoder main.cpp)
target_link_libraries(encoder lsfr_lib)

target_include_directories(encoder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})