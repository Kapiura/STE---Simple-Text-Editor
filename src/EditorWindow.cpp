#include "../include/EditorWindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <iostream>

EditorWindow::EditorWindow (const char *title, int height, int width)
    : _title (title), _height (height), _width (width)
{
  // Simple text durign creating an object of EditorWindow class
  std::cout << "EditorWindow object has been created\n";
  // Check if initializing SDL works
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      std::cout << "SDL error during init: " << SDL_GetError () << "\n";
      exit (-1);
    }
  // Check if fonts initialize well
  if (TTF_Init () < 0)
    {
      std::cout << "SDL_ttf error during init: " << SDL_GetError () << "\n";
      exit (-1);
    }
  // Creating window and renderer
  _window = SDL_CreateWindow (_title, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, _width, _height,
                              SDL_WINDOW_RESIZABLE);
  _renderer = SDL_CreateRenderer (_window, -1, SDL_RENDERER_ACCELERATED);
  // CHeck if renderer and window was created valid
  if (!_window)
    {
      std::cout << "SDL error while creating window: " << SDL_GetError ()
                << "\n";
    }
  if (!_renderer)
    {
      std::cout << "SDL error while creating renderer: " << SDL_GetError ()
                << "\n";
    }
  SDL_SetWindowMinimumSize (_window, 150, 100);
}

EditorWindow::~EditorWindow ()
{
  SDL_DestroyRenderer (_renderer);
  SDL_DestroyWindow (_window);
  TTF_CloseFont (_font);
  TTF_Quit ();
  SDL_Quit ();
  std::cout << "EditorWindow object has been destroyed\n";
}

void
EditorWindow::update ()
{
  // std::cout << "Update\n";
}
void
EditorWindow::renderer ()
{
  SDL_RenderClear (_renderer);
  SDL_RenderPresent (_renderer);
}

int
EditorWindow::getWindowWidth () const
{
  int width, height;
  SDL_GetWindowSize (_window, &width, &height);
  return width;
}

int
EditorWindow::getWindowHeight () const
{
  int width, height;
  SDL_GetWindowSize (_window, &width, &height);
  return height;
}

SDL_Renderer *
EditorWindow::getRenderer () const
{
  return _renderer;
}
