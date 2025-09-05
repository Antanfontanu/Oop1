#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;

struct Studentas{
    string var;
    string pav;
    vector <int> paz;
    int egz;
    double gal;
};

Studentas Stud_iv();

int main(){
    int m;
    vector<Studentas> Grupe;
    cout<<"Kiek studentų grupėje? "; cin>> m;
    for (auto z=0; z<m; z++)
        Grupe.push_back(Stud_iv());

    cout << "Studento informacija: " << endl;
    for (auto& Past:Grupe) 
    {
        cout << setw(10) << left << Past.var 
             << "|" << setw(15) << right << Past.pav << "|" ;
        for (auto& a : Past.paz) cout << setw(3) << a << "|";
        cout << setw(5) << Past.egz << "|"
             << setw(10) << fixed << setprecision(2) << Past.gal << endl;
    }
}

Studentas Stud_iv(){
    int n, laik_paz, sum=0;
    Studentas Pirmas;
    cout << "Įveskite studento duomenis" << endl;
    cout << "Vardas: "; cin >> Pirmas.var; 
    cout << "Pavardė: "; cin >> Pirmas.pav; 
    cout << "Kiek pažymių turi " << Pirmas.var << " " << Pirmas.pav << " : "; cin >> n;
    for (int a = 0; a < n; a++){
        cout << a+1 << ": "; cin >> laik_paz;
        Pirmas.paz.push_back(laik_paz);
        sum += laik_paz;
    }
    cout << "Įveskite egzamino pažymį: "; cin >> Pirmas.egz;
    if (n>0)
        Pirmas.gal = double(sum)/double(n) * 0.4 + Pirmas.egz * 0.6;
    else
        Pirmas.gal = Pirmas.egz;
    return Pirmas;
}
