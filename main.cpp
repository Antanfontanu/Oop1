#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime> 

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
int atsitiktinisbalas(int min, int max) {
    return min + rand() % (max - min + 1);
}
int ivestiSk(const string &tekstas, int min_val=-1000000, int max_val=1000000){
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
    srand(time(0));
    
    vector<Studentas> Grupe;
    int pasirinkimas;
    // veiksmų pasirinkimo meniu

    while (true){
        cout<<"------- Meniu -------"<<endl;
        cout<<"1 - įvesti studentus"<<endl;
        cout<<"2 - Parodyti rezultatų lentelę"<<endl;
        cout<<"3 - Baigti programą"<<endl;
        pasirinkimas = ivestiSk("Pasirinkimas: ", 1, 3);
        if (pasirinkimas==1){
            int m = ivestiSk("Kiek studentų grupėje: ", 1);
            for (int z = 0; z < m; z++) 
                Grupe.push_back(Stud_iv());
        }
        else if (pasirinkimas==2){
            if (Grupe.empty()){
                cout<< " Turi būti įvestas bent vienas studentas "<< endl;
                continue;
            }

            cout << "Pasirinkite galutinio balo skaičiavimo metodą:" << endl;
            cout << "1 - Vidurkis" << endl;
            cout << "2 -  Mediana" << endl;
            cout << "3 - Abu" << endl;
            int metodas = ivestiSk("Pasirinkimas: ", 1,3);
            
            sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b){
                return a.pav < b.pav;
            });

            // viršus rezultatų lentelės
            cout << "Studento informacija:" << endl;
            cout << setw(10) << left << "Vardas" << "|"
                << setw(15) << right << "Pavardė" << "|";
            // cout << "Pažymiai|Egz.|";
            if(metodas == 1) cout << "Galutinis (Vid.)" << endl;
            else if(metodas == 2) cout << "Galutinis (Med.)" << endl;
            else cout << "Galutinis (Vid.)|Galutinis (Med.)" << endl;
            cout<<"-------------------------------------"<<endl;
            // lentelės rezultatai
            for (auto& Past : Grupe){
                cout << setw(10) << left << Past.var << "|"
                    << setw(15) << right << Past.pav << "|";
            // for(auto& a : Past.paz) cout << setw(3) << a << "|";
            // cout << setw(5) << Past.egz << "|";
            //galutinio pažymio pasirinkimas
            if(metodas == 1) cout << setw(10) << fixed << setprecision(2) << Past.galVid << endl;
            else if (metodas  == 2) cout << setw(10) << fixed << setprecision(2) << Past.galMed << endl;
            else cout << setw(10) << fixed << setprecision(2) << Past.galVid
                    << "|" << setw(10) << fixed << setprecision(2) << Past.galMed << endl;
    }
}
        else if(pasirinkimas==3){
            cout<<"Programa baigta"<<endl;
            break;
        }
    }
}


    

    
    

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
        << Pirmas.var << " "<< Pirmas.pav<< "."<< endl;
 } else {


    cout << "Įveskite pažymius ( Nuo 1-10. Paspauskite du kartus ENTER, jei norite baigti):" << endl;
   
    int tuscios_eil = 0;

    while (true) {
        string eil;
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

    Pirmas.egz = ivestiSk("Įveskite egzamino pažymį: ", 1, 10);
}
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