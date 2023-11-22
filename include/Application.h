#pragma once

#include "EditorWindow.h"
#include "SavingFile.h"
#include "TextEditor.h"

#ifndef APPLICATION_H
#define APPLICATION_H
class Application {
public:
  Application();
  ~Application();

  int run();

private:
  EditorWindow *_window;
  TextEditor *_textEditor;
  // SavingWindow _saving_window;
};
#endif // APPLICATION_H
