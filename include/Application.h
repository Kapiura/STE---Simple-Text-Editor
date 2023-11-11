#pragma once
#include "EditorWindow.h"
#ifndef APPLICATION_H
#define APPLICATION_H
class Application {
public:
  Application();
  ~Application();

  int run();

private:
  EditorWindow *_window;
};
#endif // APPLICATION_H
