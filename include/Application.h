#pragma once

#include "EditorWindow.h"
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
};
#endif // APPLICATION_H
