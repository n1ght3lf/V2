#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <list>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "myVector.h"

/// @brief Asmens klasė
class Person {
public:
    virtual ~Person() = default; ///< Destruktorius

    /// @brief Geteriai
    virtual std::string getFirstName() const = 0;
    virtual std::string getLastName() const = 0;
    virtual std::string getName() const = 0;
};

#endif // PERSON_H
