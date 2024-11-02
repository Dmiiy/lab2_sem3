cmake_minimum_required(VERSION 3.27)
project(lab2_sem3)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(lab2_sem3 main.cpp
        include/sorting/QuickSorter.h
        "include/sorting/BubbleSort.h"
        include/sorting/ShakerSort.h
        include/sorting/InsertionSort.h
        "include/sorting/SelectionSort.h"
        include/sorting/CountingSort.h
        include/sorting/BinaryInsertionSort.h
        include/sorting/MergeSort.h
        include/sorting/HeapSort.h
        include/sorting/ShellSort.h
        include/sorting/ShellSortGap.h
        include/sorting/BatcherSort.h
        include/sorting/HelpClass.h
        "include/animation/BatcherSortWidget.h"
        include/animation/BubbleSortWidget.h
        include/animation/BinaryInsertionSortWidget.h
        include/animation/CountingSortWidget.h
        include/animation/HeapSortWidget.h
        include/animation/InsertionSortWidget.h
        include/animation/MergeSortWidget.h
        include/animation/QuickSortWidget.h
        include/animation/SelectionSortWidget.h
        include/animation/ShakerSortWidget.h
        include/animation/ShellSortWidget.h
        include/animation/BatcherSortWidget.h
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
