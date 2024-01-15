#pragma once
#include "EditorWindow.h"
#include "Slider.h"
#ifndef CUSTOMIZATIONAPP_H
#define CUSTOMIZATIONAPP_H

class CustomizationApp {
public:
  CustomizationApp(EditorWindow *edit);
  ~CustomizationApp();

  void render();

private:
  EditorWindow *_editorWindow;
  int _width;
  int _height;
  TTF_Font *_font;
  Slider *sliderRed;
  Slider *sliderGreen;
  Slider *sliderBlue;
};

#endif // CUSTOMIZATIONAPP_H
