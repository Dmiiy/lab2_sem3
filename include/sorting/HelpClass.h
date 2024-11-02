
#ifndef LAB2_SEM3_HELPCLASS_H
#define LAB2_SEM3_HELPCLASS_H

#include <functional>


class HelpClass {
public:
    template<typename T>
    static void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }
    const std::function<bool(const int&, const int&)> ascending= [](const int &a, const int &b) { return a < b; };
    const std::function<bool(const int&, const int&)> descending= [](const int &a, const int &b) { return a > b; };
};

#endif //LAB2_SEM3_HELPCLASS_H
