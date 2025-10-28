cmake_minimum_required(VERSION 3.12)

add_library(lsfr_lib STATIC)
target_sources(lsfr_lib PRIVATE LSFR.inl)
set_source_files_properties(LSFR.inl PROPERTIES LANGUAGE CXX)
target_include_directories(lsfr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})