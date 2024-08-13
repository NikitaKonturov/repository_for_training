
# Укажите минимально требуемую версию CMake
cmake_minimum_required(VERSION 3.10)

# Найдите компоненты Qt, которые вам нужны (например, Widgets)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

# Добавляем библиотеку CalculatorLib
add_library(CalculatorClass
    Calculator.cpp
)

# Включаем директории заголовочных файлов Qt
target_include_directories(CalculatorClass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Связываем библиотеку CalculatorLib с компонентом Qt (например, Qt::Widgets)
target_link_libraries(CalculatorClass Qt6::Widgets)