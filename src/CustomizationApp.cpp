#include "../include/CustomizationApp.h"
#include "../include/Slider.h"
#include <iostream>

CustomizationApp::CustomizationApp(EditorWindow *edit) : _editorWindow(edit) {
  sliderRed = new Slider(_editorWindow->getFont());
  sliderGreen = new Slider(_editorWindow->getFont());
  sliderBlue = new Slider(_editorWindow->getFont());
  std::cout << "CustomizationApp object has been created\n";
}
CustomizationApp::~CustomizationApp() {
  std::cout << "CustomizationApp object has been deleted\n";
}

void CustomizationApp::render() {
  SDL_SetRenderDrawColor(_editorWindow->getRenderer(), 200, 200, 200, 255);
}
