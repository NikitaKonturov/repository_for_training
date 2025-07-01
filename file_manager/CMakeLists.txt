cmake_minimum_required(VERSION 3.10)

project(File_Manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH "/home/ubuntu/Qt/6.5.3/gcc_64")

add_subdirectory(src/FileManagerClass)

qt_add_resources(MY_PROJECT_RESOURCES resources.qrc)

add_executable(File_Manager src/main.cpp)

target_link_libraries(File_Manager FileManagerClass)
