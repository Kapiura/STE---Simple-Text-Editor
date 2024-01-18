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

  void loadFont(const std::string &fontPath, int fontSize);

  void renderBackground();
  void renderSlider();
  void renderSliderMove(int mouseX, int mouseY);
  void setSliderColor(int re, int gr, int bl);
  void renderValueText();
  void updateColorText();
  std::string returnColorText();
  void setValueText();
  bool isMouseOverSlider(int mouseX, int mouseY);

  void setSliderValue(int xx, int yy);

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

  SDL_Rect value; // text under the silder bar
  SDL_Color textColor = {0, 0, 0, 255};
  // default text color for text under the slider

  SDL_Rect button;
  TTF_Font *_font;
  int min_val = 0;
  int max_val = 255;
  SDL_Renderer *_renderer;
  int fontSize = 20;
  InputEditor *_inputEditor;

  bool isMouseOver;
};

#endif // !SLIDER_H
