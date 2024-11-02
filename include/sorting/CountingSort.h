#ifndef COUNTINGSORTER_H
#define COUNTINGSORTER_H

#include <vector>
#include "ISorter.h"

template <typename T>
class CountingSorter : public ISorter<T> {
public:
    void sort(LinkedListSequence<T> *sequence) override {
        T maxVal = findMax(sequence);
        T minVal = findMin(sequence);
        int range = maxVal - minVal + 1;

        LinkedListSequence<int> count(0,range);
        int n = sequence->getLength();

        for (int i = 0; i < n; ++i) {
            count[(*sequence)[i] - minVal]++;
        }

        int index = 0;
        for (int i = 0; i < range; ++i) {
            while (count[i]-- > 0) {
                (*sequence)[index++] = i + minVal;
            }
        }
    }

private:
    T findMax(LinkedListSequence<T> *sequence) {
        T maxVal = (*sequence)[0];
        for (int i = 1; i < sequence->getLength(); ++i) {
            if ((*sequence)[i] > maxVal) {
                maxVal = (*sequence)[i];
            }
        }
        return maxVal;
    }

    T findMin(LinkedListSequence<T> *sequence) {
        T minVal = (*sequence)[0];
        for (int i = 1; i < sequence->getLength(); ++i) {
            if ((*sequence)[i] < minVal) {
                minVal = (*sequence)[i];
            }
        }
        return minVal;
    }
};

#endif // COUNTINGSORTER_H
