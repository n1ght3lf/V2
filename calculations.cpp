#include "calculations.h"
#include <iostream>
#include <algorithm>

using namespace std;

/// @brief Palyginti studentus pagal vardą
/// @param a Pirmas studentas
/// @param b Antras studentas
/// @return Boolean reikšmė
bool compareByFirstName(const Student &a, const Student &b)
{
    return a.getFirstName() < b.getFirstName();
}
/// @brief Palyginti studentus pagal pavardę
/// @param a Pirmas studentas
/// @param b Antras studentas
/// @return Boolean reikšmė
bool compareByLastName(const Student &a, const Student &b)
{
    return a.getLastName() < b.getLastName();
}

/// @brief Palyginti studentus pagal pažymį
/// @param a Pirmas studentas
/// @param b Antras studentas
/// @return Boolean reikšmė
bool compareByGrade(const Student &a, const Student &b)
{
    return a.calculateFinalGrade(false) < b.calculateFinalGrade(false);
}
/// @brief Funkcija, kuri surikiuoja studentus pagal nurodytus kriterijus.
/// @tparam Container Konteinerio tipas, kuriame saugomi studentai.
/// @param students Studentų konteineris, kuris bus surikiuotas.
/// @param criteria Kriterijus, pagal kurį bus atliekama rikiavimas.
/// @param Median Jei 1, tada surikiuojant pagal galutinį balą naudojama mediana.
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
/// @brief Funkcija, kuri surikiuoja studentus pagal nurodytus kriterijus.
/// @param students Studentų konteineris, kuris bus surikiuotas.
/// @param criteria Kriterijus, pagal kurį bus atliekama rikiavimas.
/// @param Median Jei 1, tada surikiuojant pagal galutinį balą naudojama mediana.
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
        if (median == 1)
        {
            int size = students.size();
            int medianIndex = size / 2;
            auto it = students.begin();
            advance(it, medianIndex);
            students.splice(students.begin(), students, it);
        }
    }
}

template void sortStudents<vector<Student>>(vector<Student> &, int, int);
template void sortStudents<deque<Student>>(deque<Student> &, int, int);
template void sortStudents<MyVector<Student>>(MyVector<Student>&, int, int);