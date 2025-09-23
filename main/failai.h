#pragma once
#include "studentas.h"
#include <vector>
#include <string>

std::vector<Studentas> nuskaitytiIsFailo(const std::string& failoVardas);
void irasytiStudentusIFaila(const std::vector<Studentas>& stud, Metodas metodas, const std::string& failoVardas);
void generuotiFailus();
int atsitiktinisbalas(int min, int max);
