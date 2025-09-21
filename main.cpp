#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

#include <fstream>
#include <sstream>
#include <chrono>
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
using std::sort;
using std::stoi;
using std::getline;
using std::rand;
using std::srand;

using std::ifstream;
using std::istringstream;
using namespace std::chrono;
using std::ofstream;
using namespace std::string_literals;
using std::to_string;

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
vector<Studentas> nuskaitytiIsFailo(const string& failoVardas);
void spausdintiLentele(const vector<Studentas>& Grupe, int metodas, std::ostream& os = std::cout);
void generuotiFailus();
int atsitiktinisbalas(int min, int max);
int ivestiSk(const string &tekstas, int min_val=-1000000, int max_val=1000000);


void generuotiFailus() {
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    cout << "Pasirinkite studentų kiekį iš šių variantų:\n";
    for (size_t i = 0; i < dydziai.size(); i++) {
        cout << i + 1 << " - " << dydziai[i] << endl;
    }
    int pasirinkimas = ivestiSk("Jūsų pasirinkimas: ", 1, (int)dydziai.size());
    int dydis = dydziai[pasirinkimas - 1];
    int nd_kiekis = ivestiSk("Kiek namų darbų balų sugeneruoti kiekvienam studentui? ", 1, 20);

    string failoVardas = string("studentai") + std::to_string(dydis) + ".txt";
    ofstream out(failoVardas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failoVardas << endl;
        return;
    }

        out << setw(15) << left << "Vardas"
            << setw(15) << left << "Pavarde";
        for (int j = 1; j <= nd_kiekis; j++) out << "ND" << j << " ";
        out << "Egzaminas" << endl;

        for (int i = 1; i <= dydis; i++) {
            out << setw(15) << left << "Vardas" + to_string(i)
                << setw(15) << left << "Pavarde" + to_string(i);

            for (int j = 0; j < nd_kiekis; j++) {
                out << atsitiktinisbalas(1, 10) << " ";
            }
            out << atsitiktinisbalas(1, 10) << endl;
        }

        out.close();
        cout << "Sukurtas failas: " << failoVardas 
             << " (" << dydis << " įrašų, ND=" << nd_kiekis << ")" << endl;
    }



//generuojami atsitiktiniai balus
int atsitiktinisbalas(int min, int max) {
    return min + rand() % (max - min + 1);
}
//skaičiaus įvedimas teisingai
int ivestiSk(const string &tekstas, int min_val, int max_val){
    int sk;
    while(true){
        cout << tekstas;
        string eil;
        getline(cin, eil);
        try{
            sk = std::stoi(eil);
            if(sk>=min_val && sk<=max_val) return sk;
            else cout << "Įveskite skaičių nuo " << min_val << " iki " << max_val << "." << endl;
        }catch(...){
            cout << "Įveskite tik skaičių." << endl;
        }
    }
}

int main(){
    srand((unsigned)system_clock::now().time_since_epoch().count());
    
    vector<Studentas> Grupe;
    int pasirinkimas;

    // veiksmų pasirinkimo meniu

    while (true){
        cout<<"------- Meniu -------"<<endl;
        cout<<"1 - įvesti studentus"<<endl;
        cout << "2 - Nuskaityti studentus iš failo" << endl;
        cout<<"3 - Parodyti rezultatų lentelę"<<endl;
        cout<<"4 - Testavimas pagal failą"<<endl;
        cout << "5 - Generuoti atsitiktinius studentų failus" << endl;
        cout<<"6 - Baigti programą"<<endl;
        pasirinkimas = ivestiSk("Pasirinkimas: ", 1, 6);
        if (pasirinkimas==1){
            int m = ivestiSk("Kiek studentų grupėje: ", 1);
            for (int z = 0; z < m; z++) 
                Grupe.push_back(Stud_iv());

            sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b){
                return a.pav < b.pav;
            });
        }
        else if (pasirinkimas == 2) {
            vector<Studentas>
            failoGrupe = nuskaitytiIsFailo("..\\kursiokai.txt");
            if (!failoGrupe.empty()) {
                Grupe.insert(Grupe.end(), failoGrupe.begin(), failoGrupe.end());
                cout << "Nuskaityta " << failoGrupe.size() << " studentų iš failo." << endl;
                sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b){
                    return a.pav < b.pav;
                });
            }
        }
        else if (pasirinkimas==3){
            if (Grupe.empty()){
                cout<< " Turi būti įvestas bent vienas studentas "<< endl;
                continue;
            }

            cout << "Pasirinkite galutinio balo skaičiavimo metodą:" << endl;
            cout << "1 - Vidurkis" << endl;
            cout << "2 -  Mediana" << endl;
            cout << "3 - Abu" << endl;
            int metodas = ivestiSk("Pasirinkimas: ", 1,3);
            spausdintiLentele(Grupe, metodas);
    

            
        }


        else if (pasirinkimas == 4) {
            cout << "Pasirinkite failą testavimui:\n";
            cout << "1 - studentai10000.txt\n";
            cout << "2 - studentai100000.txt\n";
            cout << "3 - studentai1000000.txt\n";
            int failoPasirinkimas = ivestiSk("Pasirinkimas: ", 1, 3);

            string failoKelias;
            if (failoPasirinkimas == 1) failoKelias = "..\\studentai10000.txt";
            else if (failoPasirinkimas == 2) failoKelias = "..\\studentai100000.txt";
            else failoKelias = "..\\studentai1000000.txt";

            auto start = high_resolution_clock::now();
            vector<Studentas> testGrupe = nuskaitytiIsFailo(failoKelias);
            if (testGrupe.empty()) {
                cout << "Failas tuščias arba jo nepavyko atidaryti." << endl;
                continue;
            }
            sort(testGrupe.begin(), testGrupe.end(), [](const Studentas &a, const Studentas &b){
                return a.pav < b.pav;
            });
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start).count();
            ofstream fout("testavimo_rezultatai.txt");
            if (!fout) {
                cout << "Nepavyko sukurti rezultato failo!" << endl;
                continue;
            }
            fout << "Testavimo rezultatai:\n";
            spausdintiLentele(testGrupe, 3, fout);
            fout << "Nuskaitymo ir rikiavimo laikas: " << duration << " ms" << endl;
            fout.close();
            cout << "Rezultatai įrašyti į testavimo_rezultatai.txt" << endl;

    
            


        }
        else if (pasirinkimas == 5) {
            generuotiFailus();
        }

            
        else if(pasirinkimas==6){
            cout<<"Programa baigta"<<endl;
            break;
        }
    }
    return 0;
}


    

    
    

