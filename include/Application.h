#pragma once

#include "EditorWindow.h"
#include "FileManager.h"
#include "InputEditor.h"
#include <SDL2/SDL_events.h>
#include <memory>

#ifndef APPLICATION_H
#define APPLICATION_H
class Application {
public:
  Application();
  ~Application();

  // void runSavingWindow();
  // void createSavingWindow();
  int run();

private:
  EditorWindow *_window;
  InputEditor *_textEditor;
  EditorWindow *_savingWindow;
  InputEditor *_savingInput;
  FileManager *_filemanager;

  // std::unique_ptr<EditorWindow> _window;
  // InputEditor *_textEditor;
  // std::unique_ptr<InputEditor> _savingInput;
  // std::unique_ptr<EditorWindow> _savingWindow;
  // SavingEditor *_savingInput;
};
#endif // APPLICATION_H
