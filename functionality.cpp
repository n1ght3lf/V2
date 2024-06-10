#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include "functionality.h"

using namespace std;

int getContainerTypeFromUser() {
    int containerType;

    cout << "\nPasirinkite konteinerio tipą: \n";
    cout << "1 - Vector\n";
    cout << "2 - Deque\n";
    cout << "3 - List\n";
    cout << "\nPasirinkite: ";
    cin >> containerType;

    while (containerType < 1 || containerType > 3) {
        cout << "Netinkama įvestis, įveskite skaičių tarp 1 ir 3. \n";
        cin >> containerType;
    }

    return containerType;
}

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
        cout << student << fixed << setprecision(2) << finalGrade << endl;
    }
}

template <typename Container>
void outputToFile(const Container& students, size_t numberOfStudents, bool Median, const string& filename) {
    ofstream outputFile(filename);
    outputFile << left << setw(15) << "Pavardė" << setw(15) << " Vardas" << setw(20) << (Median ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl; 
    outputFile << "-------------------------------------------------------" << endl;
    for (const auto& student : students) {
        double finalGrade = student.calculateFinalGrade(Median);
        outputFile << student << fixed << setprecision(2) << finalGrade << endl;
    }
    outputFile.close();
}

template void outputToFile<vector<Student>>(const vector<Student>&, size_t, bool, const string&);
template void outputToFile<deque<Student>>(const deque<Student>&, size_t, bool, const string&);
template void outputToFile<list<Student>>(const list<Student>&, size_t, bool, const string&);