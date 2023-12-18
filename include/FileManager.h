#pragma once
#include "EditorWindow.h"
#include "InputEditor.h"
#include "SaveManager.h"
#include <SDL2/SDL_config-x86_64.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include <dirent.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#ifndef FILEMANAGER_H
#define FILEMANAGER

class FileManager {
public:
  FileManager(EditorWindow *w, InputEditor *iw, std::filesystem::path path);
  ~FileManager();
  void loadFont(const std::string &fontPath, int fontSize);
  void renderCurrentPath();
  void renderFiles();
  void render();
  void renderNewFile();

  std::filesystem::path getFilePath() const { return _path; }
  std::string getFileNewName() const { return _file_name; }

private:
  std::string _file_name;
  int fontSize;
  std::filesystem::path _path;
  EditorWindow *_windowSaving;
  InputEditor *_savingInput;
  SDL_Renderer *_renderer;
  TTF_Font *_font;
  struct dirent *entry;
  DIR *dir;
  std::vector<std::filesystem::path> pathHistory;
  int currPath;
  int startY;
  int maxY;
  int startMaxY;

  int currentCursorPosition;

  struct MyButton {
    int btnX;
    int btnY;
    int btnW;
    int btnH;
    std::string name;
    SDL_Color buttonColor;
  };
  std::vector<MyButton> btnGroup;
  std::vector<std::string> btnNames;
  std::vector<std::array<int, 2>> btnXY;
  std::vector<std::array<int, 2>> btnWH;

public:
  void renderBlankSpaces();
  void btnRender(MyButton butt);
  bool IsMouseOver(int mouseX, int mouseY, MyButton btn) const;
  void changeButtonColor(MyButton &btn, SDL_Color col);
  void handleEventMouse(SDL_Event &e, bool &q);
  void handleButtonClick(const MyButton &btn, bool &q);
  void saveNewFile();
  bool IsMouseOverFolderFile(const std::filesystem::directory_entry &entry,
                             int index) const;
  bool IsMouseOverFolder(int mouseX, int mouseY,
                         const std::filesystem::directory_entry &entry) const;
  std::string getFileName() const { return _file_name; }
  void handleEventKeyboard(SDL_Event &e, bool &q);

  void handleRight();
  void handleLeft();
  void handleBackspace();
  void handleKeyboard();

  void renderCursor();
};

#endif // !FILEMANAGER_H
