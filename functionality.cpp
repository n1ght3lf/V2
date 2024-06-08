#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "functionality.h"

using namespace std;

int generateGrade() {
    return rand() % 10 + 1; // grazina skaiciu nuo 1 iki 10 (pazymi)
}

string generateName() {
    string firstNames[] = {"Jonas", "Tomas", "Rokas", "Lukas", "Mantas", "Arvydas"};
    return firstNames[rand() % 6];
}

string generateLastName() {
    string lastNames[] = {"Kazlauskas", "Sabonis", "Stankevicius", "Petrauskas", "Navickas", "Urbonas"};
    return lastNames[rand() % 6]; 
}

string isString(const string& prompt) {
    while (true) {
        try {
            string userInput;
            cout << prompt;
            cin >> userInput;
            if (!all_of(userInput.begin(), userInput.end(), ::isalpha)) { // patikrina ar ivestis yra tik is raidziu
                throw runtime_error("Netinkama įvestis, nenaudokite skaičių.");
            }
            return userInput;
        } catch (const runtime_error& e) {
            cerr << e.what() << '\n';
        }
    }
}

int isGrade(const string& prompt) {
    while (true) {
        try {
            int userInput;
            cout << prompt;
            cin >> userInput;
            if (cin.fail() || cin.peek() != '\n' || (userInput < 1 && userInput != -1) || userInput > 10) { // patikrina ar ivestis yra sveikas skaicius nuo 1 iki 10 arba -1
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Netinkama įvestis, įveskite sveiką skaičių nuo 1 iki 10 arba -1 jei baigėte."); 
            }
            return userInput;
        } catch (const runtime_error& e) {
            cerr << e.what() << '\n';
        }
    }
}

void testFiles(const vector<string>& filenames) {
    int TestCount = 3; 
    double totalTime = 0.0;
    for (vector<string>::const_iterator FileIterator = filenames.begin(); FileIterator != filenames.end(); ++FileIterator) { 
        ifstream inputFile(*FileIterator); 
        for (int test = 0; test < TestCount; ++test) {
            clock_t startTimer = clock(); 
            vector<Student> students;
            readData(inputFile, students);
            clock_t endTimer = clock(); 
            double seconds = double(endTimer - startTimer) / CLOCKS_PER_SEC; 
            totalTime += seconds; 
            inputFile.clear(); 
            inputFile.seekg(0); 
        }
        inputFile.close();
    }
    double averageTime = totalTime / (filenames.size() * TestCount); 
    cout << "\nKelių testų laikų vidurkis: " << averageTime << " sekundės" << endl;
}

double generateFile(int studentCount) {
    auto startTimer = chrono::high_resolution_clock::now();
    ofstream outputFile("studentai" + to_string(studentCount) + ".txt");
    if (!outputFile) {
        cerr << "Nepavyko sukurti failo 'studentai" << studentCount << ".txt'\n";
        return -1.0;
    }

    outputFile << left << setw(16) << "Vardas" << setw(16) << "Pavarde";
    for (int i = 1; i <= 15; i++) {
        outputFile << setw(5) << "ND" + to_string(i);
    }
    outputFile << setw(5) << "Egz." << endl;

    for (int i = 1; i <= studentCount; i++) {
        outputFile << setw(16) << "Vardas" + to_string(i) << setw(16) << "Pavarde" + to_string(i);
        for (int j = 0; j < 15; j++) {
            outputFile << setw(5) << generateGrade();
        }
        outputFile << setw(5) << generateGrade() << endl;
    }
    auto endTimer = chrono::high_resolution_clock::now();
    return chrono::duration<double>(endTimer - startTimer).count();
}

void outputToTerminal(const vector<Student>& badStudents, const vector<Student>& goodStudents, bool Median){
    cout <<"\nNuskriaustukai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : badStudents) {
        double finalGrade = calculateFinalGrade(student, Median);
        cout << setw(15) << student.lastName << setw(15) << student.firstName << fixed << setprecision(2) << finalGrade << endl;
    }
    cout <<"\nKietiakai: \n\n";
    cout << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    cout << "-------------------------------------------------------" << endl;
    for (const auto& student : goodStudents) {
        double finalGrade = calculateFinalGrade(student, Median);
        cout << setw(15) << student.lastName << setw(15) << student.firstName << fixed << setprecision(2) << finalGrade << endl;
    }
}

void outputToFile(const vector<Student>& students, size_t numberOfStudents, bool Median, const string& filename){
    ofstream outputFile(filename);
    outputFile << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    outputFile << "-------------------------------------------------------" << endl;
    for (int i = 0; i < numberOfStudents; i++) {
        double finalGrade = calculateFinalGrade(students[i], Median);
        outputFile << setw(15) << students[i].lastName << setw(15) << students[i].firstName << fixed << setprecision(2) << finalGrade << endl;
    }
    outputFile.close();
}