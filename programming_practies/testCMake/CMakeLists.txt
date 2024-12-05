cmake_minimum_required(VERSION 3.20)

project(testProject)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/file)

set(SOURCES src/main.cpp src/file/file.cpp)



add_executable(testProjectExe ${SOURCES})
