#pragma once
#include "EditorWindow.h"
#include "InputEditor.h"
#include "Slider.h"
#include <SDL2/SDL_rect.h>
#ifndef CUSTOMIZATIONAPP_H
#define CUSTOMIZATIONAPP_H

class CustomizationApp {
public:
  // init
  CustomizationApp(EditorWindow *edit, InputEditor *in);
  ~CustomizationApp();

  // render
  void render(int &mouseX, int &mouseY, SDL_Event &e);

  void changeSliderValue(int &mouseX, int &mouseY, bool isclicked);
  void renderButtons(int &mouseX, int &mouseY);
  void mouseOverButton(int &mouseX, int &mouseY);
  void loadFont(const std::string &fontPath, int fontSize);
  bool isMouseOverBtns(int &mouseX, int &mouseY, SDL_Rect &temp);
  void buttonFun(int &mouseX, int &mouseY, SDL_Event &e);

  // update
  void setSliderColorBackground();
  void setSliderColorFont();
  void changeBackgroundColor(bool ziutek);

private:
  EditorWindow *_editorWindow;
  InputEditor *_editorInput;
  int _width;
  int _height;
  TTF_Font *_font;

  Slider *sliderRed;
  Slider *sliderGreen;
  Slider *sliderBlue;
  SDL_Rect btnSetDefault;
  SDL_Rect btnSetCurrent;
  SDL_Rect btnSelectFont;
  SDL_Rect btnSelectBackground;
  SDL_Color backgroundColor = {198, 206, 206, 255};
  bool isBackgroundSelected;
};

#endif // CUSTOMIZATIONAPP_H
