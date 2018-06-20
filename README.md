# GRK PROJEKT
Dokumentacja projektu z Grafiki Komputerowej
# Autorzy
 - Adam Minge (426196),
 - Wiktor Morawski (430692)

Struktura projektu
```
projekt
├── cmake    : zawiera moduły ładujące zewnętrzne biblioteki i macros.cmake
├── extlibs  : zawiera wszystkie zewnętrzne biblioteki(freeglut, glew, glm) 
├── include  : zawiera wszystkie pliki nagłówkowe 
├── models   : zawiera wszystkie pliki obiektów (.obj)
├── shaders  : zawiera wszystkie pliki shaderów (.frag & .vert)
├── src      : zawiera wszystkie pliki źródłowe
└── textures : zawiera wszystkie pliki tekstur
```
# Opis sceny
- zawiera 3 gatunki ryb (każda z nich to obiekt .obj)
- na rekinie nałożona jest tekstura generowana proceduralnie
- reszta ryb posiada tekstury z pliku PNG
- dno jest obiektem (.obj) z nałożoną teksturą z pliku
- posiada jedno źródło światła
- sterujemy łodzią podwodną
- w nasz świat możemy wejść za pomocą wolnej kamery
- zostało wygenerowane kilkaset ryb w losowych miejscach, każda z nich porusza się po losowej ścieżce
- z zaawansowanych efektów użyliśmy `Szum Perlina`
# Sterowanie
| Klawisz | Akcja |
| ------ | ------ |
| W | ruch do przodu |
| S | ruch do tyłu |
| A | ruch w lewo |
| D | ruch w prawo |
| F | wolna kamera |
| Q | spowolnienie czasu |
| E | przyśpieszenie czasu |
# Wykorzystane biblioteki
- freeglut
- glew
- glm
