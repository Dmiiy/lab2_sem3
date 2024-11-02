#ifndef LAB2_SEM3_ISORTER_H
#define LAB2_SEM3_ISORTER_H

#include "../sequence/LinkedListSequence.h"
#include "HelpClass.h"

template <typename T>
class ISorter {
public:
    virtual void sort(LinkedListSequence<T> *sequence) = 0;

    void operator()(LinkedListSequence<T> *sequence) {
        sort(sequence);
    }
    virtual ~ISorter() = default;
};

#endif //LAB2_SEM3_ISORTER_H