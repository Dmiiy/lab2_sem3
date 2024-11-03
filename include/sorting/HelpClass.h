
#ifndef LAB2_SEM3_HELPCLASS_H
#define LAB2_SEM3_HELPCLASS_H

#include <functional>
#include "User.h"

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

    const std::function<bool(const User&, const User&)> compareByLastNameAscending =[](const User &a, const User &b) { return a.getLastName() < b.getLastName(); };
    const std::function<bool(const User&, const User&)> compareByLastNameDescending =[](const User &a, const User &b) { return a.getLastName() > b.getLastName(); };

    const std::function<bool(const User&, const User&)> compareByFirstNameAscending =[](const User &a, const User &b) { return a.getFirstName() < b.getFirstName(); };
    const std::function<bool(const User&, const User&)> compareByFirstNameDescending =[](const User &a, const User &b) { return a.getFirstName() > b.getFirstName(); };

    const std::function<bool(const User&, const User&)> compareByAgeAscending =[](const User &a, const User &b) { return a.getAge() < b.getAge(); };
    const std::function<bool(const User&, const User&)> compareByAgeDescending =[](const User &a, const User &b) { return a.getAge() > b.getAge(); };

};

#endif //LAB2_SEM3_HELPCLASS_H
