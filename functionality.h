#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <string>
#include <cstdlib> 
#include <vector>
#include "student.h" 
#include "calculations.h"


int generateGrade();
std::string generateName();
std::string generateLastName();
std::string isString(const std::string& prompt);
int isGrade(const std::string& prompt);
void generateFile(int studentCount);
void outputToTerminal(const std::vector<Student>& badStudents, const std::vector<Student>& goodStudents, bool Median);
template <typename Container>
void outputToFile(const Container& students, size_t numberOfStudents, bool Median, const std::string& filename);

#endif // FUNCTIONALITY_H