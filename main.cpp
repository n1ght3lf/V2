#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "nameGrade.h"
#include "nameGradeFunctions.h"
#include "nameConstants.h"
using namespace std;

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
    total=0;
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
    total=0;
    total += chrono::duration_cast<chrono::duration<double>>(end - begin).count();
    cout<<"Time taken for output: "<<total<<endl;

    for (size_t i = 0; i < students.size(); ++i)
    {
        deleteStudentData(students[i]);
    }

    return 0;
}