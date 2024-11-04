#ifndef COUNTINGSORTER_H
#define COUNTINGSORTER_H

#include <functional>
#include <stdexcept>
#include "ISorter.h"
#include "HelpClass.h"

template <typename T>
class CountingSorter : public ISorter<T> {
private:
    std::function<bool(const T&, const T&)> comparator;
    static HelpClass helpClass;

public:
    CountingSorter(std::function<bool(const T&, const T&)> comp = helpClass.ascending)
            : comparator(comp) {}

    void sort(ArraySequence<T> *sequence) override {
        if (sequence->getLength() == 0) return;

        // Проверяем, что тип T является целочисленным
        if (!std::is_integral<T>::value) {
            throw std::invalid_argument("CountingSort работает только с целочисленными типами.");
        }

        // Находим минимальное и максимальное значение в одном проходе
        T minVal = (*sequence)[0];
        T maxVal = (*sequence)[0];
        for (int i = 1; i < sequence->getLength(); ++i) {
            if ((*sequence)[i] < minVal) minVal = (*sequence)[i];
            if ((*sequence)[i] > maxVal) maxVal = (*sequence)[i];
        }

        int range = maxVal - minVal + 1;
        ArraySequence<int> count;  // Создаем пустой ArraySequence для хранения количества элементов

        // Инициализируем массив count нулями
        for (int i = 0; i < range; ++i) {
            count.append(0);
        }

        int n = sequence->getLength();

        // Подсчёт вхождений каждого элемента
        for (int i = 0; i < n; ++i) {
            count[(*sequence)[i] - minVal]++;
        }

        // Заполняем исходную последовательность по возрастанию или убыванию
        int index = 0;
        if (comparator(minVal, maxVal)) {
            // Сортировка по возрастанию
            for (int i = 0; i < range; ++i) {
                while (count[i]-- > 0) {
                    (*sequence)[index++] = i + minVal;
                }
            }
        } else {
            // Сортировка по убыванию
            for (int i = range - 1; i >= 0; --i) {
                while (count[i]-- > 0) {
                    (*sequence)[index++] = i + minVal;
                }
            }
        }
    }
};

template <typename T>
HelpClass CountingSorter<T>::helpClass;

#endif // COUNTINGSORTER_H
