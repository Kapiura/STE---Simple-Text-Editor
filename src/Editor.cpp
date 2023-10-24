#include "../include/Editor.h"
#include <SDL2/SDL.h>
#include <iostream>

Editor::Editor (const char *title, int width, int height)
    : title (title), width (width), height (height)
{
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      std::cout << "Init SDL error: " << SDL_GetError () << "\n";
      exit (-1);
    }

  window = SDL_CreateWindow (title, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, width, height,
                             SDL_WINDOW_SHOWN);

  renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

  if (!window)
    {
      std::cout << "Error during creating window: " << SDL_GetError () << "\n";
      exit (-1);
    }
}

Editor::~Editor ()
{
  SDL_DestroyWindow (window);
  SDL_DestroyRenderer (renderer);
  SDL_Quit ();
}
void
Editor::run ()
{
  bool quit = false;
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
      SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
      SDL_RenderClear (renderer);
      SDL_RenderPresent (renderer);

      SDL_Delay (16);
    }
}
