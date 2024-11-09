cmake_minimum_required(VERSION 3.27)
project(lab2_sem3)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(lab2_sem3 main.cpp
        SortingTime.h
        MainWindow.h
        SortingStudents.h
        include/sorting/User.h
        include/sorting/SortExc.h
        include/sequence/Statistics.h
        FileSorting.h
)

target_link_libraries(lab2_sem3
        PRIVATE
        Qt6::Core
        Qt6::Widgets
)
add_subdirectory(Google_tests)
include_directories(
        include
)
