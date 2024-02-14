#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

/*
    Sukurkite pirmą Github projektą ir jame šaką (branch) - v.pradinė.

    Pagal aprašytus užduoties reikalavimus realizuokite programą, kuri nuskaito vartotojų įvedamus reikiamus duomenis (patogiausiai naudoti struktūrą):
        string tipo: studento vardas ir pavardė;
        int tipo: namų darbų tarpiniai rezultatai ir egzamino rezultatas;

    Baigus duomenų įvedimą, suskaičiuoja galutinį balą ir juos pateikia į ekraną tokiu ar panašiu pavidalu (galutinis
        apskaičiuotas balas pateikiamas dviejų skaičių po kablelio tikslumu):

    Papildykite programą, kad vietoj vidurkio galutinio balo skaičiavimui būtų galima naudoti ir medianą.
        Tuomet išvedimas (output’as) turėtų atrodyti panašiai į šį, kur tik vienas pasirinktas Galutinis (Vid.) arba Galutinis (Med.) yra išvedamas:

    first subrelease v.pradinė
    --------------------------
    branch v0.1 (continue later)


    galutinis = 0,4*vidurkis + 0,6*egzaminas
    2 3
    Andrius ads 7.23 4.81 2.92 4.21
    Ugnius sad 4.23 5.91 4.50 9


    292 421 491 723
    423 450 591 9.0
    452 735
    481 450
*/
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
  // cout<<"Student and homework amounts:\n";
  cin >> StudentAmount >> HomeWorkAmount;
  nameGrade A[StudentAmount];
  for (int i = 0; i < StudentAmount; i++)
  {
    // cout<< "Name, last name and all homework results:\n";
    cin >> A[i].Name >> A[i].LastName;
    for (int j = 0; j < HomeWorkAmount; j++)
    {
      cin >> B[j];
      A[i].HomeWorkResults += B[j];
      // cout << A[i].HomeWorkResults << endl;
    }
    //  cout<<"Exam results:\n";
    cin >> A[i].ExamGrade;
    B[HomeWorkAmount] = A[i].ExamGrade;
    sort(B, B + HomeWorkAmount);
  //  cout<<HomeWorkAmount<<" "<<+1<<" "<<HomeWorkAmount%2<<endl;
    if (HomeWorkAmount+1 % 2 == 0)
    {
      A[i].Medianaa = (B[HomeWorkAmount / 2] + B[(HomeWorkAmount / 2) + 1]) / 2;
      cout<<"Median"<<A[i].Medianaa<<endl;
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
