#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct nameGrade
{
  string Name, LastName;
  float HomeWorkResults = 0, ExamGrade, Medianaa;
};

int main()
{
  int StudentAmount, HomeWorkAmount;
  bool medianOrAverage;
  float Temporary = 0, B[HomeWorkAmount + 1];
  cout << "Student and homework amounts:\n";
  cin >> StudentAmount >> HomeWorkAmount;
  nameGrade A[StudentAmount];
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
