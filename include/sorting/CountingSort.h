#ifndef COUNTINGSORTER_H
#define COUNTINGSORTER_H

#include <functional>
#include "ISorter.h"
#include "HelpClass.h"  // не забудьте импортировать HelpClass

template <typename T>
class CountingSorter : public ISorter<T> {
private:
    std::function<bool(const T&, const T&)> comparator;
    static HelpClass helpClass;

public:
    // Конструктор принимает компаратор, по умолчанию используется по возрастанию
    CountingSorter(std::function<bool(const T&, const T&)> comp = helpClass.ascending)
            : comparator(comp) {}

    void sort(ArraySequence<T> *sequence) override {
        if (sequence->getLength() == 0) return;

        T maxVal = findMax(sequence);
        T minVal = findMin(sequence);
        int range = maxVal - minVal + 1;

        ArraySequence<int> count;  // Используем ArraySequence для хранения количества элементов

        int n = sequence->getLength();

        // Инициализация счетчика
        for (int i = 0; i < range; ++i) {
            count.append(0);
        }

        // Подсчет вхождений
        for (int i = 0; i < n; ++i) {
            count[(*sequence)[i] - minVal]++;
        }

        // Сортировка по подсчету с учетом порядка компаратора
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

private:
    T findMax(ArraySequence<T> *sequence) {
        T maxVal = (*sequence)[0];
        for (int i = 1; i < sequence->getLength(); ++i) {
            if (comparator(maxVal, (*sequence)[i])) {
                maxVal = (*sequence)[i];
            }
        }
        return maxVal;
    }

    T findMin(ArraySequence<T> *sequence) {
        T minVal = (*sequence)[0];
        for (int i = 1; i < sequence->getLength(); ++i) {
            if (comparator((*sequence)[i], minVal)) {
                minVal = (*sequence)[i];
            }
        }
        return minVal;
    }
};

// Определяем статический член класса
template <typename T>
HelpClass CountingSorter<T>::helpClass;

#endif // COUNTINGSORTER_H
