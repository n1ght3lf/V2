#include "calculations.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool compareByFirstName(const Student &a, const Student &b)
{
    return a.getFirstName() < b.getFirstName();
}

bool compareByLastName(const Student &a, const Student &b)
{
    return a.getLastName() < b.getLastName();
}

bool compareByGrade(const Student &a, const Student &b)
{
    return a.calculateFinalGrade(false) < b.calculateFinalGrade(false);
}

template <typename Container>
void sortStudents(Container &students, int criteria, int Median)
{
    if (criteria == 1)
    {
        sort(students.begin(), students.end(), compareByFirstName);
    }
    else if (criteria == 2)
    {
        sort(students.begin(), students.end(), compareByLastName);
    }
    else if (criteria == 3)
    {
        sort(students.begin(), students.end(), compareByGrade);
        if (Median == 1)
        {
            int size = students.size();
            int medianIndex = size / 2;
            auto it = students.begin();
            std::advance(it, medianIndex);
            std::nth_element(students.begin(), it, students.end(), compareByGrade);
        }
    }
}

template <>
void sortStudents<list<Student>>(list<Student> &students, int criteria, int median)
{
    if (criteria == 1)
    {
        students.sort(compareByFirstName);
    }
    else if (criteria == 2)
    {
        students.sort(compareByLastName);
    }
    else if (criteria == 3)
    {
        students.sort(compareByGrade);
    }
}

template void sortStudents<vector<Student>>(vector<Student> &, int, int);
template void sortStudents<deque<Student>>(deque<Student> &, int, int);
template void sortStudents<MyVector<Student>>(MyVector<Student>&, int, int);