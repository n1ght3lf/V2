#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include "functionality.h"

using namespace std;
/// @brief Sugeneruoti pažymį
/// @return Pažymys
int generateGrade() {
    return rand() % 10 + 1; 
}
/// @brief Sugeneruoti vardą
/// @return Vardas
string generateName() {
    string firstNames[] = {"Adas", "Aidas", "Albertas", "Dovydas", "Jonas", "Lukas"};
    return firstNames[rand() % 6];
}
/// @brief Sugeneruoti pavardę
/// @return Pavardė
string generateLastName() {
    string lastNames[] = {"Adomaitis", "Petrauskas", "Butkus", "Stankevicius", "Kazlauskas", "Urbonas", "Jakubauskas", "Jankunas"};
    return lastNames[rand() % 6]; 
}
/// @brief Tikrinti, ar įvestas tekstas yra eilutė
/// @param prompt Pranešimas vartotojui
/// @return Eilutė
string isString(const string& prompt) {
    while (true) {
        try {
            string userInput;
            cout << prompt;
            cin >> userInput;
            if (!all_of(userInput.begin(), userInput.end(), ::isalpha)) { 
                throw runtime_error("Netinkama įvestis, nenaudokite skaičių.");
            }
            return userInput;
        } catch (const runtime_error& e) {
            cerr << e.what() << '\n';
        }
    }
}
/// @brief Tikrinti, ar įvestas pažymys yra tinkamas
/// @param prompt Pranešimas vartotojui
/// @return Pažymys
int isGrade(const string& prompt) {
    while (true) {
        try {
            int userInput;
            cout << prompt;
            cin >> userInput;
            if (cin.fail() || cin.peek() != '\n' || (userInput < 1 && userInput != -1) || userInput > 10) { 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Netinkama įvestis, įveskite sveiką skaičių nuo 1 iki 10 arba -1 jei baigėte."); 
            }
            return userInput;
        } catch (const runtime_error& e) {
            cerr << e.what() << '\n';
        }
    }
}
/// @brief Gauti mano vektoriaus talpą
/// @param container Mano vektorius
/// @return Talpa
template <typename T>
size_t getCapacity(const std::vector<T>& container) {
    return container.capacity();
}
/// @brief Gauti mano vektoriaus talpą
/// @param container Mano vektorius
/// @return Talpa
template <typename T>
size_t getCapacity(const MyVector<T>& container) {
    return container.getCapacity();
}
/// @brief Testuoti konteinerį
/// @param sz Dydis
/// @param containerName Konteinerio pavadinimas
template <typename Container>
void testContainer(unsigned int sz, const std::string& containerName) {
    auto start = std::chrono::high_resolution_clock::now();
    Container container;
    unsigned int reallocations = 0;
    for (int i = 1; i <= sz; ++i) {
        if (container.size() == getCapacity(container)) {
            reallocations++;
        }
        container.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Laikas užpildyti " << containerName << " su " << sz << " elementų: " << std::fixed << std::setprecision(6) << diff.count() << " s\n";
    std::cout << "Atminties perskirstymų skaičius: " << reallocations << "\n\n";
}

template void testContainer<std::vector<int>>(unsigned int, const std::string&);
template void testContainer<MyVector<int>>(unsigned int, const std::string&);

/// @brief Sugeneruoti failą su studentų duomenimis
/// @param studentCount Studentų skaičius
void generateFile(int studentCount) {
    auto startTimer = chrono::high_resolution_clock::now(); 

    ofstream outputFile("studentai" + to_string(studentCount) + ".txt");
    if (!outputFile) {
        cerr << "Nepavyko sukurti failo 'studentai" << studentCount << ".txt'\n";
        return;
    }

    outputFile << left << setw(16) << "Vardas" << setw(16) << "Pavarde";
    for (int i = 1; i <= 15; i++) {
        outputFile << setw(5) << "ND" + to_string(i);
    }
    outputFile << setw(5) << "Egz." << endl;

    for (int i = 1; i <= studentCount; i++) {
        outputFile << setw(16) << "Vardas" + to_string(i) << setw(16) << "Pavarde" + to_string(i);
        for (int homeworkIndex = 0; homeworkIndex < 15; homeworkIndex++) {
            outputFile << setw(5) << generateGrade();
        }
        outputFile << setw(5) << generateGrade() << endl;
    }

    auto endTimer = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = endTimer-startTimer; 

    cout << "Failas 'studentai" << studentCount << ".txt' sukurtas per " << diff.count() << " sekundes.\n";
}
/// @brief Išvesti duomenis į terminalą
/// @param badStudents Prastai besimokantys studentai
/// @param goodStudents Gerai besimokantys studentai
/// @param Median Ar naudoti medianą
void outputToTerminal(const vector<Student>& badStudents, const vector<Student>& goodStudents, bool Median){
    cout <<"\nNuskriaustukai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : badStudents) {
        double finalGrade = student.calculateFinalGrade(Median);
        cout << student << fixed << setprecision(2) << finalGrade << endl;
    }
    cout <<"\nKietiakai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : goodStudents) {
        double finalGrade = student.calculateFinalGrade(Median);
        cout << left << setw(15) << student.getLastName() << setw(15) << student.getFirstName() << setw(20) << fixed << setprecision(2) << finalGrade << endl;
    }
}
/// @brief Išvesti duomenis į failą
/// @param students Studentų konteineris
/// @param numberOfStudents Studentų skaičius
/// @param Median Ar naudoti medianą
/// @param filename Failo pavadinimas
template <typename Container>
void outputToFile(const Container& students, size_t numberOfStudents, bool Median, const string& filename) {
    ofstream outputFile(filename);
    outputFile << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    outputFile << "-------------------------------------------------------" << endl;
    for (const auto& student : students) {
        double finalGrade = student.calculateFinalGrade(Median);
        outputFile << left << setw(15) << student.getLastName() << setw(15) << student.getFirstName() << setw(20) << fixed << setprecision(2) << finalGrade << endl;
    }
    outputFile.close();
}

template void outputToFile<vector<Student>>(const vector<Student>&, size_t, bool, const string&);
template void outputToFile<deque<Student>>(const deque<Student>&, size_t, bool, const string&);
template void outputToFile<list<Student>>(const list<Student>&, size_t, bool, const string&);
template void outputToFile<MyVector<Student>>(const MyVector<Student>&, size_t, bool, const std::string&);