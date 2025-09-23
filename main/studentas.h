#pragma once
#include <vector>
#include <string>

// Struktūros

struct Balas{
    std::vector<int> nd;
    int egz;
};

struct Studentas{
    std::string var;
    std::string pav;
    Balas balai;
    double galVid;
    double galMed;
};

struct Grupe{
    std::vector<Studentas> studentai;
    std::string pavadinimas;
};

enum class Metodas{
    Vidurkis = 1,
    Mediana = 2,
    Abu = 3
};


Studentas Stud_iv();
double skaiciuotiMediana(std::vector<int> paz);
