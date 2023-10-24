#ifndef EDITOR_H
#define EDITOR_H
#include <SDL2/SDL.h>

class Editor {
public:
  Editor(const char *title, int width, int height);
  ~Editor();
  void run();

private:
  const char *title;
  int width;
  int height;
  SDL_Window *window;
};

#endif // EDITOR_H
