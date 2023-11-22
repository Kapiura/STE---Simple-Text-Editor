#pragma once

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class EditorWindow {
public:
  EditorWindow(std::string title, int height, int width);
  ~EditorWindow();

  SDL_Renderer *getRenderer() const;
  SDL_Window *getWindow() const;

  int getWindowHeight() const;
  int getWindowWidth() const;

  void update();
  void renderer();

protected:
  std::string _title;
  std::string _file_name;
  int _height;
  int _width;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  TTF_Font *_font;
};

#endif // EDITORWINDOW_H
