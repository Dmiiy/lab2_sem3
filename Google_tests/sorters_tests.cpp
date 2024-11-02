#include <gtest/gtest.h>
#include "../include\sorting\BubbleSort.h"
#include "../include\sorting\SelectionSort.h"
#include "../include\sorting\CountingSort.h"
#include "../include\sorting\InsertionSort.h"
#include "../include\sorting\MergeSort.h"
#include "../include\sorting\QuickSorter.h"
#include "../include/sorting/ShakerSort.h"
#include "../include/sorting/BinaryInsertionSort.h"
#include "../include/sorting/HeapSort.h"
#include "../include/sorting/ShellSort.h"
#include "../include/sorting/BatcherSort.h"
#include "../include/sorting/ShellSortGap.h"

TEST(BubbleSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(3);
    list.append(1);
    list.append(4);
    list.append(1);
    list.append(5);

    BubbleSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 1);
    ASSERT_EQ(list.get(2), 3);
    ASSERT_EQ(list.get(3), 4);
    ASSERT_EQ(list.get(4), 5);
}

TEST(BubbleSort, EmptyList) {
    LinkedListSequence<int> list;
    BubbleSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.getLength(), 0); // Проверяем, что длина списка не изменилась
}

TEST(BubbleSort, SingleElement) {
    LinkedListSequence<int> list;
    list.append(42);

    BubbleSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 42);
    ASSERT_EQ(list.getLength(), 1);
}

TEST(ShakerSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(9);
    list.append(7);
    list.append(5);
    list.append(3);
    list.append(1);

    ShakerSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 3);
    ASSERT_EQ(list.get(2), 5);
    ASSERT_EQ(list.get(3), 7);
    ASSERT_EQ(list.get(4), 9);
}

TEST(ShakerSort, ReverseSort) {
    LinkedListSequence<int> list;
    list.append(1);
    list.append(3);
    list.append(5);
    list.append(7);
    list.append(9);

    ShakerSorter<int> sorter([](const int &a, const int &b) { return a > b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 9);
    ASSERT_EQ(list.get(1), 7);
    ASSERT_EQ(list.get(2), 5);
    ASSERT_EQ(list.get(3), 3);
    ASSERT_EQ(list.get(4), 1);
}
TEST(InsertionSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(10);
    list.append(2);
    list.append(8);
    list.append(4);
    list.append(6);

    InsertionSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 2);
    ASSERT_EQ(list.get(1), 4);
    ASSERT_EQ(list.get(2), 6);
    ASSERT_EQ(list.get(3), 8);
    ASSERT_EQ(list.get(4), 10);
}

TEST(SelectionSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(7);
    list.append(2);
    list.append(5);
    list.append(3);
    list.append(1);

    SelectionSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 2);
    ASSERT_EQ(list.get(2), 3);
    ASSERT_EQ(list.get(3), 5);
    ASSERT_EQ(list.get(4), 7);
}

TEST(MergeSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(8);
    list.append(4);
    list.append(5);
    list.append(1);
    list.append(7);

    MergeSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 4);
    ASSERT_EQ(list.get(2), 5);
    ASSERT_EQ(list.get(3), 7);
    ASSERT_EQ(list.get(4), 8);
}

TEST(MergeSort, AlreadySorted) {
    LinkedListSequence<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    MergeSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 2);
    ASSERT_EQ(list.get(2), 3);
    ASSERT_EQ(list.get(3), 4);
    ASSERT_EQ(list.get(4), 5);
}
TEST(CountingSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(5);
    list.append(1);
    list.append(4);
    list.append(2);
    list.append(3);

    CountingSorter<int> sorter;
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 2);
    ASSERT_EQ(list.get(2), 3);
    ASSERT_EQ(list.get(3), 4);
    ASSERT_EQ(list.get(4), 5);
}
TEST(BinaryInsertionSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(7);
    list.append(3);
    list.append(5);
    list.append(2);
    list.append(9);

    BinaryInsertionSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 2);
    ASSERT_EQ(list.get(1), 3);
    ASSERT_EQ(list.get(2), 5);
    ASSERT_EQ(list.get(3), 7);
    ASSERT_EQ(list.get(4), 9);
}
TEST(QuickSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(9);
    list.append(4);
    list.append(6);
    list.append(3);
    list.append(1);

    QuickSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 3);
    ASSERT_EQ(list.get(2), 4);
    ASSERT_EQ(list.get(3), 6);
    ASSERT_EQ(list.get(4), 9);
}

