cmake_minimum_required(VERSION 3.12)

add_subdirectory(../LSFR ${CMAKE_CURRENT_BINARY_DIR}/LSFR)

add_library(encoder_lib STATIC encoder.cpp)
target_link_libraries(encoder_lib lsfr_lib)

target_include_directories(encoder_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})