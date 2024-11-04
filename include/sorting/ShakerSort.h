#ifndef SHAKERSORTER_H
#define SHAKERSORTER_H

#include <functional>
#include "ISorter.h"

template <typename T>
class ShakerSorter : public ISorter<T> {
private:
    std::function<bool(const T&, const T&)> comparator;
    static HelpClass helpClass;

public:
    ShakerSorter(std::function<bool(const T&, const T&)> comp = helpClass.descending)
            : comparator(comp) {}

    void sort(ArraySequence<T> *sequence) override {
        if (sequence==nullptr) {
            throw SortExc("Sequence is null");
        }
        bool swapped = true;
        int start = 0;
        int end = sequence->getLength() - 1;

        while (swapped) {
            swapped = false;

            for (int i = start; i < end; ++i) {
                if (!comparator((*sequence)[i], (*sequence)[i + 1])) {
                    helpClass.swap((*sequence)[i], (*sequence)[i + 1]);
                    swapped = true;
                }
            }

            if (!swapped)
                break;

            swapped = false;
            --end;

            for (int i = end; i > start; --i) {
                if (!comparator((*sequence)[i - 1], (*sequence)[i])) {
                    helpClass.swap((*sequence)[i - 1], (*sequence)[i]);
                    swapped = true;
                }
            }

            ++start;
        }
    }
};
template <typename T>
HelpClass ShakerSorter<T>::helpClass;
#endif // SHAKERSORTER_H
