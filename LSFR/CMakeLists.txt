cmake_minimum_required(VERSION 3.10)
project(project_name)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(project_name src/main.cpp)
add_subdirectory("src/LSFR" "${CMAKE_BINARY_DIR}/LSFR")

target_link_libraries(project_name PUBLIC lsfr_lib)



