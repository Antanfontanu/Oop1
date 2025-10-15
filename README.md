# OOP
v.03 - release
## Programos aprašymas <br/>
Programa  leidžia vartotojui suvesti arba nuskaityti duomenis apie studentą(vardą, pavardę, namų darbų rezultatus, egzamino rezultatus).<br>
Apskaičiuoja studentų galutinius rezultatus paga formulę:<br>
*Galutinis balas = 0.4 x namų darbų rezultatai + 0.6 x egzamino įvertinimas.*  <br>
Duomenų įvedimas ranka - leidžiama vartotojui pasirinkti, kiek namų darbų pažymių jis nori įvesti/sigeneruoti.
Namų darbų rezultatai - vartotojui leidžiama pasirinkti ar namų darbų rezultatus skaičiuoti su mediana ar gauti jų vidurkį.<br/>
<br/>
## Atnaujinimai v0.2
v0.1 failai buvo suskirstyti į keturis .cpp ir keturis .h failus. <br> 
Taip pat pridėtas atsitiktinis failų generavimas. <br>
bei studentų skirstymas grupėmis pagal jų rezultatus. <br>
## Atnaujinimai v0.3
Pridėtas pasirinkimas su kuriais vektoriais norime dirbti <br> 
Pridėta daugiau .h failų <br>
Pridėta objekto saugojimo vieta. <br>
Atlikti laiko testavimai tarp vector ir list konteinerių. <br>

**Failų aprašymas:**
* main.cpp yra pagrindinis failas.
* studentas.cpp faile aprašytas studento įvedimas.
* failai.cpp faile surašyti metodai naudojami failų generavimui, nuskaitymui, įrašymui.
* meniu.cpp faile aprašytos meniu naudojamos funkcijos.
* MyLib.h faile aprašytos visos pogramoje naudojamos bibliotekos.
* studentas.h faile aprašyta Stud struktūra, kuri aprašo studentą ir metodų deklaracijos.
* Timer.h faile aprašytas laiko skaičiavimo klasė.
* meniu.h deklaruotos studentų dalijimo, rikiavimo funkcijos
* failai.h deklaruotos funkcijos failai.cpp
<a/>

## Programos spartos analizė

Laiko testavimas buvo atliktas su vektoriaus ir sąrašo konteineriais, naudoti tie patys sugeneruoti failai su 5 namų darbų pažymiais iš v0.2 versijos, laikui matuoti imtas 5 bandymų vidurkis

### Testavimo sistemos parametrai
CPU: AMD Ryzen 5 7535U with Radeon Graphics 2.90 GHz <br>
RAM: 16GB (13.7GB naudojami) <br>
HDD: SSD 512GB (SKHynix HFS512GEJ4X112N) <br>
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

### Testavimo kategorijos
1 Failų kūrimas <br>
2 Duomenų nuskaitymas iš failų <br>
3 Studentų rūšiavimas į dvi grupes <br>
4 Surūšiuotų studentų išvedimas į vargšiukai.txt <br>
5 Surūšiuotų studentų išvedimas į kietiakai.txt <br>
### Rezultatų lentelė
### Testavimas su vektoriaus konteineriu

| Failas                 | Failo kūrimas | Duomenų nuskaitymas | Studentų rūšiavimas | Išvedimas į kietiakai |Išvedimas į vargšiukai|
|:------------------------|:--------------|:--------------------|:--------------------|:-------------------|:-------------------|
| studentas1000.txt       | 5.4 s         | 0.008 s             | 0 s                 | 0.004 s            | 0.01 s             |
| studentas10000.txt      | 4.9 s         | 0.048 s             | 0.003 s             | 0.048 s            | 0.044 s            |
| studentas100000.txt     | 7.1 s         | 0.445 s             | 0.049 s             | 0.388 s            | 0.282 s            |
| studentas1000000.txt    | 16.7 s        | 3.21 s              | 0.304 s             | 4.51 s             | 3.12 s             |
| studentas10000000.txt   | 111.6 s       | 34.3 s              | 3.1 s               | 56.12 s            | 64.33 s            |

### Testavimas su sąrašo konteineriu

| Failas                 | Failo kūrimas | Duomenų nuskaitymas | Studentų rūšiavimas | Išvedimas į kietiakai |Išvedimas į vargšiukai|
|:------------------------|:--------------|:--------------------|:--------------------|:-------------------|:-------------------|
| studentas1000.txt       | 5.4s          | 0.005 s             | 0.00064s            | 0.011 s            | 0.007 s            |
| studentas10000.txt      | 4.9 s         | 0.076 s             | 0.003 s             | 0.053 s            | 0.042 s            |
| studentas100000.txt     | 7.1 s         | 0.383 s             | 0.036 s             | 0.378 s            | 0.431 s            |
| studentas1000000.txt    | 16.7 s        | 3.35 s              | 0.319 s             | 4.69 s             | 3.369 s            |
| studentas10000000.txt   | 111.6 s       | 33.3 s              | 3.5 s               | 52.13 s            | 38.62 s            |


## Rezultatų diagramos

### studentas1000.txt
![studentas1000](diagramos/studentas1000.png)

### studentas10000.txt
![studentas10000](diagramos/studentas10000.png)

### studentas100000.txt
![studentas100000](diagramos/studentas100000.png)

### studentas1000000.txt
![studentas1000000](diagramos/studentas1000000.png)

### studentas10000000.txt
![studentas10000000](diagramos/studentas10000000.png)

## Spartos analizės išvados:
Buvo testuojama programa naudojant dvi skirtingas struktūras: std::vector ir std::list. Programos veikimo laikai buvo lyginami. </br>
**Galima padaryti išvadas:**
* Lyginant vector ir list labai didelių skirtumų nėra
* Atsižvelgiant į 10mln failą, sąrašas yra labiau tinkamas naudoti su dideliais duomenų kiekiais, priešingai negu vector, kuris geriau veikia mažesnio duomenų kiekio failuose.
* Iš gautų rezultatų matome, kad su skirtingais duomenų kiekiais programos vykdymo laikai kito, todėl sudėtinga padaryti vienareikšmę išvadą, kuris konteinerio tipas: vektorius ar sąrašas, yra tinkamesnis failų nuskaitymui, išvedimui ar rūšiavimui.
* Reiktų bandyti atlikti tyrimą su daugiau bandymų, kad gautume tikslesnius rezultatus.
