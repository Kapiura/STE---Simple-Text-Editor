#pragma once
#include "FileManager.h"
#include "InputEditor.h"
#include <SDL2/SDL_video.h>
#include <filesystem>
#include <string>
#include <vector>
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

class SaveManager {
public:
  SaveManager(std::string fileName, std::string content,
              std::filesystem::path path);
  SaveManager(std::string fileName, std::filesystem::path path);
  ~SaveManager();

  bool isFileExist() const;
  void saveFile(bool &q, SDL_Window *w);
  void saveFile(SDL_Window *w);
  void openFile(SDL_Window *w, InputEditor *ie);
  void PopUp(SDL_Window *w, std::string title, std::string mess);

private:
  std::string _file_name;
  bool _file_exists;
  std::string _content;
  std::filesystem::path _new_file_path;
  std::vector<std::string> _contentVector;
};

#endif // SAVEMANAGER_H
