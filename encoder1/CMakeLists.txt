cmake_minimum_required(VERSION 3.10)
project(encoder1_project)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(encoder1_project main.cpp)
add_subdirectory("LSFR" "${CMAKE_BINARY_DIR}/LSFR")
add_subdirectory("SR" "${CMAKE_BINARY_DIR}/SR")


target_link_libraries(encoder1_project PUBLIC lsfr_lib)
target_link_libraries(encoder1_project PUBLIC sr_lib)
