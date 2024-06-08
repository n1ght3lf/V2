#include "input.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <chrono>

using namespace std;

bool getMedianPreference()
{
    string userInput;
    while (true)
    {
        try
        {
            cout << "Ar norite galutinio balo skaičiavimui naudoti medianą? (1 - taip, 0 - ne): ";
            cin >> userInput;
            if (userInput == "0")
            {
                return false;
            }
            else if (userInput == "1")
            {
                return true;
            }
            else
            {
                throw invalid_argument("Neteisinga įvestis. Prašome įvesti 0 arba 1.");
            }
        }
        catch (const invalid_argument &e)
        {
            cout << e.what() << endl;
        }
    }
}

void processStudents(vector<Student> &students, bool Median, chrono::high_resolution_clock::time_point startTotal)
{
    Student student;
    int menuChoice;
    int addMoreStudents;

    while (true)
    {
        try
        {
            menuChoice = Menu();
        }
        catch (const exception &e)
        {
            cerr << "Įvyko klaida: " << e.what() << '\n';
            continue;
        }

        if (menuChoice == 1)
        {
            do
            {
                try
                {
                    input(student, Median);
                    students.push_back(student);
                }
                catch (const exception &e)
                {
                    cerr << e.what() << '\n';
                }

                while (true)
                {
                    cout << "Ar norite suvesti dar vieno studento pažymius? (1 - taip, 0 - ne): ";
                    cin >> addMoreStudents;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                    }
                    else if (addMoreStudents == 0 || addMoreStudents == 1)
                    {
                        break;
                    }
                    else
                    {
                        cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                    }
                }
            } while (addMoreStudents == 1);
        }
        else if (menuChoice == 2)
        {
            do
            {
                try
                {
                    student.firstName = isString("Įveskite studento vardą: ");
                    student.lastName = isString("Įveskite studento pavardę: ");
                    for (int j = 0; j < 5; j++)
                    {
                        student.homeworkResults.push_back(generateGrade());
                    }
                    student.examResults = generateGrade();
                    students.push_back(student);

                    while (true)
                    {
                        cout << "Ar norite sugeneruoti dar vieno studento pažymius? (1 - taip, 0 - ne): ";
                        cin >> addMoreStudents;

                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                        }
                        else if (addMoreStudents == 0 || addMoreStudents == 1)
                        {
                            break;
                        }
                        else
                        {
                            cerr << "Neteisinga įvestis. Prašome įvesti 0 arba 1." << endl;
                        }
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Įvyko klaida: " << e.what() << '\n';
                }
            } while (addMoreStudents == 1);
        }
        else if (menuChoice == 3)
        {
            int numOfGenStudents;

            while (true)
            {
                try
                {
                    cout << "Įveskite kiek studentų duomenų norite sugeneruoti: ";
                    cin >> numOfGenStudents;

                    if (cin.fail() || numOfGenStudents < 1)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw invalid_argument("Neteisinga įvestis. Prašome įvesti teigiamą skaičių.");
                    }
                    break;
                }
                catch (const exception &e)
                {
                    cerr << "Įvyko klaida: " << e.what() << '\n';
                }
            }

            for (int i = 0; i < numOfGenStudents; i++)
            {
                student.firstName = generateName();
                student.lastName = generateLastName();
                for (int j = 0; j < 5; j++)
                {
                    student.homeworkResults.push_back(generateGrade());
                }
                student.examResults = generateGrade();
                students.push_back(student);
            }
        }
        else if (menuChoice == 4)
        {
            try
            {
                string inputFileName = getFilenameFromUser();
                ifstream InputFile(inputFileName);
                cout << "\nFailas " << '"' << inputFileName << '"' << " nuskaitytas sėkmingai." << endl;
                readData(InputFile, students);
            }
            catch (const runtime_error &e)
            {
                cerr << e.what() << '\n';
            }
            catch (const exception &e)
            {
                cerr << "Įvyko klaida: " << e.what() << '\n';
            }
        }
        else if (menuChoice == 5)
        {
            try
            {
                string inputFileName = getFilenameFromUser();
                ifstream InputFile(inputFileName);
                cout << "\nFailas " << '"' << inputFileName << '"' << " atidarytas sėkmingai." << endl;
                vector<string> filenames;
                filenames.push_back(inputFileName);
                testFiles(filenames);
            }
            catch (const runtime_error &e)
            {
                cerr << e.what() << '\n';
            }
            catch (const exception &e)
            {
                cerr << "Įvyko klaida: " << e.what() << '\n';
            }
        }
        else if (menuChoice == 6)
        {
            try
            {
                int studentCounts[] = {1000, 10000, 100000, 1000000, 10000000};

                for (int i = 0; i < sizeof(studentCounts) / sizeof(studentCounts[0]); i++)
                {

                    generateFile(studentCounts[i]);

                    vector<string> filenames = {"studentai" + to_string(studentCounts[i]) + ".txt"};
                    openFiles(filenames, Median);
                }
            }
            catch (const exception &e)
            {
                cerr << "Įvyko klaida: " << e.what() << '\n';
            }
        }
        else if (menuChoice == 7)
        {
            if (!students.empty())
            {
                cout << "Įveskite kaip norite išrušiuoti studentus: 1 - pagal vardą, 2 - pagal pavardę, 3 - pagal galutinį balą: ";
                int criteria;

                while (true)
                {
                    try
                    {
                        cin >> criteria;

                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw runtime_error("Netinkama įvestis, įveskite skaičių 1, 2 arba 3.");
                        }

                        if (criteria != 1 && criteria != 2 && criteria != 3)
                        {
                            throw runtime_error("Netinkama įvestis, įveskite skaičių 1, 2 arba 3.");
                        }

                        break;
                    }
                    catch (const runtime_error &e)
                    {
                        cout << e.what() << endl;
                    }
                }

                try
                {
                    sortStudents(students, criteria, Median);
                    vector<Student> kietiakai;
                    vector<Student> nuskriaustukai;

                    for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it)
                    {
                        double finalGrade = calculateFinalGrade(*it, Median);

                        if (finalGrade < 5.0)
                        {
                            nuskriaustukai.push_back(*it);
                        }
                        else
                        {
                            kietiakai.push_back(*it);
                        }
                    }

                    cout << "Įveskite kaip norite išvesti studentus: 1 - į ekraną, 2 - į failus: ";
                    int choice;
                    cin >> choice;

                    if (choice == 1)
                    {
                        outputToTerminal(nuskriaustukai, kietiakai, Median);
                    }
                    else if (choice == 2)
                    {
                        outputToFile(nuskriaustukai, nuskriaustukai.size(), Median, "nuskriaustukai.txt");
                        outputToFile(kietiakai, kietiakai.size(), Median, "kietiakai.txt");
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Įvyko klaida rušiuojant / išvedant studentus \n";
                }

                auto endTotal = chrono::high_resolution_clock::now();
                chrono::duration<double> diffTotal = endTotal - startTotal;
                double totalTime = diffTotal.count();

                cout << "\nVisos programos veikimo laikas: " << std::fixed << std::setprecision(6) << totalTime << " sekundės\n"
                     << endl;
            }

            break;
        }
    }
}

