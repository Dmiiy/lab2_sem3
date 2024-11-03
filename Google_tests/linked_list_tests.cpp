#include <cstdlib>

#include "../include/sequence/ArraySequence.h"
#include "../include/sequence/DynamicArray.h"
#include "lib/googletest/include/gtest/gtest.h"

TEST(DynamicArray, basic_operations) {
    // Создаём массив на 3 элемента
    DynamicArray<int> array(3);
    ArraySequence<int> da(array);
    ASSERT_EQ(3, da.getLength());  // Проверяем что размер 3
    try {
        da.get(0);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Element with index 0 not defined", ex.what());
    }
    try {
        da.get(2);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Element with index 2 not defined", ex.what());
    }
    // Задаём значение всех элементов
    da[0] = 11;
    da[1] = 22;
    da[2] = 33;
    // Проверяем значение всех элементов массива
    ASSERT_EQ(11, da.get(0));
    ASSERT_EQ(22, da.get(1));
    ASSERT_EQ(33, da.get(2));
    // Обращение по индексу через оператор
    ASSERT_EQ(11, da[0]);
    ASSERT_EQ(22, da[1]);
    ASSERT_EQ(33, da[2]);
    // Проверяем что на отрицательный индекс генерируется исключение для операции get
    try {
        da.get(-1);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -1 out of range 0..2", ex.what());
    }
    // Проверяем что на отрицательный индекс генерируется исключение для операции set
    try {
        da[-1] = 101;
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -1 out of range 0..2", ex.what());
    }
    // Слишком большой индекс - за границами массива => тоже исключение
    try {
        da.get(10);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index 10 out of range 0..2", ex.what());
    }
    try {
        int x = da[11];
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index 11 out of range 0..2", ex.what());
    }
    // Меняем значения по индексу
    da[0] = 101;
    ASSERT_EQ(3, da.getLength());
    ASSERT_EQ(101, da[0]);
    ASSERT_EQ(22, da[1]);
    ASSERT_EQ(33, da[2]);
    // Вставка элемента
    da.insertAt(1, 0);
    ASSERT_EQ(4, da.getLength());
    ASSERT_EQ(1, da[0]);
    ASSERT_EQ(101, da[1]);
    ASSERT_EQ(22, da[2]);
    ASSERT_EQ(33, da[3]);
    // Перегрузка операторов
    da[0] = 2 * da[1] + da[2];             // Более наглядна
    // чем такая
}
TEST(DynamicArray, undefined_elements) {
    DynamicArray<int> da(4);
    try {
        int x = da.get(0);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Element with index 0 not defined", ex.what());
    }
    try {
        int x = da.get(2);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Element with index 2 not defined", ex.what());
    }
    try {
        int x = da.get(-1);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index -1 out of range 0..3", ex.what());
    }
    try {
        int x = da.get(11);
        FAIL() << "Should be IndexOutOfRange";
    } catch (IndexOutOfRange &ex) {
        ASSERT_STREQ("Index 11 out of range 0..3", ex.what());
    }
}



TEST(ArraySequence, removeAt) {
    int data[] = {11, 22, 33};
    ArraySequence<int> da(data, _countof(data));
    da.removeAt(1);
    ASSERT_EQ(2, da.getLength());
    ASSERT_EQ(11, da[0]);
    ASSERT_EQ(33, da[1]);
    da.removeAt(1);
    ASSERT_EQ(1, da.getLength());
    ASSERT_EQ(11, da[0]);
    da.removeAt(0);
    ASSERT_EQ(0, da.getLength());
}

TEST(DynamicArray, resize) {
    DynamicArray<int> da(0);
    ASSERT_EQ(0, da.getSize());  // Проверяем что размер 0
    for (int size = 1; size <= 10; size++) {
        da.resize(size);
        ASSERT_EQ(size, da.getSize());  // Проверяем размер
    }
}

TEST(DynamicArray, array_initialization) {
    // Инициализация динамического массива из массива значений
    int data[] = {111, 222};
    DynamicArray<int> da(data, _countof(data));
    ASSERT_EQ(_countof(data), da.getSize());
    da.set(0, 111);
    da.set(1, 222);
    ASSERT_EQ(111, da.get(0));
    ASSERT_EQ(222, da.get(1));

    // Копирующий конструктор
    DynamicArray<int> d2(da);
    ASSERT_EQ(da.getSize(), d2.getSize());
    ASSERT_EQ(111, d2.get(0));
    ASSERT_EQ(222, d2.get(1));

    // Уменьшаем размер
    d2.resize(1);
    ASSERT_EQ(1, d2.getSize());
    ASSERT_EQ(111, d2.get(0));

    // Увеличиваем размер
    d2.resize(3);
    ASSERT_EQ(3, d2.getSize());
    ASSERT_EQ(111, d2.get(0));
    d2.set(1, 221);
    d2.set(2, 331);
    ASSERT_EQ(221, d2.get(1));
    ASSERT_EQ(331, d2.get(2));
}
TEST(ArraySequence, constructor) {
    Sequence<int> *s = new ArraySequence<int>();
    ASSERT_EQ(0, s->getLength());
    for (int x = 1; x <= 10; x++) {
        s->append(x);
        ASSERT_EQ(x, s->getLength());
        ASSERT_EQ(x, s->getLast());
    }
    delete s;
}

