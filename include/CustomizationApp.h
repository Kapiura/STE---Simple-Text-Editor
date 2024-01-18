#pragma once
#include "EditorWindow.h"
#include "InputEditor.h"
#include "Slider.h"
#ifndef CUSTOMIZATIONAPP_H
#define CUSTOMIZATIONAPP_H

class CustomizationApp {
public:
  CustomizationApp(EditorWindow *edit, InputEditor *in);
  ~CustomizationApp();

  void render(int mouseX, int mouseY);

  void changeSliderValue(int mouseX, int mouseY);

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
  SDL_Color backgroundColor = {198, 206, 206, 255};
};

#endif // CUSTOMIZATIONAPP_H