int Menu()
{
    int menuChoice;
    cout << "\n1 - Suvesti ranka\n";
    cout << "2 - Generuoti pažymius\n";
    cout << "3 - Generuoti ir pažymius, vardus, pavardes\n";
    cout << "4 - Skaityti iš failo\n";
    cout << "5 - Atidaryti testavimo failus\n";
    cout << "6 - Sugeneruoti ir testuoti penkis failus\n";
    cout << "7 - Išvedimas\n";
    cout << "\nĮveskite skaičių: ";
    cin >> menuChoice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Netinkama įvestis, įveskite skaičių tarp 1 ir 7." << endl;
    }
    else if (menuChoice < 1 || menuChoice > 7)
    {
        cerr << "Netinkama įvestis, įveskite skaičių tarp 1 ir 7." << endl;
    }
    else
    {
        return menuChoice;
    }
}

string getFilenameFromUser()
{
    cout << "Įveskite norimo failo pavadinimą (kursiokai.txt, studentai1000.txt, studentai10000.txt, studentai100000.txt, studentai1000000.txt, studentai10000000.txt): \n";
    string inputFileName;
    cin >> inputFileName;
    ifstream InputFile(inputFileName);
    if (!InputFile)
    {
        throw runtime_error("Failas " + inputFileName + " nerastas.");
    }
    return inputFileName;
}

