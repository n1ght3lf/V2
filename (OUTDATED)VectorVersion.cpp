#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <random>
#include <vector>
using namespace std;

const vector<string> maleNames = {"Adas", "Aidas", "Albertas", "Dovydas", "Jonas", "Lukas"};
const vector<string> maleLastNames = {"Adomaitis", "Petrauskas", "Butkus", "Stankevičius", "Kazlauskas", "Urbonas", "Jakubauskas", "Jankūnas"};
const vector<string> femaleNames = {"Donata", "Dorotėja", "Rugilė", "Rūta", "Skaistė"};
const vector<string> femaleLastNames = {"Petrauskaitė", "Urbonaitė", "Jakubauskaitė", "Jankūnaitė", "Degutytė", "Ivanauskaitė", "Varnaitė"};

struct nameGrade {
    string name;
    string surname;
    vector<double> homework;
    double exam;
    double final;
};

void readData(nameGrade& student) {
    cout << "Enter student's name (enter '0' to finish): ";
    cin.ignore();
    getline(cin, student.name);
    if (student.name == "0") return;
    cout << "Enter student's surname: ";
    getline(cin, student.surname);
    cout << "Enter homework results, 11 to finish: ";
    int size = 1; // Initial array size
    int i = 0;
    while (true) {
        double input;
        cin >> input;
        if (input == 11) break;
        if (input < 0 || input > 10) {
            cout << "Enter a grade between 0 and 10 or 11 to cancel." << endl;
            continue;
        }
        student.homework.push_back(input);
        ++i;
    }
    while (true) {
        cout << "Enter exam result: ";
        cin >> student.exam;
        if (student.exam < 0 || student.exam > 10) {
            cout << "Enter a result between 0 and 10." << endl;
            continue;
        }
        break;
    }
}

void generateRandomGrades(nameGrade& student, bool inputName) {
    if (inputName) {
        cout << "Enter student's name: ";
        cin.ignore();
        getline(cin, student.name);
        cout << "Enter student's surname: ";
        getline(cin, student.surname);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 10.0);
    uniform_int_distribution<int> disCount(1, 1000);
    int size = disCount(gen); 
    string grades;
    for (int i = 0; i < size; ++i) {
        double grade = dis(gen);
        student.homework.push_back(grade);
        grades += to_string(grade) + " ";
    }
    student.exam = dis(gen);
    grades += "Exam: " + to_string(student.exam);
    cout << "Name: " << student.name << " " << student.surname << endl;
    cout << "Grades: " << grades << endl;
}

void generateRandomNames(nameGrade& student) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 5);
    int maleIndex = dis(gen);
    int femaleIndex = dis(gen);
    int maleLastNameIndex = dis(gen);
    int femaleLastNameIndex = dis(gen);
    if (dis(gen) % 2 == 0) {
        student.name = maleNames[maleIndex];
        student.surname = maleLastNames[maleLastNameIndex];
    } else {
        student.name = femaleNames[femaleIndex];
        student.surname = femaleLastNames[femaleLastNameIndex];
    }
}

void deleteStudentData(nameGrade& student) {
    student.homework.clear();
}

double calculateFinalAverage(nameGrade& student) {
    double sum = 0;
    for (size_t i = 0; i < student.homework.size(); ++i) {
        sum += student.homework[i];
    }
    double average = sum / student.homework.size();
    return 0.4 * average + 0.6 * student.exam;
}

double calculateFinalMedian(nameGrade& student) {
    vector<double> temp = student.homework;
    sort(temp.begin(), temp.end());
    double median;
    if (temp.size() % 2 == 0) {
        median = (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2.0;
    } else {
        median = temp[temp.size() / 2];
    }
    return 0.4 * median + 0.6 * student.exam;
}

void printResults(nameGrade& student, bool useAverage) {
    cout << student.name << " " << student.surname << " ";
    if (useAverage) {
        student.final = calculateFinalAverage(student);
        cout << fixed << setprecision(2) << student.final << endl;
    } else {
        student.final = calculateFinalMedian(student);
        cout << fixed << setprecision(2) << student.final << endl;
    }
}

int main() {
    vector<nameGrade> students;
    while (true) {
        cout << "Menu:\n1 - Enter data manually\n2 - Generate random grades\n3 - Generate random grades and names\n4 - Exit" << endl;
        int choice;
        cin >> choice;
        if (choice == 4) break;
        nameGrade newStudent;
        if (choice == 1) {
            readData(newStudent);
        } else if (choice == 2) {
            generateRandomGrades(newStudent, true);
        } else if (choice == 3) {
            generateRandomNames(newStudent);
            generateRandomGrades(newStudent, false);
        }
        if (newStudent.name == "0") break;
        students.push_back(newStudent);
    }
    
    for (size_t i = 0; i < students.size(); ++i) {
        bool useAverage;
        cout << "Use average? (0/1): ";
        cin >> useAverage;
        printResults(students[i], useAverage);
    }
    
    for (size_t i = 0; i < students.size(); ++i) {
        deleteStudentData(students[i]);
    }
    
    return 0;
}