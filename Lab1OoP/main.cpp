#include <iostream>
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
*/
struct nameGrade
{
  string Name, LastName;
  float HomeWorkResults, ExamGrade;
};

int main()
{
  int StudentAmount, HomeWorkAmount;
  cout<<"Student and homework amounts:\n";
  cin >> StudentAmount >> HomeWorkAmount;
  nameGrade A[StudentAmount];
  for (int i = 0; i < StudentAmount; i++)
  {
    cout<< "Name, last name and all homework results:\n";
    cin >> A[i].Name >> A[i].LastName;
    for (int i = 0; i < HomeWorkAmount; i++)
    {
      cin >> A[i].HomeWorkResults;
    }
    cout<<"Exam results:";
    cin >> A[i].ExamGrade;
  }
  
}
