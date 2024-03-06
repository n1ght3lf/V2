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
    bool crash = 0;
    try
    {
        ifstream nameGradeHeader("nameGrade.h");
        ifstream nameGradeFunctionsHeader("nameGradeFunctions.h");
        ifstream nameConstantsHeader("nameConstants.h");
        ifstream nameGradeFunctionsCpp("nameGradeFunctions.cpp");
        ifstream kursiokai("kursiokai.txt");
        ifstream stud10000("studentai10000.txt");
        ifstream stud100000("studentai100000.txt");
        ifstream stud1000000("studentai1000000.txt");
        if (!nameGradeHeader.is_open())
        {
            cout << "nameGrade.h nerastas.\n";
            crash=1;
        }

        if (!nameGradeFunctionsHeader.is_open())
        {
            cout << "nameGradeFunctions.h nerastas.\n";
            crash=1;
        }

        if (!nameConstantsHeader.is_open())
        {
            cout << "nameConstants.h nerastas.\n";
            crash=1;
        }

        if (!nameGradeFunctionsCpp.is_open())
        {
            cout << "nameGradeFunctions.cpp nerastas.\n";
            crash=1;
        }

        if (!kursiokai.is_open())
        {
            cout << "studentai10000.txt nerastas.\n";
            crash=1;
        }

        if (!stud10000.is_open())
        {
            cout << "studentai10000.txt nerastas.\n";
            crash=1;
        }
        if (!stud100000.is_open())
        {
            cout << "studentai100000.txt nerastas.\n";
            crash=1;
        }
        if (!stud1000000.is_open())
        {
            cout << "studentai1000000.txt nerastas.\n";
            crash=1;
        }
        if (crash == 1)
        {
            throw runtime_error("Pridėkite reikalingus failus.");
        }

        while (true)
        {
            cout << "Meniu:\n1 - Įvesti duomenis ranka\n2 - Sugeneruoti atsitiktinius pažymius\n3 - Sugeneruoti atsitiktinius pažymius ir vardus\n4 - Įvestis iš failo\n5 - Išeiti\n6 - Testavimas" << endl;
            int choice;
            cin >> choice;
            if (cin.fail())
            {
                cout << "Netinkama įvestis \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (choice == 5)
                break;
            else if (choice == 6)
            {
                cout << "Įveskite studentų skaičių testavimui (1 - 10000, 2 - 100000, 3 - 1000000): ";
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
                    cout << "Netinkamas studentų skaičius." << endl;
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
                    total = chrono::duration_cast<chrono::duration<double>>(end - begin).count();
                    cout << "Užtrukta laiko įvedimui: " << total << endl;
                }
                else
                {
                    cout << "Nepavyko atidaryti failo." << endl;
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
                        total = chrono::duration_cast<chrono::duration<double>>(end - begin).count();
                        cout << "Užtrukta laiko įvedimui: " << total << endl;
                    }
                    else
                    {
                        cout << "Nepavyko atidaryti failo." << endl;
                    }
                }
                if (fileOutput)
                    break;
                if (newStudent.name == "0")
                    break;
                students.push_back(newStudent);
            }
        }

        int sortChoice;
        while (true)
        {
            cout << "Rūšiuoti pagal:\n1 - Vardą\n2 - Pavardę\n3 - Pažymių vidurkį\n4 - Pažymių medianą" << endl;
            cin >> sortChoice;
            if (cin.fail())
            {
                cout << "Netinkama įvestis \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }
        begin = chrono::high_resolution_clock::now();

        sortStudents(students, sortChoice);

        end = chrono::high_resolution_clock::now();
        total = chrono::duration_cast<chrono::duration<double>>(end - begin).count();
        cout << "Užtrukta laiko rūšiavimui: " << total << endl;

        bool outputChoice;
        while (true)
        {
            cout << "Pasirinkite išvesties vietą (0 - failas, 1 - ekranas): ";
            cin >> outputChoice;
            if (cin.fail())
            {
                cout << "Netinkama įvestis \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }
        begin = chrono::high_resolution_clock::now();
        if (outputChoice == 0)
        {
            fileOutput = true;
            ofstream outputFile("kursiokaiOut.txt");
            if (!outputFile.is_open())
            {
                cout << "Nepavyko atidaryti failo." << endl;
                return 1;
            }
            streambuf *originalCoutBuffer = cout.rdbuf();
            cout.rdbuf(outputFile.rdbuf()); // nukreipkite cout į failą
            cout << fixed << setprecision(2) << setw(20) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(20) << left << "Galutinis(Vid.)" << setw(20) << left << "Galutinis(Med.)" << endl;
            cout << "--------------------------------------------------------------------------" << endl;

            for (size_t i = 0; i < students.size(); ++i)
            {
                printResults(students[i]);
            }
            cout.rdbuf(originalCoutBuffer); // Atstatyti originalų cout buferį
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
        total = chrono::duration_cast<chrono::duration<double>>(end - begin).count();
        cout << "Užtrukta laiko išvesties: " << total << endl;

        for (size_t i = 0; i < students.size(); ++i)
        {
            deleteStudentData(students[i]);
        }

        return 0;
    }
    catch (const runtime_error &e)
    {
        cout << "Klaida: " << e.what() << endl;
        return 1;
    }
}
