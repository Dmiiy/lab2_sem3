
#ifndef COMPS_H
#define COMPS_H

#include <functional>
#include "User.h"

const std::function<bool(const int&, const int&)> ascending= [](const int &a, const int &b) { return a < b; };
const std::function<bool(const int&, const int&)> descending= [](const int &a, const int &b) { return a > b; };

const std::function<bool(const User&, const User&)> compareByLastNameAscending =[](const User &a, const User &b) { return a.getLastName() < b.getLastName(); };
const std::function<bool(const User&, const User&)> compareByLastNameDescending =[](const User &a, const User &b) { return a.getLastName() > b.getLastName(); };

const std::function<bool(const User&, const User&)> compareByFirstNameAscending =[](const User &a, const User &b) { return a.getFirstName() < b.getFirstName(); };
const std::function<bool(const User&, const User&)> compareByFirstNameDescending =[](const User &a, const User &b) { return a.getFirstName() > b.getFirstName(); };

const std::function<bool(const User&, const User&)> compareByAgeAscending =[](const User &a, const User &b) { return a.getAge() < b.getAge(); };
const std::function<bool(const User&, const User&)> compareByAgeDescending =[](const User &a, const User &b) { return a.getAge() > b.getAge(); };

#endif COMPS_H
