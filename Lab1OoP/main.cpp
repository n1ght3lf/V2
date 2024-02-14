#include <iostream>
#include <iomanip>
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
*/
struct nameGrade
{
  string Name, LastName;
  float HomeWorkResults = 0, ExamGrade;
};

int main()
{
  int StudentAmount, HomeWorkAmount;
  float Temporary;
  // cout<<"Student and homework amounts:\n";
  cin >> StudentAmount >> HomeWorkAmount;
  nameGrade A[StudentAmount];
  for (int i = 0; i < StudentAmount; i++)
  {
    // cout<< "Name, last name and all homework results:\n";
    cin >> A[i].Name >> A[i].LastName;
    for (int j = 0; j < HomeWorkAmount; j++)
    {
      cin >> Temporary;
      A[i].HomeWorkResults += Temporary;
      //cout << A[i].HomeWorkResults << endl;
    }
    A[i].HomeWorkResults /= HomeWorkAmount;
    //  cout<<"Exam results:\n";
    cin >> A[i].ExamGrade;
    Temporary = 0;
  }
  cout << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(25) << "Galutinis(vid.)\n"<<"--------------------------------------------------\n";
  for (int i = 0; i < StudentAmount; i++)
  {
    Temporary = (A[i].HomeWorkResults * 0.4) + (A[i].ExamGrade * 0.6);
    cout << setw(15) << A[i].LastName << setw(15) << A[i].Name << setw(15) << fixed << setprecision(2) << Temporary << endl;
  }
}
