#pragma once

#include "EditorWindow.h"
#include "FileManager.h"
#include "InputEditor.h"
#include "MenuBar.h"
#include <SDL2/SDL_events.h>
#include <memory>

#ifndef APPLICATION_H
#define APPLICATION_H
class Application {
public:
  Application();
  ~Application();

  int run();

private:
  EditorWindow *_window;
  InputEditor *_textEditor;
  EditorWindow *_savingWindow;
  MenuBar *_menuBar;
  InputEditor *_savingInput;
  FileManager *_filemanager;
};
#endif // APPLICATION_H
