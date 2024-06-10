#include "input.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

/// @brief Displays the menu and prompts the user to choose an option.
/// @return The user's menu choice.

bool getMedianPreference()
{
    string a;
    while (true)
    {
        try
        {
            cout << "Ar norite galutinio balo skaičiavimui naudoti medianą? (1 - taip, 0 - ne): ";
            cin >> a;
            if (a == "0")
            {
                return false;
            }
            else if (a == "1")
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

/// @brief Processes student data based on user input. 
/// @tparam Container The type of container used to store student data (e.g., vector, list).
/// @param students The container holding student data.
/// @param Median Flag indicating whether to calculate median or average.
/// @param startTotal The starting time point for measuring total execution time.

template <typename Container>
void processStudents(Container &students, bool Median, chrono::high_resolution_clock::time_point startTotal)
{
    Student data;
    int menuChoice;
    int addMoreStudents;
    int studentCounts[] = {1000, 10000, 100000, 1000000, 10000000};
    do
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
        switch (menuChoice)
        {
        case 1:
        {
            do
            {
                try
                {
                    input(data, Median);
                    students.push_back(data);
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
            break;
        }
        case 2:
        {
            do
            {
                try
                {
                    data.setFirstName(isString("Įveskite studento vardą: "));
                    data.setLastName(isString("Įveskite studento pavardę: "));
                    for (int j = 0; j < 5; j++)
                    {
                        data.addHomeworkMark(generateGrade());
                    }
                    data.setExamMark(generateGrade());
                    students.push_back(data);
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
            break;
        }
        case 3:
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
                data.setFirstName(generateName());
                data.setLastName(generateLastName());
                for (int j = 0; j < 5; j++)
                {
                    data.addHomeworkMark(generateGrade());
                }
                data.setExamMark(generateGrade());
                students.push_back(data);
            }
            break;
        }
        case 4:
        {
            try
            {
                string inputFileName = getFilenameFromUser();
                ifstream inputFile(inputFileName);
                cout << "\nFailas " << '"' << inputFileName << '"' << " nuskaitytas sėkmingai." << endl;
                readData(inputFile, students);
            }
            catch (const runtime_error &e)
            {
                cerr << e.what() << '\n';
            }
            catch (const exception &e)
            {
                cerr << "Įvyko klaida: " << e.what() << '\n';
            }
            break;
        }
        case 5:
        {
            try
            {
                for (int i = 0; i < sizeof(studentCounts) / sizeof(studentCounts[0]); i++)
                {
                    generateFile(studentCounts[i]);
                }
                cout << "\nFailai sukurti sėkmingai." << endl;
            }
            catch (const exception &e)
            {
                cerr << "Įvyko klaida: " << e.what() << '\n';
            }
            break;
        }
        case 6:
        {
            try
            {
                cout << "Pasirinkite strategiją (1, 2, 3): ";
                int strategy;
                while (!(cin >> strategy) || (strategy != 1 && strategy != 2 && strategy != 3))
                {
                    cout << "Neteisinga įvestis. Prašome įvesti 1, 2 arba 3.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                for (int i = 0; i < sizeof(studentCounts) / sizeof(studentCounts[0]); i++)
                {
                    vector<string> filenames = {"studentai" + to_string(studentCounts[i]) + ".txt"}; // sudedame sugeneruotus failus i vektoriu
                    for (int i = 0; i < sizeof(studentCounts) / sizeof(studentCounts[0]); i++)
                {
                    generateFile(studentCounts[i]);
                    vector<string> filenames = {"studentai" + to_string(studentCounts[i]) + ".txt"};
                    openFiles<Container>(filenames, students, Median, strategy);;
                }
                cout << "\nFailai sukurti ir apdoroti sėkmingai." << endl;
                break;
                }
            }
            catch (const exception &e)
            {
                cerr << "Įvyko klaida: " << e.what() << '\n';
            }
            break;
        }
        case 7:
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
                    for (auto it = students.begin(); it != students.end(); ++it)
                    {                                                        // skirstome studentus i dvi kategorijas
                        double finalGrade = it->calculateFinalGrade(Median); // calculate final grade using the method
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

                cout << "\nVisos programos veikimo laikas: " << fixed << setprecision(6) << totalTime << " sekundės\n"
                     << endl;
            }
            break;
        }
        case 8:
        {
            try
            {
                // 
                vector<int> HomeworkMarks = {5, 6, 7, 8};
                Student s1("Dominykas", "Jurevičius", 10, HomeworkMarks);
                Student s2(s1); // Copy constructor
                if (!(s2.getFirstName() == s1.getFirstName() && s2.getLastName() == s1.getLastName() && s2.getExamMark() == s1.getExamMark() && s2.getHomeworkMarks() == s1.getHomeworkMarks()))
                {
                    cerr << "Kopijavimo konstruktoriaus testas nepavyko.\n";
                    return;
                }
                else
                {
                    cout << "Kopijavimo konstruktoriaus testas sėkmingas.\n";
                }

                Student s3(move(s1)); // Move constructor
                if (!(s3.getFirstName() == "Dominykas" && s3.getLastName() == "Jurevičius" && s3.getExamMark() == 10 && s3.getHomeworkMarks() == HomeworkMarks))
                {
                    cerr << "Perkėlimo konstruktoriaus testas nepavyko.\n";
                    return;
                }
                else
                {
                    cout << "Perkėlimo konstruktoriaus testas sėkmingas.\n";
                }

                // Test assignment operators
                Student s4;
                s4 = s2; // Copy assignment operator
                if (!(s4.getFirstName() == s2.getFirstName() && s4.getLastName() == s2.getLastName() && s4.getExamMark() == s2.getExamMark() && s4.getHomeworkMarks() == s2.getHomeworkMarks()))
                {
                    cerr << "Kopijavimo priskyrimo operatorius nepavyko.\n";
                    return;
                }
                else
                {
                    cout << "Kopijavimo priskyrimo operatorius sėkmingas.\n";
                }

                Student s5;
                s5 = move(s4); // Move assignment operator
                if (!(s5.getFirstName() == "Dominykas" && s5.getLastName() == "Jurevičius" && s5.getExamMark() == 10 && s5.getHomeworkMarks() == HomeworkMarks))
                {
                    cerr << "Perkėlimo priskyrimo operatorius nepavyko.\n";
                    return;
                }
                else
                {
                    cout << "Perkėlimo priskyrimo operatorius sėkmingas.\n";
                }

                // Test input operator
                istringstream iss("Dominykas Jurevičius 5 6 7 8 10");
                Student s6;
                iss >> s6; // Input operator
                if (!(s6.getFirstName() == "Dominykas" && s6.getLastName() == "Jurevičius" && s6.getExamMark() == 10 && s6.getHomeworkMarks() == vector<int>{5, 6, 7, 8}))
                {
                    cerr << "Įvesties operatoriaus testas nepavyko. \n";
                    return;
                }
                else
                {
                    cout << "Įvesties operatoriaus testas sėkmingas.\n";
                }

                // Test output operator
                string expectedOutput = "Dominykas Jurevičius 5 6 7 8 10";
                if (studentData(s6) != expectedOutput)
                {
                    cerr << "Išvesties operatoriaus testas nepavyko. \n";
                    return;
                }
                else
                {
                    cout << "Išvesties operatoriaus testas sėkmingas.\n";
                }

                cout << "Testai baigti. Visi metodai veikia.\n";
            }
            catch (const exception &e)
            {
                cerr << "An error occurred: " << e.what() << '\n';
            }
            break;
        }
        }
    } while (menuChoice != 8 && menuChoice != 7 && menuChoice != 6);
}

template void processStudents(vector<Student> &students, bool Median, chrono::high_resolution_clock::time_point startTotal);
template void processStudents(deque<Student> &students, bool Median, chrono::high_resolution_clock::time_point startTotal);
template void processStudents(list<Student> &students, bool Median, chrono::high_resolution_clock::time_point startTotal);

/// @brief Displays the menu and prompts the user to choose an option.
/// @return The user's menu choice.
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
    cout << "8 - I/O + 'Rule of five'\n";
    cout << "\nĮveskite skaičių: ";
    cin >> menuChoice;
    if (menuChoice < 1 || menuChoice > 8)
    {
        throw runtime_error("Netinkama įvestis, įveskite skaičių tarp 1 ir 8.");
    }
    return menuChoice;
}
/// @brief Prompts the user to enter a filename.
/// @return The filename entered by the user.
string getFilenameFromUser()
{
    cout << "Įveskite norimo failo pavadinimą (kursiokai.txt, studentai1000.txt, studentai10000.txt, studentai100000.txt, studentai1000000.txt, studentai10000000.txt): \n";
    string inputFileName;
    cin >> inputFileName;
    ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        throw runtime_error("Failas " + inputFileName + " nerastas.");
    }
    return inputFileName;
}
/// @brief Reads student data from a file and populates the container.
/// @tparam Container The type of container used to store student data.
/// @param inputFile The input file stream.
/// @param students The container to populate with student data.
template <typename Container>
void readData(ifstream& inputFile, Container& students) {
    string buffer; 
    getline(inputFile, buffer); 
    while (getline(inputFile, buffer)) {
        stringstream ss(buffer); 
        Student s; 
        if (!(ss >> s)) {
            throw runtime_error("Failed to read student.");
        }
        students.push_back(move(s));
    }
}

template void readData(ifstream &inputFile, vector<Student> &students);
template void readData(ifstream &inputFile, deque<Student> &students);
template void readData(ifstream &inputFile, list<Student> &students);
/// @brief Opens files containing student data and performs operations based on the chosen strategy.
/// @tparam Container The type of container used to store student data.
/// @param filenames The names of the input files.
/// @param students The container holding student data.
/// @param Median Flag indicating whether to calculate median or average.
/// @param strategy The strategy chosen for data processing.
template <typename Container>
void openFiles(const vector<string> &filenames, Container &students, bool Median, int strategy)
{
    for (const auto &inputFileName : filenames)
    {
        ifstream inputFile(inputFileName);
        double readTime = 0.0, sortTime = 0.0, outputTime = 0.0, distributionTime = 0.0;

        auto startReadTime = chrono::high_resolution_clock::now();
        readData(inputFile, students);
        auto endReadTime = chrono::high_resolution_clock::now();
        readTime = chrono::duration<double>(endReadTime - startReadTime).count();

        auto startSortTime = chrono::high_resolution_clock::now();
        sortStudents(students, 3, Median); // rusiuojame studentus pagal galutini bala
        auto endSortTime = chrono::high_resolution_clock::now();
        sortTime = chrono::duration<double>(endSortTime - startSortTime).count();

        auto startDistribution = chrono::high_resolution_clock::now();
        Container kietiakai, nuskriaustukai;
        if (strategy == 1)
        {
            for (auto &student : students)
            {
                double finalGrade = student.calculateFinalGrade(Median);
                if (finalGrade < 5.0)
                {
                    nuskriaustukai.push_back(student);
                }
                else
                {
                    kietiakai.push_back(student);
                }
            }
            students.clear();
        }
        else if (strategy == 2)
        {
            for (auto it = students.begin(); it != students.end();)
            {
                double finalGrade = it->calculateFinalGrade(Median);
                if (finalGrade < 5.0)
                {
                    nuskriaustukai.push_back(*it);
                    swap(*it, students.back());
                    students.pop_back();
                }
                else
                {
                    ++it;
                }
            }
            kietiakai = students;
        }
        else if (strategy == 3)
        {
            auto partitionPoint = partition(students.begin(), students.end(), [&](const Student &student)
                                            { return student.calculateFinalGrade(Median) >= 5.0; });

            copy(students.begin(), partitionPoint, back_inserter(kietiakai));
            copy(partitionPoint, students.end(), back_inserter(nuskriaustukai));
            students.clear();
        }
        auto endDistribution = chrono::high_resolution_clock::now();
        distributionTime = chrono::duration<double>(endDistribution - startDistribution).count();

        inputFile.clear();
        inputFile.seekg(0);
        inputFile.close();

        cout << "\nFailas: " << inputFileName << endl;
        cout << "Nuskaitymui: " << fixed << setprecision(6) << readTime << " sekundės" << endl;
        cout << "Rušiavimui " << fixed << setprecision(6) << sortTime << " sekundės" << endl;
        cout << "Išvedimui " << fixed << setprecision(6) << distributionTime << " sekundės" << endl;

        double timeCreateFile = readTime + sortTime + distributionTime;
        cout << "\nVisas laikas: " << fixed << setprecision(6) << timeCreateFile << " sekundės\n"
             << endl;
    }
}

template void openFiles(const vector<string> &filenames, vector<Student> &students, bool Median, int strategy);
template void openFiles(const vector<string> &filenames, deque<Student> &students, bool Median, int strategy);
template void openFiles(const vector<string> &filenames, list<Student> &students, bool Median, int strategy);
/// @brief Reads input data for a single student
/// @param data The Student object to populate with input data.
/// @param Median Flag indicating whether to calculate median or average.
void input(Student &data, bool &Median)
{
    data.setFirstName(isString("Įveskite studento vardą: "));
    data.setLastName(isString("Įveskite studento pavardę: "));
    data.clearHomeworkMarks(); // isvalome vektoriu
    vector<int> grades;
    while (true)
    {
        int result = isGrade("Įveskite namų darbo pažymį arba -1, jei baigėte: ");
        if (result == -1)
        {
            break;
        }
        grades.push_back(result);
    }
    if (!grades.empty())
    {
        data.setExamMark(grades.back());
        grades.pop_back();
    }
    data.setHomeworkMarks(move(grades));
}
/// @brief Converts a Student object to a string representation.
/// @param s The Student object.
/// @return A string representation of the Student object.
string studentData(const Student& s) {
    ostringstream oss;
    oss << s.getFirstName() << " " << s.getLastName() << " ";
    for (const auto& grade : s.getHomeworkMarks()) {
        oss << grade << " ";
    }
    oss << s.getExamMark();
    return oss.str();
}