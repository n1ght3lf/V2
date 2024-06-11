#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "student.h"
#include "calculations.h"
#include "functionality.h"

/// brief Gauti konteinerio tipą iš vartotojo
/// return Konteinerio tipas
int getContainerTypeFromUser();

/// brief Gauti medianos pirmenybę
/// return Boolean reikšmė ar medianos skaičiavimas yra pirmenybė
bool getMedianPreference();

/// @brief Apdoroti studentus
/// @param students Studentų konteineris
/// @param Median Ar naudoti medianą
/// @param startTotal Pradžios laiko momentas
template <typename Container>
void processStudents(Container& students, bool Median, std::chrono::high_resolution_clock::time_point startTotal);

/// @brief Meniu funkcija
/// @return Vartotojo pasirinkimas
int Menu();

/// @brief Gauti failo pavadinimą iš vartotojo
/// @return Failo pavadinimas
std::string getFilenameFromUser();

/// @brief Skaityti duomenis iš failo į studentų konteinerį
/// @param fin Įvesties failo srautas
/// @param students Studentų konteineris
template <typename Container>
void readData(std::ifstream& fin, Container& students);

/// @brief Atidaryti failus ir apdoroti studentus
/// @param filenames Failų pavadinimų sąrašas
/// @param students Studentų konteineris
/// @param Median Ar naudoti medianą
/// @param strategy Apdorojimo strategija
template <typename Container>
void openFiles(const std::vector<std::string>& filenames, Container& students, bool Median, int strategy);

/// @brief Vartotojo įvestis
/// @param data Studentas
/// @param Median Ar naudoti medianą
void input(Student& data, bool& Median);

/// @brief Gauti studento duomenis kaip eilutę
/// @param s Studentas
/// @return Studentų duomenys eilutėje
std::string studentData(const Student& s);

#endif // INPUT_H
