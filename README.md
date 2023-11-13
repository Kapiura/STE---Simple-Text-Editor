# STE - Simple Text Editor
##### Kacper Wiszniewski - II rok ISSP - Projekt C++ 2024 - semestr zimowy

Projektuje prosty edytor tekstu, który będzie cechował się przejrzystym i eleganckim interfejsem graficznym. Główne funkcjonalności obejmują tworzenie nowych plików, zapisywanie, odczytywanie, modyfikowanie istniejących dokumentów, a także standardowe operacje edycji, takie jak wycinanie, kopiowanie, i wklejanie. Dodatkowo, planuję zaimplementować funkcje wyszukiwania słów i fraz, zmiany czcionki oraz dostosowywania kolorów tła i tekstu.

W celu realizacji tego projektu, zamierzam skorzystać z różnych bibliotek programistycznych, takich jak SDL2, FLTK, FreeType, Glew, oraz OpenGL. Te narzędzia umożliwią mi stworzenie responsywnego interfejsu użytkownika, obsługę różnych operacji na tekście, a także dostarczą narzędzi do manipulacji grafiką i czcionkami.

W trakcie projektowania będę dbał o ergonomiczność interfejsu, zapewniając użytkownikowi intuicyjną obsługę oraz umożliwiając skuteczną pracę z edytorem tekstu. Dodatkowo, zamierzam zadbać o estetykę oprawy graficznej, aby użytkownik mógł korzystać z aplikacji w komfortowy i przyjemny sposób.

## Harmonogram

| Tydzień  | Opis                                                                             |
| ---------|:--------------------------------------------------------------------------------:|
| 1        | Organizacja projektu na github'ie oraz planowanie                                |
| 2-3      | Wstępny rysopis aplikacji w towarzystwie nauki wybranych bibliotek, framework'ow |
| 4        | Wdrażanie podstawowych funkcji – pisanie, usuwanie, tworzenie nowych plików      |
| 5        | Kolejne funkcje – zapis, modyfikacja, odczyt                                     |
| 6        | Wdrożenie skrótów klawiszowych do kopiowania/wycinania/wklejania                 |
| 7-8      | Dodanie menu u góry typowego dla edytorów tekstowych                             |
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
## Task 3 
- Naprawienie błędu występującego z wczytwaniem biblioteki SDL a dokladniej z modułem odpowiadającym za czcionki (SDL_TTF)
- Lekka zmiana struktury katalogów
- Usuniecie katalogu ttf na rzecz katalogu assets, który nie tylko będzie zawierał czcionki, lecz także inne dołączane do programu pliki, czy to inne czcionki, graficzne etc.
- Modyfikacja pliku konfiguracyjnego Cmake, który zmodyfikowałem przy pomocy repozytorium pewnego użytnownika [aminosbh](https://github.com/aminosbh/sdl2-ttf-sample)
- Dodanie folderu cmake z plikami konfiguracyjnymi, pomagjące w lokalizacji bibliotek SDL, które rowniez należa do wyżej wynmienionego [użytkownika](https://github.com/aminosbh)
- Lekkie zmiany w pliku nagłówkowym Editor.h, które jednak są mało znaczące
---
## Task4
- Przedefinowanie całego projektu, dodanie struktury klas 
- Projekt składa się z klas: EditorWindow, MenuBar, Application, FileManager, SearchEngine, TextEditor
- Akutalizacja klasy Application do uruchamiania pętli programu
- Tworzenie oraz redner okna głownego w klasie EditorWindow
- Usunięcie klasy Editor która miała zarządzać oknami, lecz po przemyśleniach zmieniłem całą strukture klas
- Aktualnie po zbudowaniu projektu oraz jego włączeniu pojawia się nam na środku monitora okienko z białym tłem o rozmiarach 600x800 o nazwie STE-SimpleTextEditor z możliwością zmiany rozmiaru okna za pomocą myszki
---
