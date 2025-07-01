# Укажите минимально требуемую версию CMake
cmake_minimum_required(VERSION 3.10)

# Найдите компоненты Qt, которые вам нужны (например, Widgets)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

# Добавляем библиотеку CalculatorLib
add_library(FileManagerClass
    FileManagerClass.cpp
)

qt_add_resources(MY_PROJECT_RESOURCES resources.qrc)

# Включаем директории заголовочных файлов Qt
target_include_directories(FileManagerClass PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Связываем библиотеку CalculatorLib с компонентом Qt (например, Qt::Widgets)
target_link_libraries(FileManagerClass Qt6::Widgets)