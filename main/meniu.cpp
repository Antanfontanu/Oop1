#include "meniu.h"
#include "failai.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int ivestiSk(const string &tekstas, int min_val, int max_val){
    int sk;
    while(true){
        cout << tekstas;
        string eil;
        getline(cin, eil);
        try{
            sk = stoi(eil);
            if(sk>=min_val && sk<=max_val) return sk;
            else cout << "Įveskite skaičių nuo " << min_val << " iki " << max_val << "." << endl;
        }catch(...){
            cout << "Įveskite tik skaičių." << endl;
        }
    }
}

void spausdintiLentele(const vector<Studentas>& Grupe, Metodas metodas,std::ostream& os){
    cout << setw(10) << left << "Vardas" << "|"
         << setw(15) << right << "Pavardė" << "|";
    if (metodas==Metodas::Vidurkis) cout << "Galutinis (Vid.)" << endl;
    else if (metodas==Metodas::Mediana) cout << "Galutinis (Med.)" << endl;
    else cout << "Galutinis (Vid.)|Galutinis (Med.)" << endl;
    cout << "------------------------------------------------" << endl;

    for (auto& s : Grupe){
        os << setw(10) << left << s.var
           << "|" << setw(15) << right << s.pav << "|";
        if (metodas==Metodas::Vidurkis) os << setw(10) << fixed << setprecision(2) << s.galVid << endl;
        else if (metodas==Metodas::Mediana) os << setw(10) << fixed << setprecision(2) << s.galMed << endl;
        else os << setw(10) << fixed << setprecision(2) << s.galVid
                << "|" << setw(10) << fixed << setprecision(2) << s.galMed << endl;
    }
}

void padalintiStudentus(const vector<Studentas>& Grupe, Metodas metodas){
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakai;

    for (const auto& s : Grupe){
        double galutinis;
        if(metodas==Metodas::Vidurkis) galutinis = s.galVid;
        else if(metodas==Metodas::Mediana) galutinis = s.galMed;
        else galutinis = (s.galVid + s.galMed)/2.0;

        if(galutinis<5.0) vargsiukai.push_back(s);
        else kietiakai.push_back(s);
    }

    irasytiStudentusIFaila(vargsiukai, metodas, "vargsiukai.txt");
    irasytiStudentusIFaila(kietiakai, metodas, "kietiakai.txt");
}
