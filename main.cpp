#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <random>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>
#include <chrono>
using namespace std;

const vector<string> maleNames = {"Adas", "Aidas", "Albertas", "Dovydas", "Jonas", "Lukas"};
const vector<string> maleLastNames = {"Adomaitis", "Petrauskas", "Butkus", "Stankevicius", "Kazlauskas", "Urbonas", "Jakubauskas", "Jankunas"};
const vector<string> femaleNames = {"Donata", "Doroteja", "Rugile", "Ruta", "Skaiste"};
const vector<string> femaleLastNames = {"Petrauskaite", "Urbonaite", "Jakubauskaite", "Jankunaite", "Degutyte", "Ivanauskaite", "Varnaite"};

struct nameGrade
{
    string name;
    string surname;
    vector<int> homework;
    int exam;
    double final;
};

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

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    vector<nameGrade> students;
    bool fileOutput = false;
    double total = 0;
    auto begin = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();

    while (true)
    {
        cout << "Menu:\n1 - Enter data manually\n2 - Generate random grades\n3 - Generate random grades and names\n4 - Input from file\n5 - Exit\n6 - Testing" << endl;
        int choice;
        cin >> choice;
        if (choice == 5)
            break;
        else if (choice == 6)
        {
            cout << "Enter the number of students to test (1 - 10000, 2 - 100000, 3 - 1000000): ";
            int numStudents;
            cin >> numStudents;
            string filename;
            switch (numStudents)
            {
            case 1:
                filename = "studentai10000.txt";
                break;
            case 2:
                filename = "studentai100000.txt";
                break;
            case 3:
                filename = "studentai1000000.txt";
                break;
            default:
                cout << "Invalid number of students." << endl;
                break;
            }
            ifstream file(filename);
            if (file.is_open())
            {
                begin = chrono::high_resolution_clock::now();
                string firstLine;
                getline(file, firstLine);
                int numHomework = count(firstLine.begin(), firstLine.end(), 'N');
                while (getline(file, firstLine))
                {
                    istringstream iss(firstLine);
                    nameGrade newStudent;
                    iss >> newStudent.name >> newStudent.surname;
                    for (int i = 0; i < numHomework; ++i)
                    {
                        int grade;
                        iss >> grade;
                        newStudent.homework.push_back(grade);
                    }
                    iss >> newStudent.exam;
                    students.push_back(newStudent);
                }
                file.close();
                fileOutput = true;
                end = chrono::high_resolution_clock::now();
                total += chrono::duration_cast<chrono::duration<double>>(end - begin).count();
                cout<<"Time taken for input: "<<total<<endl;
            }
            else
            {
                cout << "Unable to open file." << endl;
            }
        }
        else
        {
            nameGrade newStudent;
            if (choice == 1)
            {
                readData(newStudent);
            }
            else if (choice == 2)
            {
                generateRandomGrades(newStudent, true);
            }
            else if (choice == 3)
            {
                generateRandomNames(newStudent);
                generateRandomGrades(newStudent, false);
            }
            else if (choice == 4)
            {
                begin = chrono::high_resolution_clock::now();
                ifstream file("kursiokai.txt");
                if (file.is_open())
                {
                    string firstLine;
                    getline(file, firstLine);
                    int numHomework = count(firstLine.begin(), firstLine.end(), 'N');
                    while (getline(file, firstLine))
                    {
                        istringstream iss(firstLine);
                        nameGrade newStudent;
                        iss >> newStudent.name >> newStudent.surname;
                        for (int i = 0; i < numHomework; ++i)
                        {
                            int grade;
                            iss >> grade;
                            newStudent.homework.push_back(grade);
                        }
                        iss >> newStudent.exam;
                        students.push_back(newStudent);
                    }
                    file.close();
                    fileOutput = true;
                    end = chrono::high_resolution_clock::now();
                    total += chrono::duration_cast<chrono::duration<double>>(end - begin).count();
                    cout<<"Time taken for input: "<<total<<endl;
                }
                else
                {
                    cout << "Unable to open file." << endl;
                }
            }
            if (fileOutput)
                break;
            if (newStudent.name == "0")
                break;
            students.push_back(newStudent);
        }
    }

    cout << "Sort by:\n1 - Name\n2 - Lastname\n3 - Grade (average)\n4 - Grade (median)" << endl;
    int sortChoice;
    cin >> sortChoice;
    begin = chrono::high_resolution_clock::now();
    
    sortStudents(students, sortChoice);

    end = chrono::high_resolution_clock::now();
    total += chrono::duration_cast<chrono::duration<double>>(end - begin).count();
    cout<<"Time taken for sorting: "<<total<<endl;

    bool outputChoice;
    cout << "Choose the output destination (0 for file, 1 for screen): ";
    cin >> outputChoice;
    begin = chrono::high_resolution_clock::now();
    if (outputChoice == 0)
    {
        fileOutput = true;
        ofstream outputFile("kursiokaiOut.txt");
        if (!outputFile.is_open())
        {
            cout << "Unable to open file." << endl;
            return 1;
        }
        streambuf *originalCoutBuffer = cout.rdbuf();
        cout.rdbuf(outputFile.rdbuf()); //redirect cout to the file
        cout << fixed << setprecision(2) << setw(20) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(20) << left << "Galutinis(Vid.)" << setw(20) << left << "Galutinis(Med.)" << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        for (size_t i = 0; i < students.size(); ++i)
        {
            printResults(students[i]);
        }
        cout.rdbuf(originalCoutBuffer); // Restore original cout buffer
    }
    else
    {
        cout << fixed << setprecision(2) << setw(20) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(20) << left << "Galutinis(Vid.)" << setw(20) << left << "Galutinis(Med.)" << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        for (size_t i = 0; i < students.size(); ++i)
        {
            printResults(students[i]);
        }
    }

    end = chrono::high_resolution_clock::now();
    total += chrono::duration_cast<chrono::duration<double>>(end - begin).count();
    cout<<"Time taken for output: "<<total<<endl;

    for (size_t i = 0; i < students.size(); ++i)
    {
        deleteStudentData(students[i]);
    }

    return 0;
}
