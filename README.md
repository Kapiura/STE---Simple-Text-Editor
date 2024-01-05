# STE - Simple Text Editor
##### Kacper Wiszniewski - II rok ISSP - Projekt C++ 2024 - semestr zimowy

Projektuje prosty edytor tekstu, który będzie cechował się przejrzystym i eleganckim interfejsem graficznym. Główne funkcjonalności obejmują tworzenie nowych plików, zapisywanie, odczytywanie, modyfikowanie istniejących dokumentów, a także standardowe operacje edycji, takie jak wycinanie, kopiowanie, i wklejanie. Dodatkowo, planuję zaimplementować funkcje wyszukiwania słów i fraz, zmiany czcionki oraz dostosowywania kolorów tła i tekstu.

W celu realizacji tego projektu, zamierzam skorzystać z różnych bibliotek programistycznych, takich jak SDL2, FLTK, FreeType, Glew, oraz OpenGL. Te narzędzia umożliwią mi stworzenie responsywnego interfejsu użytkownika, obsługę różnych operacji na tekście, a także dostarczą narzędzi do manipulacji grafiką i czcionkami.

W trakcie projektowania będę dbał o ergonomiczność interfejsu, zapewniając użytkownikowi intuicyjną obsługę oraz umożliwiając skuteczną pracę z edytorem tekstu. Dodatkowo, zamierzam zadbać o estetykę oprawy graficznej, aby użytkownik mógł korzystać z aplikacji w komfortowy i przyjemny sposób.

## Harmonogram

| Tydzień  | Opis                                                                             |
| -------- | -------------------------------------------------------------------------------- |
| 1 : [16.10.2023]-[22.10.2023]        | Organizacja projektu na platformie GitHub oraz opracowanie planu projektu       |
| 2-3 : [23.10.2023]-[05.11.2023]      | Opracowanie wstępnego opisu aplikacji wraz z badaniem wybranych bibliotek i frameworków |
| 4 : [06.11.2023]-[12.11.2023]        | Implementacja podstawowych funkcji, takich jak pisanie, usuwanie, tworzenie nowych plików |
| 5 : [13.11.2023]-[19.11.2023]         | Rozwinięcie funkcjonalności o zapis, modyfikację i odczyt dokumentów            |
| 6 : [20.11.2023]-[26.11.2023]        | Wprowadzenie skrótów klawiszowych do kopiowania, wycinania i wklejania           |
| 7-8 : [27.11.2023]-[10.12.2023]       | Dodanie menu w górnej części interfejsu, zgodnego z konwencją edytorów tekstowych |
| 9 : [11.12.2023]-[17.12.2023]         | Implementacja możliwości zmiany czcionki w edytorze                              |
| 10 : [18.12.2023]-[24.12.2023]        | Dodanie opcji personalizacji interfejsu edytora                                 |
| 11 : [25.12.2023]-[31.12.2023]       | Przeprowadzenie poprawek estetycznych w interfejsie                              |
| 12-13 : [01.01.2024]-[14.01.2024]    | Rozwiązanie wszelakich błędów i poprawki jakościowe                             |
| 14 : [15.01.2024]-[21.01.2024]       | Przygotowanie i prezentacja końcowa projektu                                     |

