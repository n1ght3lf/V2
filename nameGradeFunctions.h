#ifndef NAMEGRADEFUNCTIONS_H
#define NAMEGRADEFUNCTIONS_H

#include "nameGrade.h"

void readData(nameGrade &student);
void generateRandomGrades(nameGrade &student, bool inputName);
void generateRandomNames(nameGrade &student);
void deleteStudentData(nameGrade &student);
double calculateFinalAverage(const nameGrade &student);
double calculateFinalMedian(const nameGrade &student);
void printResults(const nameGrade &student);
void sortStudents(std::vector<nameGrade> &students, int sortChoice);

#endif
