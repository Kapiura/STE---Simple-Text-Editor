# STE - Simple Text Editor
##### Kacper Wiszniewski - II rok ISSP - Projekt C++ 2024 - semestr zimowy

Projektuje prosty edytor tekstu, który będzie cechował się przejrzystym i eleganckim interfejsem graficznym. Główne funkcjonalności obejmują tworzenie nowych plików, zapisywanie, odczytywanie, modyfikowanie istniejących dokumentów, a także standardowe operacje edycji, takie jak wycinanie, kopiowanie, i wklejanie. Dodatkowo, planuję zaimplementować funkcje wyszukiwania słów i fraz, zmiany czcionki oraz dostosowywania kolorów tła i tekstu.

W celu realizacji tego projektu, zamierzam skorzystać z różnych bibliotek programistycznych, takich jak SDL2, FLTK, FreeType, Glew, oraz OpenGL. Te narzędzia umożliwią mi stworzenie responsywnego interfejsu użytkownika, obsługę różnych operacji na tekście, a także dostarczą narzędzi do manipulacji grafiką i czcionkami.

W trakcie projektowania będę dbał o ergonomiczność interfejsu, zapewniając użytkownikowi intuicyjną obsługę oraz umożliwiając skuteczną pracę z edytorem tekstu. Dodatkowo, zamierzam zadbać o estetykę oprawy graficznej, aby użytkownik mógł korzystać z aplikacji w komfortowy i przyjemny sposób.

## Harmonogram

| Tydzień  | Opis                                                                             |
| -------- | -------------------------------------------------------------------------------- |
| 1        | Organizacja projektu na platformie GitHub oraz opracowanie planu projektu       |
| 2-3      | Opracowanie wstępnego opisu aplikacji wraz z badaniem wybranych bibliotek i frameworków |
| 4        | Implementacja podstawowych funkcji, takich jak pisanie, usuwanie, tworzenie nowych plików |
| 5        | Rozwinięcie funkcjonalności o zapis, modyfikację i odczyt dokumentów            |
| 6        | Wprowadzenie skrótów klawiszowych do kopiowania, wycinania i wklejania           |
| 7-8      | Dodanie menu w górnej części interfejsu, zgodnego z konwencją edytorów tekstowych |
| 9        | Implementacja możliwości zmiany czcionki w edytorze                              |
| 10       | Dodanie opcji personalizacji interfejsu edytora                                 |
| 11       | Przeprowadzenie poprawek estetycznych w interfejsie                              |
| 12-13    | Rozwiązanie wszelakich błędów i poprawki jakościowe                             |
| 14       | Przygotowanie i prezentacja końcowa projektu                                     |

### Update 6

- Usunięcie błędów związanych z poruszaniem się kursorem po linijkach oraz wyrazach.
- Program już nie dodaje automatycznie pustych znaków.
- Dodano funkcję usuwania linii po naciśnięciu przycisku BACKSPACE w przypadku, gdy linia jest pusta.
- Poprawiono wprowadzanie znaków z klawiatury, aby uniknąć wyświetlania dziwnych znaków po naciśnięciu klawiszy typu F1, F5, ESC itp.
- Dokonano ogólnej poprawy działania kursora.
- Usprawniono działanie kursora oraz proces tworzenia nowych linii w pliku.
- Dodano klasę FileManager, która jest odpowiedzialna za operacje zapisu i odczytu plików.
---

### Update 5
- Wprowadzenie obsługi klawiatury
    - Implementacja możliwości wprowadzania znaków z klawiatury
    - Umożliwienie dynamicznej edycji tekstu w edytorze
- Dodanie kursora
    - Wprowadzenie kursora w celu wizualnego wskazywania akturalnej pozycji w tekście
    - Możliwość dodawania, usuwania i modyfikowania tekstu za pomocą kursora
- Implementacja dunkcji dodawania nowych linii tekstu
- Dodanie funkcji umożliwiającej usunięcie znaku z linii, na której akutalnie znajduje się kursor
- Poruszanie się za pomocą strzałek
    - Umożliwianie poruszania się po teksćie za pomocą strzałek
    - Obsługa poruszania się zarówno wzdłuż linii, jak i między słowami
- Błędy
    - Automatyczne dodawanie białych znaków na końcu linii, mimo że nie istnieje on w zmiennej typu string
    - Błędne działanie przesuwania krusora w niektorych przypadkach
---

### Update 4
- Przedefiniowanie całego projektu, dodanie struktury klas 
- Projekt składa się z klas: EditorWindow, MenuBar, Application, FileManager, SearchEngine, TextEditor
- Aktualizacja klasy "Application" do uruchamiania pętli programu
- Tworzenie oraz renderowanie okna głównego w klasie "EditorWindow"
- Usunięcie klasy "Editor", która miała zarządzać oknami, lecz po przemyśleniach zmieniłem całą strukturę klas
- Obecnie po zbudowaniu projektu i jego uruchomieniu pojawia się okno o białym tle o rozmiarze 600x800 o nazwie "STE-SimpleTextEditor" z możliwością zmiany rozmiaru okna za pomocą myszki
---

### Update 3 
- Naprawienie błędu związane z wczytywaniem biblioteki SDL, a dokładniej z modułem odpowiadającym za czcionki (SDL_TTF)
- Lekka zmiana struktury katalogów
- Usunięcie katalogu "ttf" na rzecz katalogu "assets", który będzie zawierał nie tylko czcionki, lecz także inne pliki dołączane do programu, takie jak inne czcionki, grafiki, itp.
- Modyfikacja pliku konfiguracyjnego CMake, z pomocą repozytorium użytkownika [aminosbh](https://github.com/aminosbh/sdl2-ttf-sample)
- Dodanie folderu "cmake" z plikami konfiguracyjnymi pomagającymi w lokalizacji bibliotek SDL, również dostarczonymi przez [wyżej wymienionego użytkownika](https://github.com/aminosbh)
- Lekkie zmiany w pliku nagłówkowym "Editor.h", jednak mające niewielki wpływ na funkcjonalność
---

### Update 2
- Napotkanie problemu z includowaniem czcionek z biblioteki SDL
- Modyfikacja pliku cmake w celu naprawy tego błędu 
- Możliwość uruchomienia prostego okienka z tytułem i białym tłem, którego rozmiar możemy modyfikować myszką
- Jeśli nie uda się do końca 11.11.2023, zmienię bibliotekę z SDL na FLTK, w której na pewno będzie mi łatwiej
---

### Update 1 
- Stworzenie projektu na GitHubie, dodanie prowadzącego do projektu
- Utworzenie pliku źródłowego
- Utworzenie pliku konfiguracyjnego CMake
- Zbudowanie projektu
- Organizacja środowiska programistycznego (NeoVim)
- Dodanie pliku .gitignore z ignorowaniem folderu build oraz lib
- Stworzenie pliku main.cpp z możliwością budowy oraz uruchomienia okienka bez żadnych większych funkcji, oprócz jego zamknięcia
