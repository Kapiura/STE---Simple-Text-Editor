#pragma once

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <SDL2/SDL.h>

class EditorWindow {
public:
  EditorWindow(const char *title, int height, int width);
  ~EditorWindow();

  SDL_Renderer *getRenderer() const;
  SDL_Window *getWindow() const;

  void update();
  void renderer();

private:
  const char *_title;
  int _height;
  int _width;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
};

#endif // EDITORWINDOW_H
