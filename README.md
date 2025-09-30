# OOP
v.02 - release
## Atnaujinimai
v0.1 failai buvo suskirstyti į keturis .cpp ir keturis .h failus. <br> 
Taip pat pridėtas atsitiktinis failų generavimas. <br>
bei studentų skirstymas grupėmis pagal jų rezultatus. <br>

## Atnaujintas meniu
1 - įvesti studentus <br>
2 - Nuskaityti studentus iš failo <br>
3 - Parodyti rezultatų lentelę <br>
4 - Testavimas pagal failą <br>
5 - Generuoti atsitiktinius studentų failus <br>
6 - Padalinti studentus į grupes (vargšiukai/kietiakai) <br>
7 - Baigti programą <br>

## Programos spartos analizė

### Laiko matavimo metodas
Buvo naudota naudota C++ biblioteka chrono
### Testuoti failai:
studentas1000.txt - 1000 studentų <br>
studentas10000.txt - 10000 studentų <br>
studentas100000.txt - 100000 studentų <br>
studentas1000000.txt - 1000000 studentų <br> 
studentas10000000.txt - 10000000 studentų <br>
#### Kodas:
```cpp
auto start = high_resolution_clock::now();
auto end = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(end - start).count();
```

### Testevimo kategorijos
1 Failų kūrimas <br>
2 Duomenų nuskaitymas iš failų <br>
3 Studentų rūšiavimas į dvi grupes <br>
4 Surūšiuotų studentų išvedimas į du naujus failus <br>

### Rezultatų lentelė

| Failas                 | Failo kūrimas | Duomenų nuskaitymas | Studentų rūšiavimas | Išvedimas į failus |
|:------------------------|:--------------|:--------------------|:--------------------|:-------------------|
| studentas1000.txt       | 5.4 s         | 0.008 s             | 0 s                 | 0.049 s            |
| studentas10000.txt      | 4.9 s         | 0.057 s             | 0.003 s             | 0.133 s            |
| studentas100000.txt     | 7.1 s         | 0.567 s             | 0.049 s             | 1.615 s            |
| studentas1000000.txt    | 16.7 s        | 4.21 s              | 0.504 s             | 10.7 s             |
| studentas10000000.txt   | 111.6 s       | 39.3 s              | 3.8 s               | 121.1 s            |
