#include "../include/Slider.h"
#include <iostream>

Slider::Slider(TTF_Font *font) : r(255), g(255), b(255), _font(font) {
  std::cout << "Silder object has been created\n";
}

Slider::~Slider() { std::cout << "Slider object has been deleted\n"; }
