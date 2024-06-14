#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <vector>
#include <list>
#include <algorithm> 
#include <numeric>   
#include "student.h" 
#include "input.h"
/// @brief 
/// @param a 
/// @param b 
/// @return 
bool compareByFirstName(const Student& a, const Student& b);
/// @brief 
/// @param a 
/// @param b 
/// @return 
bool compareByLastName(const Student& a, const Student& b);
/// @brief 
/// @param a 
/// @param b 
/// @return 
bool compareByGrade(const Student& a, const Student& b);
/// @brief 
/// @param homeworkResults 
/// @return 
double calculateAverage(const std::vector<int>& homeworkResults);
/// @brief 
/// @param data 
/// @param Median 
/// @return 
double calculateFinalGrade(const Student& data, bool Median);
/// @brief 
/// @param homeworkResults 
/// @return 
double calculateMedian(std::vector<int> homeworkResults);
/// @brief 
/// @tparam Container 
/// @param students 
/// @param criteria 
/// @param Median 
template <typename Container>
void sortStudents(Container& students, int criteria, int Median);
/// @brief 
/// @param students 
/// @param criteria 
/// @param Median 
template <>
void sortStudents<std::list<Student>>(std::list<Student>& students, int criteria, int Median);

#endif // CALCULATIONS_H