#pragma once

#ifndef EDITOR_H
#define EDITOR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Editor {
public:
  Editor(const char *title, int width, int height);
  ~Editor();

  void loop();

  void pollEvent(SDL_Event &event);
  void clear() const;

private:
  const char *_title;
  int _width;
  int _height;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Surface *_textSurface;
  SDL_Texture *_textTexture;
  SDL_Surface *_surface;
  TTF_Font *_font;
  SDL_Color _backgroundColor = {255, 255, 255, 255};
  SDL_Color _textColor = {255, 255, 255, 255};
  SDL_Color _themeColor = {255, 255, 255, 255};
};

#endif // EDITOR_H
