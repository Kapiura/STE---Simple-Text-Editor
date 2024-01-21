#include "../include/CustomizationApp.h"
#include "../include/Slider.h"
#include <iostream>

CustomizationApp::CustomizationApp(EditorWindow *edit, InputEditor *in)
    : _editorWindow(edit), _editorInput(in) {
  // window, font, x, w, y, h
  sliderRed = new Slider(_editorWindow, _editorInput, 10, 10, 10, 265);
  sliderGreen = new Slider(_editorWindow, _editorInput, 80, 10, 10, 265);
  sliderBlue = new Slider(_editorWindow, _editorInput, 150, 10, 10, 265);
  sliderRed->setSliderColor(255, 0, 0);
  sliderGreen->setSliderColor(0, 255, 0);
  sliderBlue->setSliderColor(0, 0, 255);

  std::cout << "CustomizationApp object has been created\n";
}
CustomizationApp::~CustomizationApp() {
  delete sliderRed;
  delete sliderGreen;
  delete sliderBlue;
  std::cout << "CustomizationApp object has been deleted\n";
}

void CustomizationApp::render(int mouseX, int mouseY) {
  SDL_RenderClear(_editorWindow->getRenderer());
  SDL_SetRenderDrawColor(_editorWindow->getRenderer(), backgroundColor.r,
                         backgroundColor.g, backgroundColor.b,
                         backgroundColor.a);

  sliderRed->renderSlider();
  sliderGreen->renderSlider();
  sliderBlue->renderSlider();
  sliderRed->renderSliderMove(mouseX, mouseY);
  sliderGreen->renderSliderMove(mouseX, mouseY);
  sliderBlue->renderSliderMove(mouseX, mouseY);
  sliderRed->renderValueText();
  sliderGreen->renderValueText();
  sliderBlue->renderValueText();
  SDL_SetRenderDrawColor(_editorWindow->getRenderer(), backgroundColor.r,
                         backgroundColor.g, backgroundColor.b,
                         backgroundColor.a);
}

void CustomizationApp::changeSliderValue(int &mouseX, int &mouseY,
                                         bool isCliked) {
  // render(mouseX, mouseY);
  std::cout << mouseX << "\n";
  sliderRed->setSliderValue(mouseY, isCliked);
  sliderBlue->setSliderValue(mouseY, isCliked);
  sliderGreen->setSliderValue(mouseY, isCliked);
}
