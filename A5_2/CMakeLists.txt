cmake_minimum_required(VERSION 3.12)
project(A5_2_project)

add_subdirectory(encoder)

add_executable(encoder main.cpp)
target_link_libraries(encoder encoder_lib)

target_include_directories(encoder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})