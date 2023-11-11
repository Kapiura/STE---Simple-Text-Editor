#include "../include/Editor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>

Editor::Editor (const char *title, int width, int height)
    : _title (title), _width (width), _height (height)
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      std::cout << "Init SDL error: " << SDL_GetError () << "\n";
      exit (-1);
    }
  if (!_font)
    {
      std::cout << "TTF_OpenFont Error: " << SDL_GetError () << "\n";
      exit (-1);
    }

  _window = SDL_CreateWindow (_title, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, _width, _height,
                              SDL_WINDOW_RESIZABLE);

  _renderer = SDL_CreateRenderer (_window, -1, SDL_RENDERER_ACCELERATED);

  // Initialize TTF
  if (TTF_Init () < 0)
    {
      std::cout << "TTF_Init Error: " << TTF_GetError () << "\n";
      exit (-1);
    }
  // _surface = TTF_RenderText_Solid (_font, "Hello", _textColor);

  if (!_window || !_renderer)
    {
      std::cout << "Error during "
                   "creating window: "
                << SDL_GetError () << "\n";
      exit (-1);
    }

  // loading options from json file

  // SDL_SetRenderDrawColor (_renderer, _backgroundColor.r, _backgroundColor.g,
  // _backgroundColor.b, _backgroundColor.a);
}

Editor::~Editor ()
{
  SDL_DestroyRenderer (_renderer);
  SDL_DestroyWindow (_window);
  TTF_Quit ();
  SDL_Quit ();
}
void
Editor::loop ()
{
  _backgroundColor = { 255, 255, 255, 255 } bool quit = false;
  SDL_Event event;

  while (!quit)
    {
      while (SDL_PollEvent (&event) != 0)
        {
          if (event.type == SDL_QUIT)
            {
              quit = true;
            }
        }

      SDL_SetRenderDrawColor (_renderer, ) SDL_RenderClear (_renderer);
      SDL_RenderPresent (_renderer);

      SDL_Delay (16);
    }
}
