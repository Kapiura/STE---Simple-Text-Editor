#include "../include/SaveManager.h"
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_video.h>
#include <filesystem>
#include <fstream>
#include <iostream>

SaveManager::SaveManager (std::string fileName, std::string content,
                          std::filesystem::path path)
    : _file_name (fileName), _content (content), _new_file_path (path)
{
  std::cout << "SaveManager-SAVING object has been created\n";
}
SaveManager::SaveManager (std::string fileName, std::filesystem::path path)
    : _file_name (fileName), _new_file_path (path)
{
  std::cout << "SaveManager-OPEN object has been created\n";
}
SaveManager::~SaveManager ()
{
  std::cout << "SaveManager object has been destroyed\n";
}

void
SaveManager::openFile (SDL_Window *w, InputEditor *ie)
{
  // Utwórz obiekt ifstream do odczytu pliku
  std::ifstream file (_file_name);

  // Sprawdź, czy plik został poprawnie otwarty
  if (!file.is_open ())
    {
      std::cerr << "File doesnt exist\n" << std::endl;
      std::string title = "Opening";
      std::string mess = "File doesn't exist!";
      this->PopUp (w, title, mess);
    }
  else
    {
      // Odczytaj plik linia po linii
      std::string line;
      while (std::getline (file, line))
        {
          std::cout << line << std::endl;
          _contentVector.push_back (line);
        }
      ie->setText (_contentVector);
      file.close ();
      std::cout << _file_name << " has been opened\n";
      std::string title = "Opening";
      std::string mess = "File has been opened succesfully";
      this->PopUp (w, title, mess);
    }
  file.close ();
}

bool
SaveManager::isFileExist () const
{
  std::string temp = _new_file_path.string () + "/" + _file_name;
  std::cout << temp << "\n";
  if (std::filesystem::exists (temp))
    {
      return true;
    }
  else
    {
      return false;
    }
}

void
SaveManager::PopUp (SDL_Window *w, std::string title, std::string mess)
{
  int btn;
  SDL_MessageBoxData messbox;
  messbox.flags = SDL_MESSAGEBOX_INFORMATION;
  messbox.window = w;
  messbox.title = title.c_str ();
  messbox.message = mess.c_str ();
  SDL_MessageBoxButtonData buttons[]
      = { { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Ok" } };
  messbox.buttons = buttons;
  messbox.numbuttons = SDL_arraysize (buttons);
  SDL_MessageBoxColor messBackground = { 255, 255, 255 };
  SDL_MessageBoxColor messText = { 0, 0, 0 };
  SDL_MessageBoxColor messButtonBorder = { 0, 0, 0 };
  SDL_MessageBoxColor messButtonBackground = { 255, 255, 255 };
  SDL_MessageBoxColor messButtonSelected = { 150, 150, 25 };
  SDL_MessageBoxColorScheme mescolt
      = { messBackground, messText, messButtonBorder, messButtonBackground,
          messButtonSelected };
  messbox.colorScheme = &mescolt;
  if (SDL_ShowMessageBox (&messbox, &btn) > 0)
    {
      std::cerr << "Messagebox error " << SDL_GetError () << "\n";
      exit (-1);
    }
}

void
SaveManager::saveFile (bool &q, SDL_Window *w)
{
  if (!this->isFileExist ())
    {
      std::ofstream savingFile{ _file_name };
      savingFile << _content;
      savingFile.close ();
      std::cout << "New file " << _file_name << " has been created in "
                << _new_file_path << "\n";
      std::string title = "Saving";
      std::string mess = "File has been saved succesfully";
      this->PopUp (w, title, mess);
      q = true;
    }
  else
    {
      std::cout << "File has already existed\n";
      std::string title = "Saving";
      std::string mess = "File has been already existing!";
      this->PopUp (w, title, mess);
    }
}

void
SaveManager::saveFile (SDL_Window *w)
{
  if (this->isFileExist ())
    {
      std::ofstream savingFile{ _file_name };
      savingFile << _content;
      savingFile.close ();
      std::cout << "New file " << _file_name << " has been created in "
                << _new_file_path << "\n";
      std::string title = "Saving";
      std::string mess = "File has been saved succesfully";
      this->PopUp (w, title, mess);
    }
  else
    {
      std::cout << "File has already existed\n";
      std::string title = "Saving";
      std::string mess = "File has been already existing!";
      this->PopUp (w, title, mess);
    }
}
