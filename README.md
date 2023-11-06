# STE - Simple Text Editor
##### Kacper Wiszniewski - II rok ISSP - Projekt C++ 2024 - semestr zimowy

Prosty edytor tekstu w dostępny przejrzystej i eleganckiej oprawie graficznej.
Założeniami są funkcje takie jak tworzenie nowych plikow, zapis, odczyt, menu,modyfikacja juz istniejacych, funkcje wklej/wytnij/skopiuj, szukanie wyrazów, fraz,zmianę czcionki, kolorów tła oraz tekstu i co jeszcze do głowy mi przyjdzie.
Do wykonania tego projektu wykorzystać planuję biblioteki SDL2, FLTK, FreeType,
Glew, OpenGL.

## Harmonogram

| Tydzień  | Opis                                                                             |
| ---------|:--------------------------------------------------------------------------------:|
| 1        | Organizacja projektu na github'ie oraz planowanie                                |
| 2-3      | Wstępny rysopis aplikacji w towarzystwie nauki wybranych bibliotek, framework'ow |
| 4        | Wdrażanie podstawowych funkcji – pisanie, usuwanie, tworzenie nowych plików      |
| 5        | Kolejne funkcje – zapis, modyfikacja, odczyt                                     |
| 6        | Wdrożenie skrótów klawiszowych do kopiowania/wycinania/wklejania                 |
| 7-8      | Organizacja projektu na github'ie oraz planowanie                                |
| 9        | Możliwość zmiany czcionki                                                        |
| 10       | Wprowadzenie możliwości personalizacji edytora                                   |
| 11       | Poprawki estetyczne                                                              |
| 12-13    | Poprawki błędów wszelakich                                                       |
| 14       | Prezentacja końcowa                                                              |


## Task 1
- Stowrzenie projektu na githubie, dodanie prowadzącego do projektu
- Utworzenie pliku źródłowego
- Utworzenie pliku konfiguracyjnego CMake
- Zbudowanie projektu
- Organizacja środowiska programistycznego (NeoVim)
- Dodanie pliku .gitignore a w nim ignorowanie folderu build oraz lib
- Stworzenie pliku main.cpp z możliwością budowy oraz uruchomienia okoienka bez żadnych większych możliwości, oprócz jego zamknięcia
---

## Task 2 
- Napotkanie problemu z inlcudowaniem czcionek z biblioteki SDL
- Modyfikacja pliku cmake w celu naprawy tego błedu 
- Możliwość uruchomienia prostego okienka z tytułem i białym tłem, którego rozmiar możemy modyfikować myszką
- Jeśli nie uda się do konca 11.11.2023 zmienię biblioteke z SDL na FLTK w ktorej na pewno bedzie mi duzo łatwiej
---

