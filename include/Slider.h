#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#ifndef SLIDER_H
#define SLIDER_H
class Slider {
public:
  Slider(TTF_Font *font);
  ~Slider();

private:
  int r;
  int g;
  int b;
  SDL_Rect slider;
  int x;
  int w;
  int t;
  int h;
  SDL_Rect button;
  TTF_Font *_font;
  int min_val = 0;
  int max_val = 255;
};

#endif // !SLIDER_H
