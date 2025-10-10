cmake_minimum_required(VERSION 3.12)

add_library(sr_lib STATIC SR.inl)
target_include_directories(sr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})