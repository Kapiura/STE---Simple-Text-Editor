#include "../include/Application.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <iostream>

Application::Application() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL error during init: " << SDL_GetError() << "\n";
    exit(-1);
  }
  if (TTF_Init() < 0) {
    std::cerr << "SDL_ttf error during init: " << SDL_GetError() << "\n";
    exit(-1);
  }
  _window = new EditorWindow("STE", 600, 800);
  _textEditor = new InputEditor(_window->getRenderer(), *_window);
  _menuBar = new MenuBar(_window, _textEditor);
  std::cout << "Application object has been created\n";
}

Application::~Application() {
  delete _menuBar;
  delete _textEditor;
  delete _window;
  TTF_Quit();
  SDL_Quit();
  std::cout << "Application object has been destroyed\n";
}
int Application::run() {
  bool quit = false;
  SDL_Event event;
  SDL_RenderClear(_window->getRenderer());

  while (!quit) {

    while (SDL_PollEvent(&event) != 0) {

      if (event.type == SDL_QUIT) {
        if (_textEditor->getTextContent() == "") {
          quit = true;
        } else {

          int btn;
          this->popUpWindow(btn);
          if (btn == 0) {
            quit = true;
          } else if (btn == 1) {
            _savingWindow = new EditorWindow("Saving", 250, 400);
            _filemanager =
                new FileManager(_savingWindow, _textEditor, _window->getPath());
            bool sQuit = false;
            SDL_Event sEvent;
            while (!sQuit) {
              while (SDL_PollEvent(&sEvent) != 0) {
                _filemanager->handleEventMouse(sEvent, sQuit);
                _filemanager->handleEventKeyboard(sEvent, sQuit);
                if (sEvent.type == SDL_QUIT) {
                  sQuit = true;
                } else if (sEvent.window.event == SDL_WINDOWEVENT_CLOSE &&
                           sEvent.window.windowID ==
                               SDL_GetWindowID(_savingWindow->getWindow())) {
                  sQuit = true;
                }
                _savingWindow->render();
                _filemanager->render();
              }
            }
            delete _filemanager;
            delete _savingWindow;
          }
        }
      }
      _window->render();
      _textEditor->handleEvents(event);
      _textEditor->handleEventMouse(event);
      _window->render();
      _textEditor->render();
      _menuBar->render();
      _menuBar->handleEventMouse(event, quit);
      _backgroundColor = _textEditor->returnBackgroundColor();
      SDL_SetRenderDrawColor(_window->getRenderer(), _backgroundColor.r,
                             _backgroundColor.g, _backgroundColor.b,
                             _backgroundColor.a);
      SDL_RenderPresent(_window->getRenderer());
    }
  }
  return 0;
}

void Application::popUpWindow(int &btn) {
  SDL_MessageBoxData messageboxdata;
  messageboxdata.flags = SDL_MESSAGEBOX_WARNING;
  messageboxdata.window = _window->getWindow();
  messageboxdata.title = "Leaving unsaved file";
  messageboxdata.message = "Do you really want to quit without saving?";
  SDL_MessageBoxButtonData buttons[] = {
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Yes"},
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No"}};
  messageboxdata.buttons = buttons;
  messageboxdata.numbuttons = SDL_arraysize(buttons);
  SDL_MessageBoxColor messBackground = {255, 255, 255};
  SDL_MessageBoxColor messText = {0, 0, 0};
  SDL_MessageBoxColor messButtonBorder = {0, 0, 0};
  SDL_MessageBoxColor messButtonBackground = {255, 255, 255};
  SDL_MessageBoxColor messButtonSelected = {150, 150, 25};
  SDL_MessageBoxColorScheme mescolt = {messBackground, messText,
                                       messButtonBorder, messButtonBackground,
                                       messButtonSelected};
  messageboxdata.colorScheme = &mescolt;
  if (SDL_ShowMessageBox(&messageboxdata, &btn) > 0) {
    std::cerr << "Messagebox error " << SDL_GetError() << "\n";
    exit(-1);
  }
}