TEST(HeapSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(4);
    list.append(10);
    list.append(3);
    list.append(5);
    list.append(1);

    HeapSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 3);
    ASSERT_EQ(list.get(2), 4);
    ASSERT_EQ(list.get(3), 5);
    ASSERT_EQ(list.get(4), 10);
}

TEST(HeapSort, EmptyList) {
    LinkedListSequence<int> list;
    HeapSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.getLength(), 0); // Проверяем, что длина списка не изменилась
}

TEST(HeapSort, SingleElement) {
    LinkedListSequence<int> list;
    list.append(42);

    HeapSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 42);
    ASSERT_EQ(list.getLength(), 1);
}
TEST(ShellSort, BasicSort) {
    LinkedListSequence<int> list;
    list.append(8);
    list.append(5);
    list.append(2);
    list.append(6);
    list.append(3);

    ShellSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 2);
    ASSERT_EQ(list.get(1), 3);
    ASSERT_EQ(list.get(2), 5);
    ASSERT_EQ(list.get(3), 6);
    ASSERT_EQ(list.get(4), 8);
}

TEST(ShellSort, AlreadySorted) {
    LinkedListSequence<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    ShellSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 2);
    ASSERT_EQ(list.get(2), 3);
    ASSERT_EQ(list.get(3), 4);
    ASSERT_EQ(list.get(4), 5);
}

TEST(ShellSort, EmptyList) {
    LinkedListSequence<int> list;
    ShellSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.getLength(), 0); // Проверяем, что длина списка не изменилась
}
//TEST(ShellSortWithGap, BasicSort) {
//    LinkedListSequence<int> list;
//    list.append(12);
//    list.append(11);
//    list.append(13);
//    list.append(5);
//    list.append(6);
//
//    LinkedListSequence<int> gaps;
//    gaps.append(5);
//    gaps.append(3);
//    gaps.append(1);
//
//    ShellSorterWithGap<int> sorter(gaps, [](const int &a, const int &b) { return a < b; });
//    sorter.sort(&list);
//
//    ASSERT_EQ(list.get(0), 5);
//    ASSERT_EQ(list.get(1), 6);
//    ASSERT_EQ(list.get(2), 11);
//    ASSERT_EQ(list.get(3), 12);
//    ASSERT_EQ(list.get(4), 13);
//}

//TEST(ShellSortWithGap, EmptyList) {
//    LinkedListSequence<int> list;
//    LinkedListSequence<int> gaps;
//    gaps.append(1);// Смещение не имеет значения для пустого списка
//    ShellSorterWithGap<int> sorter(gaps, [](const int &a, const int &b) { return a < b; });
//    sorter.sort(&list);
//
//    ASSERT_EQ(list.getLength(), 0); // Проверяем, что длина списка не изменилась
//}
//
//TEST(BatcherSort, BasicSort) {
//    LinkedListSequence<int> list;
//    list.append(6);
//    list.append(3);
//    list.append(8);
//    list.append(1);
//    list.append(5);
//
//    BatcherSorter<int> sorter([](const int &a, const int &b) { return a < b; });
//    sorter.sort(&list);
//
//    ASSERT_EQ(list.get(0), 1);
//    ASSERT_EQ(list.get(1), 3);
//    ASSERT_EQ(list.get(2), 5);
//    ASSERT_EQ(list.get(3), 6);
//    ASSERT_EQ(list.get(4), 8);
//}

TEST(BatcherSort, AlreadySorted) {
    LinkedListSequence<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    BatcherSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.get(0), 1);
    ASSERT_EQ(list.get(1), 2);
    ASSERT_EQ(list.get(2), 3);
    ASSERT_EQ(list.get(3), 4);
    ASSERT_EQ(list.get(4), 5);
}

TEST(BatcherSort, EmptyList) {
    LinkedListSequence<int> list;
    BatcherSorter<int> sorter([](const int &a, const int &b) { return a < b; });
    sorter.sort(&list);

    ASSERT_EQ(list.getLength(), 0); // Проверяем, что длина списка не изменилась
}