void readData(ifstream &InputFile, vector<Student> &students)
{
    string buffer;
    getline(InputFile, buffer);
    while (getline(InputFile, buffer))
    {
        stringstream ss(buffer);
        vector<int> grades;
        Student s;
        ss >> s.firstName >> s.lastName;
        int grade;
        while (ss >> grade)
        {
            grades.push_back(grade);
        }
        if (ss.fail() && !ss.eof())
        {
            throw runtime_error("Nepavyko nuskaityti pažymio.");
        }
        if (!grades.empty())
        {
            s.examResults = grades.back();
            grades.pop_back();
        }
        s.homeworkResults = grades;
        students.push_back(s);
    }
}

void openFiles(const vector<string> &filenames, bool Median)
{
    for (const auto &inputFileName : filenames)
    {
        ifstream InputFile(inputFileName);
        vector<Student> students;
        double readTime = 0.0, sortTime = 0.0, outputTime = 0.0;

        auto startReadTime = chrono::high_resolution_clock::now();
        readData(InputFile, students);
        auto endReadTime = chrono::high_resolution_clock::now();
        readTime = chrono::duration<double>(endReadTime - startReadTime).count();

        auto startSortTime = chrono::high_resolution_clock::now();
        sortStudents(students, 3, Median);
        vector<Student> kietiakai, nuskriaustukai;
        for (auto &student : students)
        {
            double finalGrade = calculateFinalGrade(student, Median);
            if (finalGrade < 5.0)
            {
                nuskriaustukai.push_back(student);
            }
            else
            {
                kietiakai.push_back(student);
            }
        }
        auto endSortTime = chrono::high_resolution_clock::now();
        sortTime = chrono::duration<double>(endSortTime - startSortTime).count();

        auto startOutputTime = chrono::high_resolution_clock::now();
        outputToFile(nuskriaustukai, nuskriaustukai.size(), Median, "nuskriaustukai.txt");
        outputToFile(kietiakai, kietiakai.size(), Median, "kietiakai.txt");
        auto endOutputTime = chrono::high_resolution_clock::now();
        outputTime = chrono::duration<double>(endOutputTime - startOutputTime).count();

        InputFile.clear();
        InputFile.seekg(0);
        InputFile.close();

        cout << "\nFailas: " << inputFileName << endl;
        cout << "Nuskaitymui: " << std::fixed << std::setprecision(6) << readTime << " sekundės\n";
        cout << "Rūšiavimui: " << std::fixed << std::setprecision(6) << sortTime << " sekundės\n";
        cout << "Išvedimui: " << std::fixed << std::setprecision(6) << outputTime << " sekundės\n";
        cout << "Visas laikas: " << std::fixed << std::setprecision(6) << readTime + sortTime + outputTime << " sekundės\n";
    }
}

void input(Student &student, bool &Median)
{
    student.firstName = isString("Įveskite studento vardą: ");
    student.lastName = isString("Įveskite studento pavardę: ");
    student.homeworkResults.clear();
    while (true)
    {
        int result = isGrade("Įveskite namų darbo pažymį arba -1, jei baigėte: ");
        if (result == -1)
        {
            break;
        }
        student.homeworkResults.push_back(result);
    }
    student.examResults = isGrade("Įveskite studento egzamino rezultatą: ");
}
