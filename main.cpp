#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

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
    vector<int> paz;
    int egz;
    double galVid;
    double galMed; 
};

Studentas Stud_iv();
double skaiciuotiMediana(vector<int> paz);

int main(){
    int m;
    vector<Studentas> Grupe;
    cout << "Kiek studentų grupėje: "; 
    cin >> m;
    cin.ignore(); // išvalom buferį po cin

    for (int z = 0; z < m; z++) 
        Grupe.push_back(Stud_iv());

    cout << "Pasirinkite galutinio balo skaičiavimo metodą:" << endl;
    cout << "1 - Vidurkis" << endl;
    cout << "2 - Mediana" << endl;
    cout << "3 - Abu" << endl;
    int pasirinkimas;
    cin >> pasirinkimas;

    // viršus rezultatų lentelės
    cout << "Studento informacija:" << endl;
    cout << setw(10) << left << "Vardas" << "|"
         << setw(15) << right << "Pavardė" << "|";
    cout << "Pažymiai|Egz.|";
    if(pasirinkimas == 1) cout << "Galutinis (Vid.)" << endl;
    else if(pasirinkimas == 2) cout << "Galutinis (Med.)" << endl;
    else cout << "Galutinis (Vid.)|Galutinis (Med.)" << endl;

    // rezultatai
    for (auto& Past : Grupe){
        cout << setw(10) << left << Past.var << "|"
             << setw(15) << right << Past.pav << "|";
        for(auto& a : Past.paz) cout << setw(3) << a << "|";
        cout << setw(5) << Past.egz << "|";

        if(pasirinkimas == 1) cout << setw(10) << fixed << setprecision(2) << Past.galVid << endl;
        else if(pasirinkimas == 2) cout << setw(10) << fixed << setprecision(2) << Past.galMed << endl;
        else cout << setw(10) << fixed << setprecision(2) << Past.galVid
                  << "|" << setw(10) << fixed << setprecision(2) << Past.galMed << endl;
    }
}

Studentas Stud_iv() {
    int sum = 0;
    Studentas Pirmas;

    cout << "Įveskite studento duomenis" << endl;
    cout << "Vardas: "; cin >> Pirmas.var; 
    cout << "Pavardė: "; cin >> Pirmas.pav; 
    cin.ignore(); // išvalom buferį po cin

    cout << "Įveskite pažymius (Paspauskite du kartus ENTER, jei norite baigti):" << endl;
    string eil;
    int tuscios_eil = 0;

    while (true) {
        cout << "Pažymys: ";
        getline(cin, eil);

        if (eil.empty()) {
            tuscios_eil++;
            if (tuscios_eil == 2) break; // du tušti ENTER -> pabaiga
            else continue;
        } else {
            tuscios_eil = 0;
        }

        try {
            int laik_paz = std::stoi(eil);
            Pirmas.paz.push_back(laik_paz);
            sum += laik_paz;
        } catch (...) {
            cout << "Reikia įvesti skaičių, bandykite dar kartą." << endl;
        }
    }

    cout << "Įveskite egzamino pažymį: "; 
    cin >> Pirmas.egz;
    cin.ignore();

    if (!Pirmas.paz.empty()) {
        Pirmas.galVid = double(sum) / double(Pirmas.paz.size()) * 0.4 + Pirmas.egz * 0.6;
        Pirmas.galMed = skaiciuotiMediana(Pirmas.paz) * 0.4 + Pirmas.egz * 0.6;
    } else {
        Pirmas.galVid = Pirmas.egz;
        Pirmas.galMed = Pirmas.egz;
    }

    return Pirmas; 
}

// mediana
double skaiciuotiMediana(vector<int> paz){
    int n = paz.size();
    if (n == 0) return 0;

    sort(paz.begin(), paz.end()); 

    if (n % 2 != 0) {
        return paz[n / 2];
    } else {
        return (paz[(n - 1) / 2] + paz[n / 2]) / 2.0;
    }
}
