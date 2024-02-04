#pragma once
#include "EditorWindow.h"
#include "FileManager.h"
#include "InputEditor.h"
#include "MenuBar.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <memory>
#ifndef APPLICATION_H
#define APPLICATION_H
class Application {
public:
  // init
  Application();
  ~Application();

  int run();
  void popUpWindow(int &btn);

  // SDL_Color returnBackgroundColor() const { return _backgroundColor; }
  // void setBackGroundColor(SDL_Color color) { _backgroundColor = color; }

private:
  EditorWindow *_window;
  InputEditor *_textEditor;
  EditorWindow *_savingWindow;
  MenuBar *_menuBar;
  InputEditor *_savingInput;
  FileManager *_filemanager;

  SDL_Color _backgroundColor = {255, 255, 255, 255};
};
#endif // APPLICATION_H
