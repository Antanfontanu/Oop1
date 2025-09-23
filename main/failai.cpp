#include "failai.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

using namespace std;

int atsitiktinisbalas(int min, int max) {
    return min + rand() % (max - min + 1);
}

void generuotiFailus() {
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    cout << "Pasirinkite studentų kiekį iš šių variantų:\n";
    for (size_t i = 0; i < dydziai.size(); i++) {
        cout << i + 1 << " - " << dydziai[i] << endl;
    }
    int pasirinkimas;
    cin >> pasirinkimas; cin.ignore();
    int dydis = dydziai[pasirinkimas - 1];
    int nd_kiekis;
    cout << "Kiek namų darbų balų sugeneruoti kiekvienam studentui? ";
    cin >> nd_kiekis; cin.ignore();

    string failoVardas = "studentai" + to_string(dydis) + ".txt";
    ofstream out(failoVardas);
    if (!out) { cout << "Nepavyko sukurti failo: " << failoVardas << endl; return; }

    out << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde";
    for (int j = 1; j <= nd_kiekis; j++) out << "ND" << j << " ";
    out << "Egzaminas" << endl;

    for (int i = 1; i <= dydis; i++) {
        out << setw(15) << left << "Vardas" + to_string(i)
            << setw(15) << left << "Pavarde" + to_string(i);
        for (int j = 0; j < nd_kiekis; j++) out << atsitiktinisbalas(1, 10) << " ";
        out << atsitiktinisbalas(1, 10) << endl;
    }

    out.close();
    cout << "Sukurtas failas: " << failoVardas 
         << " (" << dydis << " įrašų, ND=" << nd_kiekis << ")" << endl;
}

vector<Studentas> nuskaitytiIsFailo(const string& failoVardas) {
    vector<Studentas> grupe;
    ifstream failas(failoVardas);
    if (!failas) { cout << "Nepavyko atidaryti failo: " << failoVardas << endl; return grupe; }

    string eilute;
    getline(failas, eilute);

    bool pavVarOrder = false;
    if (eilute.find("Pavarde") != string::npos && eilute.find("Vardas") != string::npos) pavVarOrder = true;

    while(getline(failas, eilute)){
        if(eilute.empty()) continue;
        Studentas s;
        vector<string> tokens;
        string token;
        istringstream ss(eilute);
        while(ss >> token) tokens.push_back(token);

        if(tokens.size() < 3) continue;

        if(pavVarOrder) { s.pav = tokens[0]; s.var = tokens[1]; }
        else { s.var = tokens[0]; s.pav = tokens[1]; }

        s.balai.nd.clear();
        for(size_t i = 2; i < tokens.size(); ++i) {
            try { s.balai.nd.push_back(stoi(tokens[i])); }
            catch(...) { cout << "Įspėjimas: eilutėje su studentu „" << s.var << " " << s.pav << "“ pažymys \"" << tokens[i] << "\" buvo praleistas (ne skaičius)." << endl; }
        }

        if(!s.balai.nd.empty()){
            s.balai.egz = s.balai.nd.back();
            s.balai.nd.pop_back();
        } else s.balai.egz = 0;

        int sum = 0; for(int p : s.balai.nd) sum += p;
        s.galVid = s.balai.nd.empty() ? s.balai.egz : double(sum)/s.balai.nd.size()*0.4 + s.balai.egz*0.6;
        s.galMed = s.balai.nd.empty() ? s.balai.egz : skaiciuotiMediana(s.balai.nd)*0.4 + s.balai.egz*0.6;

        grupe.push_back(s);
    }

    cout << "Sėkmingai nuskaityta " << grupe.size() << " studentų iš failo." << endl;
    return grupe;
}

void irasytiStudentusIFaila(const vector<Studentas>& stud, Metodas metodas, const string& failoVardas){
    ofstream out(failoVardas);
    if(!out){ cout << "Nepavyko sukurti failo: " << failoVardas << endl; return; }

    for(const auto& s : stud){
        double galutinis = (metodas == Metodas::Vidurkis) ? s.galVid :
                            (metodas == Metodas::Mediana) ? s.galMed :
                            (s.galVid + s.galMed)/2.0;
        out << s.var << " " << s.pav << " " << fixed << setprecision(2) << galutinis << endl;
    }
    out.close();
}
