# Oop1
v0.1-release

## Trumpas aprašymas
Programa leidžia:
Įvesti studentų duomenis ranka, generuoti automatiškai arba nuskaityti juos iš failo.
Apskaičiuoti galutinius balus pagal namų darbų vidurkį arba medianą.
Spausdinti rezultatų lentelę.
Taip pat pridėti failus testavimui.
#### Pastabos:
Programa patikrina klaidas vartotojo įvedime ir informuoja, jei įvestas neteisingas skaičius arba failas neegzistuoja.<br>

Galutiniai balai gali būti skaičiuojami pagal vidurkį, medianą arba abu metodus.
## Naudojimas
Programa turi meniu, kuriuo lengva naudotis.
Meniu aprašymas: <br>
1 - Įvesti studentų duomenis <br>
2 - Nuskaityti studentus iš failo <br>
3 - Parodyti rezultatų lentelę <br>
4 - Testavimas pagal failą <br>
5 - Baigti programą <br>



### Galimi failų formatai
Vardas Pavardė 5 6 7 8 9 10 <br>
Pavardė Vardas 6 7 5 8 9 10 <br>
#### Pastabos:
Paskutinis skaičius laikomas egzamino balu.
Netinkami simboliai faile bus praleisti su įspėjimu.


## Efektyvumo tyrimai
### Tema
Patikrinimas, kiek programa užtruks laiko nuskaityti ir surūšiuoti duomenis iš įkeltų testavimo failų

### Testavimo failai
studentai10000.txt - 10 000 studentų<br>
studentai100000.txt - 100 000 studentų<br>
studentai1000000.txt - 1 000 000 studentų<br>


### Laiko matavimo metodas
Buvo naudota naudota C++ biblioteka chrono
#### Kodas:
```cpp
auto start = high_resolution_clock::now();
auto end = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(end - start).count();
```
## Rezultatai

10 000 studentų failas nuskaitytas ir surikiuotas	~159 ms greičiu.<br>
100 000	- ~1284 ms greičiu.<br>
1 000 000 -	~10 052 ms greičiu.<br>

### Išvados
Laikas proporcingai didėja turimam duomenų skaičiui.
Turint didelius duomenų failus galima bandyti optimizuoti kodą.
