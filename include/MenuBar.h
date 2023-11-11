#pragma once

#include "EditorWindow.h"

#ifndef MENUBAR_H
#define MENUBAR_H

#include <SDL2/SDL_video.h>

class MenuBar {
public:
  MenuBar(EditorWindow *window);
  ~MenuBar();

private:
  EditorWindow *_window;
};

#endif // MENUBAR_H
