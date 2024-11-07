#ifndef COUNTINGSORTER_H
#define COUNTINGSORTER_H

#include <functional>
#include <stdexcept>
#include <map>
#include "ISorter.h"
#include "HelpClass.h"

template <typename T, typename Comparator = std::function<bool(const T&, const T&)>>
class CountingSorter : public ISorter<T> {
private:
    Comparator comparator;

public:
    CountingSorter(Comparator comp) : comparator(comp) {}

    void sort(ArraySequence<T>* sequence) override {
        if (sequence == nullptr) {
            throw SortExc("Sequence is null");
        }
        if (sequence->getLength() == 0) return;

        std::map<T, int, Comparator> countMap(comparator);

        for (int i = 0; i < sequence->getLength(); ++i) {
            countMap[(*sequence)[i]]++;
        }

        int index = 0;
        if (comparator(countMap.begin()->first, countMap.rbegin()->first)) {
            // Сортировка по возрастанию
            for (const auto& pair : countMap) {
                for (int j = 0; j < pair.second; ++j) {
                    (*sequence)[index++] = pair.first;
                }
            }
        } else {
            // Сортировка по убыванию
            for (auto it = countMap.rbegin(); it != countMap.rend(); ++it) {
                for (int j = 0; j < it->second; ++j) {
                    (*sequence)[index++] = it->first;
                }
            }
        }
    }
};

#endif // COUNTINGSORTER_H
