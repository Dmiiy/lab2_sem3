#ifndef SHELLSORTER_GAP_H
#define SHELLSORTER_GAP_H

#include <functional>
#include "ISorter.h"

template <typename T>
class ShellSorterWithGap : public ISorter<T> {
private:
    std::function<bool(const T&, const T&)> comparator;
    LinkedListSequence<int> gaps;
    static HelpClass helpClass;
public:
    ShellSorterWithGap(LinkedListSequence<int> gapSequence, std::function<bool(const T&, const T&)> comp = helpClass.descending)
            : gaps(gapSequence), comparator(comp) {}

    void sort(LinkedListSequence<T> *sequence) override {
        for (int i = 0; i < gaps.getLength(); i++) {
            int gap = gaps[i];
            // Вставляем элементы в подмассивы, определяемые разницей
            for (int i = gap; i < sequence->getLength(); i++) {
                T temp = (*sequence)[i];
                int j;

                // Сравниваем и перемещаем элементы, чтобы создать отсортированный подмассив
                for (j = i; j >= gap && comparator(temp, (*sequence)[j - gap]); j -= gap)
                    (*sequence)[j] = (*sequence)[j - gap];

                (*sequence)[j] = temp;
            }
        }
    }
};

#endif // SHELLSORTER_GAP_H
