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
template <typename T>
size_t getCapacity(const std::vector<T>& container);
template <typename T>
size_t getCapacity(const MyVector<T>& container);
template <typename Container>
void testContainer(unsigned int sz, const std::string& containerName);

#endif // FUNCTIONALITY_H