//Studento įvedimas
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
            Pirmas.paz.push_back(paz);
            sum+=paz;
        }
        Pirmas.egz = atsitiktinisbalas(1,10);
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
            Pirmas.paz.push_back(laik_paz);
            sum += laik_paz;
        } catch (...) {
            cout << "Reikia įvesti skaičių, bandykite dar kartą." << endl;
        }
    }

    Pirmas.egz = ivestiSk("Įveskite egzamino pažymį:  ", 1, 10);
}
    if (!Pirmas.paz.empty()) {
        Pirmas.galVid = double(sum) / double(Pirmas.paz.size()) * 0.4 + Pirmas.egz * 0.6;
        Pirmas.galMed = skaiciuotiMediana(Pirmas.paz) * 0.4 + Pirmas.egz * 0.6;
    } else {
        cout << "Įspėjimas: studentui " << Pirmas.var << " " << Pirmas.pav 
         << " nėra įvestų pažymių. Galutinis balas lygus egzamino balui." << endl;
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
// Lentelės spausdinimas
void spausdintiLentele(const vector<Studentas>& Grupe, int metodas,std::ostream& os){
    cout << setw(10) << left << "Vardas" << "|"
         << setw(15) << right << "Pavardė" << "|";
    if (metodas==1) cout << "Galutinis (Vid.)" << endl;
    else if (metodas==2) cout << "Galutinis (Med.)" << endl;
    else cout << "Galutinis (Vid.)|Galutinis (Med.)" << endl;
    cout << "------------------------------------------------" << endl;

    for (auto& s : Grupe){
        os << setw(10) << left << s.var
           << "|" << setw(15) << right << s.pav << "|";
        if (metodas==1) os << setw(10) << fixed << setprecision(2) << s.galVid << endl;
        else if (metodas==2) os << setw(10) << fixed << setprecision(2) << s.galMed << endl;
        else os << setw(10) << fixed << setprecision(2) << s.galVid
                << "|" << setw(10) << fixed << setprecision(2) << s.galMed << endl;
    }
}

//Failo nuskaitymas
vector<Studentas> nuskaitytiIsFailo(const string& failoVardas) {
    vector<Studentas> grupe;
    std::ifstream failas(failoVardas);
    
    if (!failas) {
        cout << "Nepavyko atidaryti failo: " << failoVardas << endl;
        return grupe;
    }

    string eilute;


    std::getline(failas, eilute); 



    bool pavVarOrder = false;
    if (eilute.find("Pavarde") != string::npos && eilute.find("Vardas") != string::npos) {
        pavVarOrder = true;
    }
    //

    while (std::getline(failas, eilute)) {
        if (eilute.empty()) continue;
        Studentas s;
        vector<string> tokens;
        std::string token;
        std::istringstream ss(eilute);
        while (ss >> token) tokens.push_back(token);

        if (tokens.size() < 3) continue;

        if (pavVarOrder) {
            s.pav = tokens[0];
            s.var = tokens[1];
        } else {
            s.var = tokens[0];
            s.pav = tokens[1];
        }

        s.paz.clear();
        for (size_t i = 2; i < tokens.size(); ++i) {
            try {
                int bal = std::stoi(tokens[i]);
                s.paz.push_back(bal);
            } catch (...) {
                cout << "Įspėjimas: eilutėje su studentu „" << s.var << " " << s.pav 
                    << "“ pažymys \"" << tokens[i] << "\" buvo praleistas (ne skaičius)." << endl;
                continue;
            }
        }

        if (!s.paz.empty()) {
            s.egz = s.paz.back();
            s.paz.pop_back();
        } else {
            s.egz = 0;
        }

        int sum = 0;
        for (int p : s.paz) sum += p;
        s.galVid = s.paz.empty() ? s.egz : double(sum)/s.paz.size()*0.4 + s.egz*0.6;
        s.galMed = s.paz.empty() ? s.egz : skaiciuotiMediana(s.paz)*0.4 + s.egz*0.6;

        grupe.push_back(s);
    }

    cout << "Sėkmingai nuskaityta " << grupe.size() << " studentų iš failo." << endl;
    return grupe;
}