TEST(ArraySequence, ArraySequence_Append_Prepend_element) {
    int data[] = {111, 222};
    Sequence<int> *s = new ArraySequence<int>(data, _countof(data));  // Список целых чисел
    ASSERT_EQ(2, s->getLength());
    ASSERT_EQ(111, s->get(0));
    ASSERT_EQ(222, s->get(1));
    ASSERT_EQ(111, s->getFirst());
    ASSERT_EQ(222, s->getLast());
    s->append(333);
    ASSERT_EQ(3, s->getLength());
    ASSERT_EQ(333, s->get(2));
    s->prepend(10);
    ASSERT_EQ(4, s->getLength());
    ASSERT_EQ(10, s->get(0));
    ASSERT_EQ(111, s->get(1));
    ASSERT_EQ(222, s->get(2));
    ASSERT_EQ(333, s->get(3));
    delete s;
}

// Создание второго динамического массива как копии первого
TEST(ArraySequence, create_from_DynamicArray) {
    int data[] = {123, 234, 345};
    DynamicArray<int> da(data, _countof(data));     // Список целых чисел
    Sequence<int> *s = new ArraySequence<int>(da);  // Список целых чисел
    ASSERT_EQ(3, s->getLength());
    ASSERT_EQ(data[0], s->get(0));
    ASSERT_EQ(data[1], s->get(1));
    ASSERT_EQ(data[2], s->get(2));
    ASSERT_EQ(data[0], s->getFirst());
    ASSERT_EQ(data[2], s->getLast());
    s->append(333);
    ASSERT_EQ(4, s->getLength());
    ASSERT_EQ(333, s->getLast());
    s->prepend(10);
    ASSERT_EQ(5, s->getLength());
    // 123, 234, 345
    ASSERT_EQ(10, s->get(0));
    ASSERT_EQ(data[0], s->get(1));
    ASSERT_EQ(data[1], s->get(2));
    ASSERT_EQ(data[2], s->get(3));
    ASSERT_EQ(333, s->get(4));
    Sequence<int> *sub = s->getSubsequence(1, 3);
    ASSERT_EQ(3, sub->getLength());
    ASSERT_EQ(123, sub->get(0));
    ASSERT_EQ(234, sub->get(1));
    ASSERT_EQ(345, sub->get(2));
    // Вставим ещё один элемент посередине
    sub->insertAt(4444, 1);
    ASSERT_EQ(4, sub->getLength());
    ASSERT_EQ(123, sub->get(0));
    ASSERT_EQ(4444, sub->get(1));
    ASSERT_EQ(234, sub->get(2));
    ASSERT_EQ(345, sub->get(3));
    delete s;
    delete sub;
}

// Сцепление двух списков
TEST(ArraySequence, concat) {
    // Первая последовательность
    int data1[] = {11, 22};
    DynamicArray<int> da1(data1, _countof(data1));    // Список целых чисел
    Sequence<int> *s1 = new ArraySequence<int>(da1);  // Список целых чисел
    // Вторая последовательность
    int data2[] = {33};
    DynamicArray<int> da2(data2, _countof(data2));    // Список целых чисел
    Sequence<int> *s2 = new ArraySequence<int>(da2);  // Список целых чисел
    // Сцепляем два списка
    Sequence<int> *res = s1->concat(s2);
    ASSERT_EQ(3, res->getLength());
    ASSERT_EQ(11, res->get(0));
    ASSERT_EQ(22, res->get(1));
    ASSERT_EQ(33, res->get(2));
    delete s1;
    delete s2;
    delete res;
}

TEST(ArraySequence, findSubsequence) {
    int data[] = {11, 22, 33, 44, 55};
    DynamicArray<int> da(data, _countof(data));
    Sequence<int> *main = new ArraySequence<int>(da);

    {
        int d[] = {11, 22};
        Sequence<int> *sub1 = new ArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(0, main->findSubsequence(*sub1));
        delete sub1;
    }
    {
        int d[] = {22, 33};
        Sequence<int> *sub = new ArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(1, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {33, 44, 55};
        Sequence<int> *sub = new ArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(2, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {44, 55};
        Sequence<int> *sub = new ArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(3, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {55};
        Sequence<int> *sub = new ArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(4, main->findSubsequence(*sub));
        delete sub;
    }
    {
        int d[] = {33, 55};
        Sequence<int> *sub = new ArraySequence<int>(DynamicArray<int>(d, _countof(d)));
        ASSERT_EQ(-1, main->findSubsequence(*sub));
        delete sub;
    }

    delete main;
}