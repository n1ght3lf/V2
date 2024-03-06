#include "nameGradeFunctions.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "nameConstants.h"
using namespace std;

void generateTestFile(const string& filename, int numEntries) {
    ofstream outputFile(filename);

    outputFile << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> numHomeworkDist(1, 50); // Random number of homework columns

    int numHomework = numHomeworkDist(gen);

    for (int i = 1; i <= numHomework; ++i) {
        outputFile << setw(9) << left << "ND" + to_string(i);
    }
    outputFile << "Egz." << endl;

    uniform_int_distribution<int> dis(1, 10);

    for (int i = 1; i <= numEntries; ++i) {
        outputFile << setw(20) << left << "Vardas" + to_string(i);
        outputFile << setw(20) << left << "Pavarde" + to_string(i);

        for (int j = 0; j < numHomework; ++j) {
            outputFile << setw(9) << left << dis(gen);
        }

        outputFile << dis(gen) << endl;
    }

    outputFile.close();
}

void readData(nameGrade &student)
{
    cout << "Įveskite studento vardą (įveskite '0' jei norite baigti): ";
    cin.ignore();
    getline(cin, student.name);
    if (student.name == "0")
        return;
    cout << "Įveskite studento pavardę: ";
    getline(cin, student.surname);

    cout << "Įveskite namų darbų rezultatus, 11 - baigti: ";
    int i = 0;
    while (true)
    {
        double input;
        cin >> input;
        if (input == 11)
            break;
        if (input < 0 || input > 10 || cin.fail())
        {
            cout << "Netinkama įvestis. Įveskite pažymį tarp 0 ir 10 arba 11, jei norite nutraukti." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        int grade = static_cast<int>(round(input));
        student.homework.push_back(grade);
        ++i;
    }

    while (true)
    {
        cout << "Įveskite egzamino rezultatą: ";
        double examInput;
        cin >> examInput;
        if (examInput < 0 || examInput > 10 || cin.fail())
        {
            cout << "Netinkama įvestis. Įveskite pažymį tarp 0 ir 10." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        student.exam = static_cast<int>(round(examInput));
        break;
    }
}

void generateRandomGrades(nameGrade &student, bool inputName)
{
    if (inputName)
    {
        cout << "Įveskite studento vardą: ";
        cin.ignore();
        getline(cin, student.name);
        cout << "Įveskite studento pavardę: ";
        getline(cin, student.surname);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 10);
    uniform_int_distribution<int> disCount(1, 1000);
    int size = disCount(gen);
    string grades;
    for (int i = 0; i < size; ++i)
    {
        int grade = dis(gen);
        student.homework.push_back(grade);
        grades += to_string(grade) + " ";
    }
    student.exam = dis(gen);
    grades += "Egzaminas: " + to_string(student.exam);
}

void generateRandomNames(nameGrade &student)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, maleNames.size() - 1); 
    uniform_int_distribution<int> disLastName(0, maleLastNames.size() - 1); 
    int maleIndex = dis(gen);
    int maleLastNameIndex = disLastName(gen);
    dis = uniform_int_distribution<int>(0, femaleNames.size() - 1); 
    disLastName = uniform_int_distribution<int>(0, femaleLastNames.size() - 1); 
    int femaleIndex = dis(gen);
    int femaleLastNameIndex = disLastName(gen);
    if (dis(gen) % 2 == 0)
    {
        student.name = maleNames[maleIndex];
        student.surname = maleLastNames[maleLastNameIndex];
    }
    else
    {
        student.name = femaleNames[femaleIndex];
        student.surname = femaleLastNames[femaleLastNameIndex];
    }
}


void deleteStudentData(nameGrade &student)
{
    student.homework.clear();
}

double calculateFinalAverage(const nameGrade &student)
{
    double sum = 0;
    for (size_t i = 0; i < student.homework.size(); ++i)
    {
        sum += student.homework[i];
    }
    double average = sum / student.homework.size();
    return 0.4 * average + 0.6 * student.exam;
}

double calculateFinalMedian(const nameGrade &student)
{
    vector<int> temp = student.homework;
    sort(temp.begin(), temp.end());
    double median;
    if (temp.size() % 2 == 0)
    {
        median = (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2.0;
    }
    else
    {
        median = temp[temp.size() / 2];
    }
    return 0.4 * median + 0.6 * student.exam;
}

void printResults(const nameGrade &student)
{
    cout << fixed << setprecision(2) << setw(20) << left << student.name << setw(20) << left << student.surname << setw(20) << left << calculateFinalAverage(student) << setw(20) << left << calculateFinalMedian(student) << endl;
}

void sortStudents(vector<nameGrade> &students, int sortChoice)
{
    do
    {
        switch (sortChoice)
        {
        case 1:
            sort(students.begin(), students.end(), [](const nameGrade &a, const nameGrade &b) {
                return a.name < b.name;
            });
            break;
        case 2:
            sort(students.begin(), students.end(), [](const nameGrade &a, const nameGrade &b) {
                return a.surname < b.surname;
            });
            break;
        case 3:
            sort(students.begin(), students.end(), [](const nameGrade &a, const nameGrade &b) {
                return calculateFinalAverage(a) < calculateFinalAverage(b);
            });
            break;
        case 4:
            sort(students.begin(), students.end(), [](const nameGrade &a, const nameGrade &b) {
                return calculateFinalMedian(a) < calculateFinalMedian(b);
            });
            break;
        default:
            cout << "Netinkama įvestis." << endl;
            cout << "Rūšiuoti pagal :\n1 - Vardą\n2 - Pavardę\n3 - Pažymių vidurkį\n4 - Pažymių medianą" << endl;
            cin >> sortChoice;
            continue;
        }
        break; 
    } while (true);
}
