#ifndef LAB2_SEM3_ISORTER_H
#define LAB2_SEM3_ISORTER_H


#include "HelpClass.h"
#include "../sequence/ArraySequence.h"
#include "SortExc.h"

template <typename T>
class ISorter {
public:
    virtual void sort(ArraySequence<T> *sequence) = 0;

    void operator()(ArraySequence<T> *sequence) {
        sort(sequence);
    }

    virtual ~ISorter() = default;
};

#endif //LAB2_SEM3_ISORTER_H
