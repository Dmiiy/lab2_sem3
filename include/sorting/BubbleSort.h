#ifndef BUBBLESORTER_H
#define BUBBLESORTER_H

#include <functional>
#include "ISorter.h"

template <typename T>
class BubbleSorter : public ISorter<T> {
private:
    std::function<bool(const T&, const T&)> comparator;
    static HelpClass helpClass;

public:
    BubbleSorter(std::function<bool(const T&, const T&)> comp = helpClass.descending)
            : comparator(comp) {}

    void sort(ArraySequence<T> *sequence) override {
        if (sequence==nullptr) {
            throw SortExc("Sequence is null");
        }
        int n = sequence->getLength();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (!comparator((*sequence)[j], (*sequence)[j + 1])) {
                    helpClass.swap((*sequence)[j], (*sequence)[j + 1]);
                }
            }
        }
    }
};
template <typename T>
HelpClass BubbleSorter<T>::helpClass;
#endif // BUBBLESORTER_H
