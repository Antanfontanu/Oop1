#include "studentas.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "meniu.h"
#include "failai.h"


using namespace std;

Studentas Stud_iv() {
    int sum = 0;
    Studentas Pirmas;
    
    cout << "Įveskite studento duomenis" << endl;
    cout << "Vardas: "; cin >> Pirmas.var; 
    cout << "Pavardė: "; cin >> Pirmas.pav; 
    cin.ignore(); 

    int ats = ivestiSk("Ar norite sugeneruoti atsitiktinius balus už namų darbus ir egzaminą? (1 - taip, 0 - ne): ", 0, 1);

    if (ats == 1) {
        int balu_sk = ivestiSk("Kiek balų atsitiktinai sugeneruoti: ", 1);

        for (int i=0; i< balu_sk; i++) {
            int paz = atsitiktinisbalas(1,10);
            Pirmas.balai.nd.push_back(paz);
            sum+=paz;
        }
        Pirmas.balai.egz = atsitiktinisbalas(1,10);
        cout<< "Sugeneruoti"<< balu_sk << " namų darbų ir egzamino balai studentui"
        << Pirmas.var << "  "<< Pirmas.pav<< "."<< endl;
    } else {

        cout << "Įveskite pažymius ( Nuo 1-10. Paspauskite du kartus ENTER, jei norite baigti vesti pažymius):" << endl;
        int tuscios_eil = 0;

        while (true) {
            string eil;
            cout << "Pažymys: ";
            getline(cin, eil);

            if (eil.empty()) {
                tuscios_eil++;
                if (tuscios_eil == 2) break; 
                else continue;
            } else {
                tuscios_eil = 0;
            }

            try {
                int laik_paz = std::stoi(eil);
                if (laik_paz <1 || laik_paz>10){
                    cout << "Pažymys turi būti nuo 1 iki 10"<< endl;
                    continue;
                }
                Pirmas.balai.nd.push_back(laik_paz);
                sum += laik_paz;
            } catch (...) {
                cout << "Reikia įvesti skaičių, bandykite dar kartą." << endl;
            }
        }

        Pirmas.balai.egz = ivestiSk("Įveskite egzamino pažymį:  ", 1, 10);
    }

    if (!Pirmas.balai.nd.empty()) {
        Pirmas.galVid = double(sum) / double(Pirmas.balai.nd.size()) * 0.4 + Pirmas.balai.egz * 0.6;
        Pirmas.galMed = skaiciuotiMediana(Pirmas.balai.nd) * 0.4 + Pirmas.balai.egz * 0.6;
    } else {
        cout << "Įspėjimas: studentui " << Pirmas.var << " " << Pirmas.pav 
         << " nėra įvestų pažymių. Galutinis balas lygus egzamino balui." << endl;
        Pirmas.galVid = Pirmas.balai.egz;
        Pirmas.galMed = Pirmas.balai.egz;
    }

    return Pirmas; 
}

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
