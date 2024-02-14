#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;
/*
Papildykite programą taip, kad ji veiktu ir tokiu atveju, kai namų darbų ir įrašų skaičiai
(namų darbų - n, studentų skaičius - m) yra nežinomi iš anksto, t.y. tik įvedimo metu vartotojas nusprendžia kuomet jis jau įvedė visų namų darbų rezultatus ir kada jis
baigią žmonių įvedimą. Šią dalį reikia realizuoti dviem būdais (atskiri failai), kur visus studentus ir kiekvieno iš jų darbų rezultatus saugant į:
          C  masyvą (atskiras failas, visur turi būti naudojami tik C masyvai).
          std::vector  tipo konteinerį (atskiras failas, visur turi būti naudojami tik std::vector konteineriai).
Atliekant šią užduotį reikia sukurti du atskirus *.cpp failus ir C masyvams ir vector, tačiau toliau nuo 0.2 versijos naudosime tik vector versiją.

Papildykite programą taip, kad būtų galimybė, jog mokinio gautieji balai už namų darbus bei egzaminą būtų generuojami atsitiktinai.

Išleiskite pataisytą subrelizą (juodraštinis release failas) Github sistemoje su užvardinimu v0.1.*/
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
    cout << "Enter homework results, 0 to finish: ";
    int size = 1; // Initial array size
    student.homework = new double[size];
    int i = 0; //index
    while (true) {
        double input;
        cin >> input;
        if (input == 0) break;
        if (i == size) { // If the array is full, resize it
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
    cout << "Enter exam result: ";
    cin >> student.exam;
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

void deleteStudentData(nameGrade& student){

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
        nameGrade newStudent;
        readData(newStudent);
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
/*
int main()
{
  int StudentAmount, HomeWorkAmount;
  bool medianOrAverage;
  float Temporary = 0, B[HomeWorkAmount + 1];
  nameGrade* A = new nameGrade[];
  for (int i = 0; i < StudentAmount; i++)
  {
    cout << "Name, last name and all homework results:\n";
    cin >> A[i].Name >> A[i].LastName;
    for (int j = 0; j < HomeWorkAmount; j++)
    {
      cin >> B[j];
      A[i].HomeWorkResults += B[j];
    }
    cout << "Exam results:\n";
    cin >> A[i].ExamGrade;
    B[HomeWorkAmount] = A[i].ExamGrade;
    sort(B, B + HomeWorkAmount);
    if (HomeWorkAmount + 1 % 2 == 0)
    {
      A[i].Medianaa = (B[HomeWorkAmount / 2] + B[(HomeWorkAmount / 2) + 1]) / 2;
      cout << "Median" << A[i].Medianaa << endl;
    }
    else
    {
      A[i].Medianaa = B[HomeWorkAmount / 2];
    }
    A[i].HomeWorkResults /= HomeWorkAmount;
  }
  cout << "For median input 0, for average input 1 ";
  cin >> medianOrAverage;
  if (medianOrAverage == 1)
  {
    cout << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(25) << "Galutinis(vid.)\n"
         << "--------------------------------------------------\n";
    for (int i = 0; i < StudentAmount; i++)
    {
      Temporary = (A[i].HomeWorkResults * 0.4) + (A[i].ExamGrade * 0.6);
      cout << setw(15) << A[i].LastName << setw(15) << A[i].Name << setw(15) << fixed << setprecision(2) << Temporary << endl;
    }
  }
  else
  {
    cout << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(25) << "Galutinis(med.)\n"
         << "--------------------------------------------------\n";
    for (int i = 0; i < StudentAmount; i++)
    {
      cout << setw(15) << A[i].LastName << setw(15) << A[i].Name << setw(15) << fixed << setprecision(2) << A[i].Medianaa << endl;
    }
  }
}
*/