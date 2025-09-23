#pragma once
#include "studentas.h"
#include <vector>
#include <iostream>

int ivestiSk(const std::string &tekstas, int min_val=-1000000, int max_val=1000000);
void spausdintiLentele(const std::vector<Studentas>& Grupe, Metodas metodas, std::ostream& os = std::cout);
void padalintiStudentus(const std::vector<Studentas>& Grupe, Metodas metodas);
