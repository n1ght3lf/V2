#include "nameGradeFunctions.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "nameConstants.h"
using namespace std;

void readData(nameGrade &student)
{
    cout << "Enter student's name (enter '0' to finish): ";
    cin.ignore();
    getline(cin, student.name);
    if (student.name == "0")
        return;
    cout << "Enter student's surname: ";
    getline(cin, student.surname);
    cout << "Enter homework results, 11 to finish: ";
    int i = 0;
    while (true)
    {
        double input;
        cin >> input;
        if (input == 11)
            break;
        if (input < 0 || input > 10)
        {
            cout << "Enter a grade between 0 and 10 or 11 to cancel." << endl;
            continue;
        }
        int grade = static_cast<int>(round(input));
        student.homework.push_back(grade);
        ++i;
    }
    while (true)
    {
        cout << "Enter exam result: ";
        double examInput;
        cin >> examInput;
        student.exam = static_cast<int>(round(examInput));
        if (student.exam < 0 || student.exam > 10)
        {
            cout << "Enter a result between 0 and 10." << endl;
            continue;
        }
        break;
    }
}

void generateRandomGrades(nameGrade &student, bool inputName)
{
    if (inputName)
    {
        cout << "Enter student's name: ";
        cin.ignore();
        getline(cin, student.name);
        cout << "Enter student's surname: ";
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
    grades += "Exam: " + to_string(student.exam);
}

void generateRandomNames(nameGrade &student)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 5);
    int maleIndex = dis(gen);
    int femaleIndex = dis(gen);
    int maleLastNameIndex = dis(gen);
    int femaleLastNameIndex = dis(gen);
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
            cout << "Invalid choice." << endl;
            cout << "Sort by:\n1 - Name\n2 - Lastname\n3 - Grade (average)\n4 - Grade (median)" << endl;
            cin >> sortChoice;
            continue;
        }
        break; 
    } while (true);
}
