#pragma once
#include "EditorWindow.h"
#include "InputEditor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#ifndef SLIDER_H
#define SLIDER_H
class Slider {
public:
  Slider(EditorWindow *window, InputEditor *_inputEditor, int x, int y, int w,
         int h);
  ~Slider();

  std::string returnColorText();

  int getValue() const { return yMove; };

  void setMoveSliderColor(int v);
  void setSliderValue(int &yy, bool isclicked);
  void setSliderValue(int v);
  void setSliderColor(int re, int gr, int bl);

  void renderSlider();
  void renderSliderMove(int mouseX, int mouseY);
  void renderValueText();

private:
  int r;
  int g;
  int b;

  SDL_Rect slider; // slider bar
  int x;
  int w;
  int y;
  int h;

  SDL_Rect sliderVal; // slider
  int xMove;
  int wMove;
  int yMove;
  int hMove;
  int rm, gm, bm;

  int min_val = 0;
  int max_val = 255;
  int fontSize = 21;

  SDL_Rect value;
  SDL_Color textColor = {0, 0, 0, 255};
  SDL_Rect button;
  TTF_Font *_font;
  SDL_Renderer *_renderer;
  InputEditor *_inputEditor;

  bool isMouseOver;
  bool isMouseOverSlider(int &mouseX, int &mouseY);

  void loadFont(const std::string &fontPath, int fontSize);
  void renderBackground();
  void updateColorText();
  void setValueText();
};
#endif // !SLIDER_H
