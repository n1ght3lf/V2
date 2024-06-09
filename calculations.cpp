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
void sortStudents(vector<Student> &students, int criteria, int Median)
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
        if (Median == 1)
        {
            sort(students.begin(), students.end(), [](const Student &a, const Student &b)
                 { return calculateFinalGrade(a, true) < calculateFinalGrade(b, true); });
        }
        else
        {
            sort(students.begin(), students.end(), compareByGrade);
        }
    }
}
template <>
void sortStudents<list<Student>>(list<Student> &students, int criteria)
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

template void sortStudents<vector<Student>>(vector<Student> &, int);
template void sortStudents<deque<Student>>(deque<Student> &, int);