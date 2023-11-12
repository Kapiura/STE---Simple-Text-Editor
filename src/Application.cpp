#include "../include/Application.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>

Application::Application ()
{
  std::cout << "Application object has been created\n";
  _window = new EditorWindow ("STE - SimpleTextEditor", 600, 800);
  _textEditor = new TextEditor (_window->getRenderer (), *_window);
}

Application::~Application ()
{
  std::cout << "Application object has been destroyed\n";
  delete _textEditor;
  delete _window;
}

int
Application::run ()
{
  bool quit = false;
  SDL_Event event;
  SDL_WaitEvent (&event);

  while (!quit)
    {
      while (SDL_PollEvent (&event) != 0)
        {
          if (event.type == SDL_QUIT)
            {
              quit = true;
            }
          _textEditor->handleEvents (event);
          _window->update ();
          _window->renderer ();
          _textEditor->render ();
          _textEditor->update ();
        }
    }
  return 0;
}
