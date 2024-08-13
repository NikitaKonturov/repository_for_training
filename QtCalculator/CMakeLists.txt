
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MyProject)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем путь к Qt6, если необходимо
# set(CMAKE_PREFIX_PATH "/path/to/Qt6")

# Добавляем поддиректорию с библиотекой Calculator
add_subdirectory(src/Calculator)

# Указываем, что main.cpp является частью исполняемого файла
add_executable(Calculator src/main.cpp)

# Связываем исполняемый файл с библиотекой CalculatorLib
target_link_libraries(Calculator CalculatorClass)