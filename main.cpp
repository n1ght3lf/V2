#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <random>
using namespace std;

const string maleNames[] = {"Adas", "Aidas", "Albertas", "Dovydas", "Jonas", "Lukas"};
const string maleLastNames[] = {"Adomaitis", "Petrauskas", "Butkus", "Stankevičius", "Kazlauskas", "Urbonas", "Jakubauskas", "Jankūnas"};
const string femaleNames[] = {"Donata", "Dorotėja", "Rugilė", "Rūta", "Skaistė"};
const string femaleLastNames[] = {"Petrauskaitė", "Urbonaitė", "Jakubauskaitė", "Jankūnaitė", "Degutytė", "Ivanauskaitė", "Varnaitė"};

struct nameGrade {
    string name;
    string surname;
    double* homework;
    double exam;
    double final;
    int n = 0; // number of homework assignments
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
    student.homework = new double[size];
    int i = 0;
    while (true) {
        double input;
        cin >> input;
        if (input == 11) break;
        if (input < 0 || input > 10) {
            cout << "Enter a grade between 0 and 10 or 11 to cancel." << endl;
            continue;
        }
        if (i == size) {
            size *= 2;
            double* newHomework = new double[size];
            for (int j = 0; j < i; ++j) {
                newHomework[j] = student.homework[j];
            }
            delete[] student.homework;
            student.homework = newHomework;
        }
        student.homework[i] = input;
        ++i;
    }
    student.n = i;
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

void generateRandomGrades(nameGrade& student) {
    cout << "Enter student's name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter student's surname: ";
    getline(cin, student.surname);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 10.0);
    uniform_int_distribution<int> disCount(1, 1000);
    int size = disCount(gen); 
    student.homework = new double[size];
    string grades;
    for (int i = 0; i < size; ++i) {
        double grade = dis(gen);
        student.homework[i] = grade;
        grades += to_string(grade) + " ";
    }
    student.n = size;
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
    delete[] student.homework;
    student.homework = nullptr;
}

double calculateFinalAverage(nameGrade& student) {
    double sum = 0;
    for (int i = 0; i < student.n; ++i) {
        sum += student.homework[i];
    }
    double average = sum / student.n;
    return 0.4 * average + 0.6 * student.exam;
}

double calculateFinalMedian(nameGrade& student) {
    sort(student.homework, student.homework + student.n);
    double median;
    if (student.n % 2 == 0) {
        median = (student.homework[student.n / 2 - 1] + student.homework[student.n / 2]) / 2.0;
    } else {
        median = student.homework[student.n / 2];
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
    nameGrade* students = new nameGrade[1];
    int m = 0;
    while (true) {
        cout << "Menu:\n1 - Enter data manually\n2 - Generate random grades\n3 - Generate random grades and names\n4 - Exit" << endl;
        int choice;
        cin >> choice;
        if (choice == 4) break;
        nameGrade newStudent;
        if (choice == 1) {
            readData(newStudent);
        } else if (choice == 2) {
            generateRandomGrades(newStudent);
        } else if (choice == 3) {
            generateRandomNames(newStudent);
            generateRandomGrades(newStudent);
        }
        if (newStudent.name == "0") break;
        
        nameGrade* newStudentsArray = new nameGrade[m + 1];
        for (int i = 0; i < m; ++i) {
            newStudentsArray[i] = students[i];
        }
        newStudentsArray[m] = newStudent;
        delete[] students;
        students = newStudentsArray;
        ++m;
    }
    
    for (int i = 0; i < m; ++i) {
        bool useAverage;
        cout << "Use average? (0/1): ";
        cin >> useAverage;
        printResults(students[i], useAverage);
    }
    
    for (int i = 0; i < m; ++i) {
        deleteStudentData(students[i]);
    }
    
    delete[] students;
    
    return 0;
}
