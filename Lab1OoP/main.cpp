#include <iostream>
#include <fstream>
using namespace std;

struct nameGrade {
  string name, lastName;
  float results, averageGrade, medianGrade;
};

int main(){
  ifstream in("import.txt");
  int n=0;
  cout<<"Įveskite kelių studentų rezultatus tikrinsite"<<endl;
  while (1<2){
    cin>>n;
    if (n<50 && n>0) break;
    if (n>50) cout<<"Skaičius per didelis"<<endl;
    if (n<1) cout<<"Skaičius per mažas"<<endl;
  }
  nameGrade person[n];
  for (int i = 0 ; i < n ; i++){
  }
  return 0;
}
