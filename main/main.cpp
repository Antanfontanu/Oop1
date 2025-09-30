#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include "studentas.h"
#include "failai.h"
#include "meniu.h"
#include <filesystem>


   


using namespace std;
using namespace std::chrono;



int main(){
    srand((unsigned)system_clock::now().time_since_epoch().count());
    
    
    vector<Studentas> Grupe;
    int pasirinkimas;

    while (true){
        cout<<"------- Meniu -------"<<endl;
        cout<<"1 - įvesti studentus"<<endl;
        cout << "2 - Nuskaityti studentus iš failo" << endl;
        cout<<"3 - Parodyti rezultatų lentelę"<<endl;
        cout<<"4 - Testavimas pagal failą"<<endl;
        cout << "5 - Generuoti atsitiktinius studentų failus" << endl;
        cout << "6 - Padalinti studentus į grupes (vargšiukai/kietiakai)" << endl;
        cout<<"7 - Baigti programą"<<endl;

        pasirinkimas = ivestiSk("Pasirinkimas: ", 1, 7);

        if (pasirinkimas==1){
            int m = ivestiSk("Kiek studentų grupėje: ", 1);
            for (int z = 0; z < m; z++) Grupe.push_back(Stud_iv());

            sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b){
                return a.pav < b.pav;
            });
        }
        else if (pasirinkimas == 2) {
        
            cout << "Pasirinkite, iš kurio failo nuskaityti studentus:" << endl;
            cout << "1 - kursiokai.txt" << endl;
            cout << "2 - studentas1000.txt" << endl;
            cout << "3 - studentas10000.txt" << endl;
            cout << "4 - studentas100000.txt" << endl;
            cout << "5 - studentas1000000.txt" << endl;
            cout << "6 - studentas10000000.txt" << endl;

            int failoPasirinkimas = ivestiSk("Pasirinkimas: ", 1, 6);
            string failoKelias;

            switch (failoPasirinkimas) {
                case 1: failoKelias = "kursiokai.txt"; break;
                case 2: failoKelias = "studentas1000.txt"; break;
                case 3: failoKelias = "studentas10000.txt"; break;
                case 4: failoKelias = "studentas100000.txt"; break;
                case 5: failoKelias = "studentas1000000.txt"; break;
                case 6: failoKelias = "studentas10000000.txt"; break;
            }
            
            if (!std::filesystem::exists(failoKelias)) {
                cout << "Failo \"" << failoKelias << "\" nėra! "
                    << "Pirmiausia sugeneruokite jį (naudokite meniu nr 5)." << endl;
            }else {
                auto start_read = high_resolution_clock::now();
                vector<Studentas> failoGrupe = nuskaitytiIsFailo(failoKelias);
                auto end_read = high_resolution_clock::now();

            cout << "Failo nuskaitymas užtruko: "
                 << duration_cast<milliseconds>(end_read - start_read).count()
                 << " ms" << endl;
            if (!failoGrupe.empty()) {
                Grupe.insert(Grupe.end(), failoGrupe.begin(), failoGrupe.end());
                cout << "Nuskaityta " << failoGrupe.size() << " studentų iš failo." << endl;
                sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b){
                    return a.pav < b.pav;
                    });
            }
        }
    }
        else if (pasirinkimas==3){
            if (Grupe.empty()){ cout<< " Turi būti įvestas bent vienas studentas "<< endl; continue; }

            cout << "Pasirinkite galutinio balo skaičiavimo metodą:" << endl;
            cout << "1 - Vidurkis" << endl;
            cout << "2 -  Mediana" << endl;
            cout << "3 - Abu" << endl;
            int metodas = ivestiSk("Pasirinkimas: ", 1,3);
            spausdintiLentele(Grupe, Metodas(metodas));
        }
        else if (pasirinkimas == 4) {
            cout << "Pasirinkite failą testavimui:\n";
            cout << "1 - studentai10000.txt\n";
            cout << "2 - studentai100000.txt\n";
            cout << "3 - studentai1000000.txt\n";
            int failoPasirinkimas = ivestiSk("Pasirinkimas: ", 1, 3);

            string failoKelias;
            if (failoPasirinkimas == 1) failoKelias = "studentai10000.txt";
            else if (failoPasirinkimas == 2) failoKelias = "studentai100000.txt";
            else failoKelias = "studentai1000000.txt";

            auto start = high_resolution_clock::now();
            vector<Studentas> testGrupe = nuskaitytiIsFailo(failoKelias);
            if (testGrupe.empty()) { cout << "Failas tuščias arba jo nepavyko atidaryti." << endl; continue; }
            sort(testGrupe.begin(), testGrupe.end(), [](const Studentas &a, const Studentas &b){ return a.pav < b.pav; });
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start).count();

            ofstream fout("testavimo_rezultatai.txt");
            if (!fout) { cout << "Nepavyko sukurti rezultato failo!" << endl; continue; }
            fout << "Nuskaitymo ir rikiavimo laikas: " << duration << " ms" << endl;
            fout << "Testavimo rezultatai:\n";
            
            
            spausdintiLentele(testGrupe, Metodas::Abu, fout);

            fout.close();
            cout << "Rezultatai įrašyti į testavimo_rezultatai.txt" << endl;
        }
        else if (pasirinkimas == 5) { generuotiFailus(); }
        else if (pasirinkimas == 6){
            
            if (Grupe.empty()) { cout << "Pirmiau įveskite studentus." << endl; continue; }

            cout << "Pasirinkite galutinio balo skaičiavimo metodą:" << endl;
            cout << "1 - Vidurkis" << endl;
            cout << "2 - Mediana" << endl;
            cout << "3 - Abu" << endl;
            int metodas = ivestiSk("Pasirinkimas: ", 1, 3);

            padalintiStudentus(Grupe, Metodas(metodas));
        }
        else if(pasirinkimas==7){ cout<<"Programa baigta"<<endl; break; }
    }
    return 0;
}
