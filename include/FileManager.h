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
#include <asm-generic/errno.h>
#include <dirent.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#ifndef FILEMANAGER_H
#define FILEMANAGER

class FileManager {

public:
  // constructors, destructors
  // saving window
  FileManager(EditorWindow *w, InputEditor *iw, std::filesystem::path path);
  // opening window
  FileManager(EditorWindow *w, InputEditor *iw, std::filesystem::path path,
              std::string open);
  ~FileManager();

  // returns
  std::filesystem::path getFilePath() const { return _path; }
  std::string getFileNewName() const { return _file_name; }
  std::string getFileName() const { return _file_name; }

  // render
  void render();
  void renderOpen();

  // handle keyboard, mouse events
  void handleEventKeyboard(SDL_Event &e, bool &q);
  void handleEventMouseOpen(SDL_Event &e, bool &q);
  void handleEventMouse(SDL_Event &e, bool &q);

private:
  // variables
  std::string _file_name;
  int fontSize;
  std::filesystem::path _path;
  EditorWindow *_windowSaving;
  InputEditor *_editorInput;
  InputEditor *_savingInput;
  SDL_Renderer *_renderer;
  TTF_Font *_font;
  struct dirent *entry;
  DIR *dir;
  std::vector<std::filesystem::path> pathHistory;
  int currentCursorPosition;
  // scroll variables
  int currPath;
  int startY;
  int maxY;
  int startMaxY;
  // button
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

  void loadFont(const std::string &fontPath, int fontSize);

  // render
  void renderCurrentPath();
  void renderFiles();
  void renderNewFile();
  void renderCursor();
  void renderBlankSpaces();
  void btnRender(MyButton butt);
  void changeButtonColor(MyButton &btn, SDL_Color col);

  // handle keyboard, mouse events
  void handleRight();
  void handleLeft();
  void handleBackspace();
  void handleKeyboard(SDL_Event &e);
  void handleButtonClickOpen(const MyButton &btn, bool &q);
  bool IsMouseOver(int mouseX, int mouseY, MyButton btn) const;
  void handleButtonClick(const MyButton &btn, bool &q);
  bool IsMouseOverFolderFile(const std::filesystem::directory_entry &entry,
                             int index) const;
  bool IsMouseOverFolder(int mouseX, int mouseY,
                         const std::filesystem::directory_entry &entry) const;

  // file handling
  void saveNewFile();
};
#endif // !FILEMANAGER_H
