#include "../include/Application.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_messagebox.h>
#include <cstdlib>
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

  while (!quit)
    {
      while (SDL_PollEvent (&event) != 0)
        {

          if (event.type == SDL_QUIT)
            {
              int btn;
              SDL_MessageBoxData messageboxdata;
              messageboxdata.flags = SDL_MESSAGEBOX_INFORMATION;
              messageboxdata.window = _window->getWindow ();
              messageboxdata.title = "Are you really wanna leave the program?";
              messageboxdata.message
                  = "Are you really want to quit without saving?";
              SDL_MessageBoxButtonData buttons[] = {
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Yes" },
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No" },
              };
              messageboxdata.buttons = buttons;
              messageboxdata.numbuttons = SDL_arraysize (buttons);
              if (SDL_ShowMessageBox (&messageboxdata, &btn) < 0)
                {
                  SDL_LogError (
                      SDL_LOG_CATEGORY_APPLICATION,
                      "Error displaying message box! SDL_Error: %s\n",
                      SDL_GetError ());
                }
              if (btn == 0)
                {
                  quit = true;
                }
              else if (btn == 1)
                {
                  // _saving_window = new SavingWindow ();
                  std::string textContent = _textEditor->getTextContent ();
                  std::string filePathToSave = "~";
                  std::string command = "xdg-open " + filePathToSave;
                  if (system (command.c_str ()) == -1)
                    {
                      std::cerr << "Error opening file manager! Failed to "
                                   "execute command."
                                << std::endl;
                    }
                }
            }

          _textEditor->handleEvents (event);
          _window->update ();
          _textEditor->update ();
          _window->renderer ();
          _textEditor->render ();
        }
    }
  return 0;
}
