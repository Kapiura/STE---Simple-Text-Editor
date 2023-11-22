#ifndef SAVING_WINDOW_H
#define SAVING_WINDOW_H

#include "EditorWindow.h"

class SavingWindow : private EditorWindow {
public:
  SavingWindow();
  ~SavingWindow();

private:
  std::string savingPath;
};

#endif // SAVING_WINDOW_H
