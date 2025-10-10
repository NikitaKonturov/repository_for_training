cmake_minimum_required(VERSION 3.12)

add_library(lsfr_lib STATIC LSFR.inl)
target_include_directories(lsfr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})