#ifndef COUNTINGSORTER_H
#define COUNTINGSORTER_H

#include <map>
#include <functional>
#include "ISorter.h"

template <typename T, typename Comparator = std::function<bool(const T&, const T&)>>
class CountingSorter : public ISorter<T> {
private:
    Comparator comparator;

public:
    CountingSorter(Comparator comp) : comparator(comp) {}

    void sort(ArraySequence<T>* sequence) override {
        if (!sequence || sequence->getLength() == 0) {
            throw SortExc("Sequence is null");
        };

        std::map<T, int, Comparator> countMap(comparator);

        // Подсчет количества вхождений каждого элемента
        for (int i = 0; i < sequence->getLength(); ++i) {
            countMap[(*sequence)[i]]++;
        }

        int index = 0;

        for (const auto& pair : countMap) {
            for (int j = 0; j < pair.second; ++j) {
                (*sequence)[index++] = pair.first;
            }
        }
    }
};

#endif // COUNTINGSORTER_H
