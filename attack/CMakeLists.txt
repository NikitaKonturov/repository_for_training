cmake_minimum_required(VERSION 3.12)
project(attack_project)

add_subdirectory(LSFR)

add_executable(attack main.cpp)
target_link_libraries(attack lsfr_lib)

target_include_directories(attack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})