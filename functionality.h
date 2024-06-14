#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <string>
#include <cstdlib>
#include <vector>
#include "student.h"
#include "calculations.h"

/// @brief Sugeneruoti pažymį
/// @return Pažymys
int generateGrade();

/// @brief Sugeneruoti vardą
/// @return Vardas
std::string generateName();

/// @brief Sugeneruoti pavardę
/// @return Pavardė
std::string generateLastName();

/// @brief Tikrinti, ar įvestas tekstas yra eilutė
/// @param prompt Pranešimas vartotojui
/// @return Eilutė
std::string isString(const std::string& prompt);

/// @brief Tikrinti, ar įvestas pažymys yra tinkamas
/// @param prompt Pranešimas vartotojui
/// @return Pažymys
int isGrade(const std::string& prompt);

/// @brief Sugeneruoti failą su studentų duomenimis
/// @param studentCount Studentų skaičius
void generateFile(int studentCount);

/// @brief Išvesti duomenis į terminalą
/// @param badStudents Prastai besimokantys studentai
/// @param goodStudents Gerai besimokantys studentai
/// @param Median Ar naudoti medianą
void outputToTerminal(const std::vector<Student>& badStudents, const std::vector<Student>& goodStudents, bool Median);

/// @brief Išvesti duomenis į failą
/// @param students Studentų konteineris
/// @param numberOfStudents Studentų skaičius
/// @param Median Ar naudoti medianą
/// @param filename Failo pavadinimas
template <typename Container>
void outputToFile(const Container& students, size_t numberOfStudents, bool Median, const std::string& filename);

/// @brief Gauti konteinerio talpą
/// @param container Konteineris
/// @return Talpa
template <typename T>
size_t getCapacity(const std::vector<T>& container);

/// @brief Gauti mano vektoriaus talpą
/// @param container Mano vektorius
/// @return Talpa
template <typename T>
size_t getCapacity(const MyVector<T>& container);

/// @brief Testuoti konteinerį
/// @param sz Dydis
/// @param containerName Konteinerio pavadinimas
template <typename Container>
void testContainer(unsigned int sz, const std::string& containerName);

#endif // FUNCTIONALITY_H