## Przykład działania prototypu
![](https://github.com/Kapiura/STE---Simple-Text-Editor/blob/main/Reademe_assets/2ndPrototype.gif)
---


### Update 11

**Naprawienia i Ulepszenia:**

- **Naprawiony Błąd z Poruszaniem Się Strzałkami:**
  - Usunięto problem z poruszaniem się między linijkami za pomocą strzałek, zapewniając płynne nawigowanie.

- **Ulepszenie Funkcji Przycisku Backspace:**
  - Teraz kliknięcie przycisku Backspace na początku linii usuwa nową linię i dołącza ją do poprzedniej, zgodnie z większością edytorów tekstu.

- **Poprawienie Wyświetlania Menubara:**
  - Zoptymalizowano wyświetlanie menubara dla lepszej czytelności i estetyki.

- **Funkcje Menubara:**
  - Dodano działające funkcje menubara, takie jak:
    - Utworzenie nowego pliku
    - Otwarcie pliku
    - Szybkie zapisanie aktualnego pliku
    - Zapisanie pliku jako o danej nazwie
    - Zamknięcie aplikacji
    - Wklejanie
    - Cofnięcie ostatniego ruchu (jeszcze nie działa, ale przycisk jest gotowy do użycia)
    - Opcje (jeszcze nie działają, ale przycisk jest gotowy do użycia)
    - Creditsy

- **Poprawienie Zapisywania i Otwierania Plików:**
  - Zmniejszono błąd związany z zapisywaniem i otwieraniem plików.

- **Błąd z Dużymi Plikami:**
  - Zidentyfikowano problem z obsługą dużych plików (około 40 kB), który powoduje trudności dla komputera.
---

### Update 10

- **Naprawienie Wpisywania Nazwy Pliku w Oknie Zapisu:**
  - Poprawiono problem z wpisywaniem nazwy pliku w oknie zapisu, aby umożliwić bezproblemowe zapisywanie.

- **Otwieranie i Ładowanie Plików:**
  - Dodano funkcję otwierania plików oraz ładowania ich zawartości do aplikacji.

- **Modyfikacja Plików i Zapis:**
  - Teraz możliwe jest modyfikowanie plików w aplikacji i zapisywanie wprowadzonych zmian.
---

### Update 9

- **Szybki Zapis za Pomocą Paska Narzędzi:**
  - Dodana funkcja szybkiego zapisu, umożliwiająca zapis aktualnie modyfikowanego pliku za pomocą paska narzędzi.

- **Poprawienie Wyskakującego Okna Przy Zamykaniu Programu:**
  - Usunięcie problemu z wyskakującym oknem przy zamykaniu programu, zapewniając płynne zakończenie działania aplikacji.

- **Okienko z Creditsami:**
  - Dodane wyskakujące okienko z informacjami o autorze i innych współtwórcach.

- **Opcja Wklejania z Menubaru:**
  - Dodana opcja wklejania tekstu za pomocą przycisku "Paste" w menubarze.

- **Poprawa Nawigacji Kursorem za Pomocą Klawiatury:**
  - Naprawa błędów związanych z nawigacją kursorem za pomocą klawiatury, zapewniając płynne i poprawne poruszanie się po tekście.
  - Do naprawienia jeszcze kilka zwiazanych z poruszaniem sie prawo lewo po innych liniach niz dotychczasowa.
---



### Update 8
- **Pasek Nawigacyjny:**
  - Dodany pasek ułatwiający obsługę plików.
  - Nowe funkcje obejmują: 
    - Utwórz nowy plik
    - Otwórz istniejący plik
    - Zapisz plik
    - Zapisz plik jako
    - Zamknij aplikację
    - Cofnij (undo) i Wklej (paste) w obszarze edytora
    - Dostęp do opcji dostosowywania (customization) oraz informacji o autorze (credits)

- **Poprawione Wstawianie Tekstu:**
  - Zoptymalizowano proces wstawiania tekstu dla lepszej wydajności i precyzji.

- **Obsługa Paska Narzędzi:**
  - Dodana obsługa paska narzędzi umożliwiającego szybki dostęp do różnych funkcji aplikacji.

- **Przyciski File, Edit, Options:**
  - Każda z zakładek zawiera teraz działające opcje:
    - File: Nowy plik, Zapisz jako, Zamknij
    - Edit: Cofnij, Wklej
    - Options: Dostosowanie aplikacji, Informacje o autorze

- **Licznik Linii i Pozycja Kursora:**
  - Dodany licznik linii, aby łatwo śledzić aktualną pozycję w pliku.

- **Poruszanie się po Drzewku Systemu:**
  - Dodana możliwość poruszania się po strukturze drzewa systemu dla wygodniejszej nawigacji.

- **Poprawione Wstawianie Tekstu w Nazwę Pliku:**
  - Usprawniono proces wstawiania tekstu do nazwy pliku, eliminując błędy.
---


### Update 7
- Utworzenie prostego file managera, umożliwiający poruszanie sie po drzewku katalogu, wybieranie konretnych plikow
- Dodanie komunikatu typu pop-up, pytającego użytkownika, czy na pewno chce opuścić program bez zapisywania. Jeśli odpowiedź jest pozytywna, program zamyka się poprawnie. W przypadku negatywnej odpowiedzi, program otwiera drugie okno w celu zapisu.
- Naprawienie błędu związane z występowaniem białych znaków podczas pisania.
- Dodanie pod skrótem klawiszowym CTRL+V, dopisywanie do lini tekstu ze schowka.
---

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
