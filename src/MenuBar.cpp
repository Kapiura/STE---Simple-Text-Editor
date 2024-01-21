#include "../include/MenuBar.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <immintrin.h>
#include <iostream>

MenuBar::MenuBar(EditorWindow *w, InputEditor *ie)
    : _windowEditor(w), _inputEditor(ie),
      _renderer(_windowEditor->getRenderer()) {
  int tempx = 1;
  // SDL_Color backgroundcolor = { 255, 255, 255, 255 };
  // main options
  std::vector<std::string> tempStr = {"File", "Edit", "Options"};
  for (auto &el : tempStr) {
    int textWidth, textHeight;
    std::string tempStr = el;

    // Render text to get its size
    SDL_Surface *tempSurf = TTF_RenderText_Solid(_inputEditor->getFont(),
                                                 tempStr.c_str(), _fontColor);

    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurf);

    SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);

    SDL_Color col = {0, 0, 0, 0};
    SDL_Rect rect = {tempx, 0, textWidth, textHeight};

    // Update size of the rectangle based on text size
    selOps.push_back({el, tempx, 0, textWidth, textHeight, col, false, rect});

    // Increment tempx by the total width of the text and some padding
    tempx += textWidth + 10;

    // Clean up
    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurf);
  }
  // File - New Open Save Save as Close
  int tempy = selOps[0].h;
  tempx = selOps[0].x;
  tempStr = {"New", "Open", "Save", "Save as", "Close"};
  for (auto &el : tempStr) {
    int textWidth, textHeight;
    std::string tempStr = el;
    SDL_Surface *tempSurf = TTF_RenderText_Solid(_inputEditor->getFont(),
                                                 tempStr.c_str(), _fontColor);
    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurf);
    SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Color col = {255, 255, 255, 255};
    SDL_Rect rect = {tempx, tempy, textWidth, textHeight};

    selFile.push_back(
        {el, tempx, tempy, textWidth, textHeight, col, false, rect});
    tempy += textHeight + 2;

    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurf);
  }
  // Edit Undo Paste
  tempy = selOps[1].h;
  tempx = selOps[1].x;
  tempStr = {"Undo", "Paste"};

  for (auto &el : tempStr) {
    int textWidth, textHeight;
    std::string tempStr = el;
    SDL_Surface *tempSurf = TTF_RenderText_Solid(_inputEditor->getFont(),
                                                 tempStr.c_str(), _fontColor);
    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurf);
    SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Color col = {255, 255, 255, 255};
    SDL_Rect rect = {tempx, tempy, textWidth, textHeight};

    selEdit.push_back(
        {el, tempx, tempy, textWidth, textHeight, col, false, rect});
    tempy += textHeight + 2;

    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurf);
  }

  tempy = selOps[2].h;
  tempx = selOps[2].x;
  tempStr = {"Customize", "Credits"};

  for (auto &el : tempStr) {
    int textWidth, textHeight;
    std::string tempStr = el;
    SDL_Surface *tempSurf = TTF_RenderText_Solid(_inputEditor->getFont(),
                                                 tempStr.c_str(), _fontColor);
    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurf);
    SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Color col = {255, 255, 255, 255};
    SDL_Rect rect = {tempx, tempy, textWidth, textHeight};

    selOptions.push_back(
        {el, tempx, tempy, textWidth, textHeight, col, false, rect});
    tempy += textHeight + 2;

    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurf);
  }
  for (auto &el : selOps) {
    changeButtonColor(el, {198, 206, 206, 255});
  }

  std::cout << "MenuBar object has been created\n";
}

MenuBar::~MenuBar() { std::cout << "MenuBar object has been destroyed\n"; }

void MenuBar::render() {
  int windowHeight, windowWidth;
  SDL_GetWindowSize(_windowEditor->getWindow(), &windowWidth, &windowHeight);
  this->lineRender(windowWidth);
  this->textsRender();
}

void MenuBar::lineRender(int const &windowWidth) {
  SDL_SetRenderDrawColor(_renderer, _barColor.r, _barColor.g, _barColor.b,
                         _barColor.a);
  SDL_Rect blankRect{0, 0, windowWidth, 32};
  SDL_RenderDrawRect(_renderer, &blankRect);
  SDL_RenderFillRect(_renderer, &blankRect);
}

void MenuBar::textsRender() {
  for (auto &el : selOps) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_SetRenderDrawColor(_renderer, el.clr.r, el.clr.g, el.clr.b, el.clr.a);
    SDL_RenderDrawRect(_renderer, &el.rect);
    SDL_RenderFillRect(_renderer, &el.rect);
    SDL_Surface *tempSurf = TTF_RenderText_Solid(_inputEditor->getFont(),
                                                 el.name.c_str(), _fontColor);
    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurf);
    SDL_RenderCopy(_renderer, tempTexture, NULL, &el.rect);
    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurf);
  }
}

void MenuBar::renderOpsOption(std::vector<selectOption> &vecOps) {
  for (auto &el : vecOps) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_SetRenderDrawColor(_renderer, el.clr.r, el.clr.g, el.clr.b, el.clr.a);
    SDL_RenderFillRect(_renderer, &el.rect);
    SDL_RenderDrawRect(_renderer, &el.rect);

    SDL_Surface *tempSurf = TTF_RenderText_Solid(_inputEditor->getFont(),
                                                 el.name.c_str(), _fontColor);
    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurf);
    SDL_RenderCopy(_renderer, tempTexture, NULL, &el.rect);

    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurf);
  }
}

bool MenuBar::isMouseOver(int mouseX, int mouseY, selectOption btn) const {
  return mouseX >= btn.x && mouseX <= btn.x + btn.w && mouseY >= btn.y &&
         mouseY <= btn.y + btn.h;
}

void MenuBar::handleMouseMotion(SDL_Event &e) {
  if (e.type == SDL_MOUSEMOTION) {
    int mouseX = e.motion.x;
    int mouseY = e.motion.y;

    for (auto &el : selFile) {
      if (isMouseOver(mouseX, mouseY, el) && fileOps) {
        changeButtonColor(el, {255, 255, 0, 255});
      } else {
        changeButtonColor(el, {198, 206, 206, 255});
      }
    }
    for (auto &el : selEdit) {
      if (isMouseOver(mouseX, mouseY, el) && editOps) {
        changeButtonColor(el, {255, 255, 0, 255});
      } else {
        changeButtonColor(el, {198, 206, 206, 255});
      }
    }
    for (auto &el : selOptions) {
      if (isMouseOver(mouseX, mouseY, el) && opsOps) {
        changeButtonColor(el, {255, 255, 0, 255});
      } else {
        changeButtonColor(el, {198, 206, 206, 255});
      }
    }
    // Handling File options
    if (isMouseOver(mouseX, mouseY, selOps[0])) {
      changeButtonColor(selOps[0], {255, 255, 0, 255});
      renderOpsOption(selFile);
      fileOps = true;
    } else if ((fileOps == true &&
                (mouseX >= selOps[0].x && mouseX <= selOps[0].x + selOps[0].w &&
                 mouseY >= selOps[0].y &&
                 mouseY <= selFile[selFile.size() - 1].y +
                               selFile[selFile.size() - 1].h))) {

      changeButtonColor(selOps[0], {255, 255, 0, 255});
      renderOpsOption(selFile);
    } else {
      fileOps = false;
      changeButtonColor(selOps[0], {198, 206, 206, 255});
    }

    // Handling Edit options
    if (isMouseOver(mouseX, mouseY, selOps[1])) {
      changeButtonColor(selOps[1], {255, 255, 0, 255});
      renderOpsOption(selEdit);
      editOps = true;
    } else if ((editOps == true &&
                (mouseX >= selOps[1].x && mouseX <= selOps[1].x + selOps[1].w &&
                 mouseY >= selOps[1].y &&
                 mouseY <= selEdit[selEdit.size() - 1].y +
                               selEdit[selEdit.size() - 1].h))) {

      changeButtonColor(selOps[1], {255, 255, 0, 255});
      renderOpsOption(selEdit);
    } else {
      editOps = false;
      changeButtonColor(selOps[1], {198, 206, 206, 255});
    }

    // Handling Options options
    if (isMouseOver(mouseX, mouseY, selOps[2])) {
      changeButtonColor(selOps[2], {255, 255, 0, 255});
      renderOpsOption(selOptions);
      opsOps = true;
    } else if ((opsOps == true &&
                (mouseX >= selOps[2].x && mouseX <= selOps[2].x + selOps[2].w &&
                 mouseY >= selOps[2].y &&
                 mouseY <= selOptions[selOptions.size() - 1].y +
                               selOptions[selOptions.size() - 1].h))) {

      changeButtonColor(selOps[2], {255, 255, 0, 255});
      renderOpsOption(selOptions);
    } else {
      opsOps = false;
      changeButtonColor(selOps[2], {198, 206, 206, 255});
    }
  }
}

void MenuBar::handleEventMouse(SDL_Event &e, bool &q) {
  // Reset colors for all options
  for (auto &el : selFile)
    el.clr = {198, 206, 206, 255};
  for (auto &el : selEdit)
    el.clr = {198, 206, 206, 255};
  for (auto &el : selOptions)
    el.clr = {198, 206, 206, 255};

  this->handleMouseMotion(e);
  if (q)
    std::cout << q << "\n";

  if (e.type == SDL_MOUSEBUTTONDOWN) {
    int mouseX = e.button.x;
    int mouseY = e.button.y;

    // Check which option is clicked and handle the event
    for (auto &el : selOps) {

      if (isMouseOver(mouseX, mouseY, el)) {
        handleButtonClick(el);
        break;
      }
    }

    // Check if any file option is clicked
    if (fileOps) {
      for (auto &el : selFile) {
        if (isMouseOver(mouseX, mouseY, el) && el.name == "New") {
          int btn;
          this->PopBackWindow(
              btn, "Creating new file",
              "Are you really want to create new file and leave current?",
              "Yes", "No");
          if (btn == 0) {
            std::vector<std::string> tempTextVector = {""};
            std::cout << "New file\n";
            _inputEditor->setText(tempTextVector);
            _inputEditor->setCursorDefaulr();
          }
        }
        if (isMouseOver(mouseX, mouseY, el) && el.name == "Open") {
          _savingWindow = new EditorWindow("Opening", 250, 400);
          _filemanager = new FileManager(_savingWindow, _inputEditor,
                                         _windowEditor->getPath(), "Open");
          bool sQuit = false;
          SDL_Event sEvent;
          while (!sQuit) {
            while (SDL_PollEvent(&sEvent) != 0) {
              _filemanager->handleEventMouseOpen(sEvent, sQuit);
              if (sEvent.type == SDL_QUIT) {
                sQuit = true;
              } else if (sEvent.window.event == SDL_WINDOWEVENT_CLOSE &&
                         sEvent.window.windowID ==
                             SDL_GetWindowID(_savingWindow->getWindow())) {
                sQuit = true;
              }
              _savingWindow->render();
              _filemanager->renderOpen();
            }
          }
          delete _filemanager;
          delete _savingWindow;
        }
        if (isMouseOver(mouseX, mouseY, el) && el.name == "Save") {
          SaveManager savingProc(_windowEditor->getFileName(),
                                 _inputEditor->getTextContent(),
                                 _windowEditor->getPath());
          savingProc.saveFile(_windowEditor->getWindow());
        }

        if (isMouseOver(mouseX, mouseY, el) && el.name == "Save as") {
          _savingWindow = new EditorWindow("Saving", 250, 400);
          _filemanager = new FileManager(_savingWindow, _inputEditor,
                                         _windowEditor->getPath());
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
        if (isMouseOver(mouseX, mouseY, el) && el.name == "Close") {
          handleButtonClick(el);
          q = true;
        }
      }
    }

    // Check if any edit option is clicked
    for (auto &el : selEdit) {
      if (isMouseOver(mouseX, mouseY, el) && el.name == "Undo") {
        std::cout << "Undo\n";
      }
      if (isMouseOver(mouseX, mouseY, el) && el.name == "Paste") {
        _inputEditor->handleCtrlV();
      }
    }

    // Check if any options option is clicked
    for (auto &el : selOptions) {
      if (isMouseOver(mouseX, mouseY, el) && el.name == "Credits") {
        int btn;
        this->PopBackWindow(btn, "Credits",
                            "Text editor made by Kapiura\nAll is "
                            "written in C++ by using SDL library.",
                            "Ok");
      }
      if (isMouseOver(mouseX, mouseY, el) && el.name == "Customize") {

        _customWindow = new EditorWindow("Customization", 350, 400);
        _custom = new CustomizationApp(_customWindow, _inputEditor);
        bool sQuit = false;
        SDL_Event sEvent;
        // bool leftMouseButtonDown = false;
        // int mouseX, mouseY;
        while (!sQuit) {
          while (SDL_PollEvent(&sEvent) != 0) {
            SDL_GetMouseState(&mouseX, &mouseY);
            // mouseX = sEvent.motion.x;
            // mouseY = sEvent.motion.y;
            if (sEvent.type == SDL_QUIT) {
              sQuit = true;
            } else if (sEvent.window.event == SDL_WINDOWEVENT_CLOSE &&
                       sEvent.window.windowID ==
                           SDL_GetWindowID(_customWindow->getWindow())) {
              sQuit = true;
            }
            if (sEvent.type == SDL_MOUSEMOTION ||
                sEvent.type == SDL_MOUSEBUTTONDOWN) {
              if (sEvent.button.button == SDL_BUTTON_LEFT) {
                _custom->changeSliderValue(mouseX, mouseY, true);
              } else {
                _custom->changeSliderValue(mouseX, mouseY, false);
              }
            }
            // switch (sEvent.type) {
            // case SDL_MOUSEMOTION:
            //   // int mouseX, mouseY;
            //   // SDL_GetMouseState(&mouse1X, &mouse1Y);
            //   if (sEvent.type == SDL_MOUSEBUTTONDOWN) {
            //     if (sEvent.button.button == SDL_BUTTON_LEFT) {
            //       // int mouse1X, mouse1Y;
            //       // leftMouseButtonDown = true;
            //       // SDL_GetMouseState(&mouse1X, &mouse1Y);
            //       _custom->changeSliderValue(mouseX, mouseY);
            //     }
            //   }
            //   _custom->changeSliderValue(mouseX, mouseY);
            //   break;
            // }

            // if (sEvent.type == SDL_MOUSEMOTION) {
            //   int mouse1X, mouse1Y;
            //   SDL_GetMouseState(&mouse1X, &mouse1Y);
            //   _custom->changeSliderValue(mouse1X, mouse1Y);
            // } else
            // switch (sEvent.type) {
            // case SDL_MOUSEBUTTONDOWN:
            //   if (sEvent.button.button == SDL_BUTTON_LEFT) {
            //     int mouse1X, mouse1Y;
            //     leftMouseButtonDown = true;
            //     SDL_GetMouseState(&mouse1X, &mouse1Y);
            //     _custom->changeSliderValue(mouse1X, mouse1Y,
            //                                leftMouseButtonDown);
            //   }
            // else {
            //   leftMouseButtonDown = false;
            // }
            // break;
            // case SDL_MOUSEMOTION:
            //   int mouse1X, mouse1Y;
            //   SDL_GetMouseState(&mouse1X, &mouse1Y);
            //   _custom->changeSliderValue(mouse1X, mouse1Y,
            //   leftMouseButtonDown); break;
            // }
            _customWindow->render();
            _custom->render(mouseX, mouseY);
            SDL_RenderPresent(_customWindow->getRenderer());
          }
        }
        delete _custom;
        delete _customWindow;
      }
    }
  }
}

void MenuBar::handleButtonClick(const selectOption &btn) {
  std::cout << "Button clicked\t" << btn.name << "\n";
}

void MenuBar::PopBackWindow(int &btn, std::string title, std::string message,
                            std::string yes, std::string no) {
  SDL_MessageBoxData messageboxdata;
  messageboxdata.flags = SDL_MESSAGEBOX_WARNING;
  messageboxdata.window = _windowEditor->getWindow();
  messageboxdata.title = title.c_str();
  messageboxdata.message = message.c_str();
  SDL_MessageBoxButtonData buttons[] = {
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, yes.c_str()},
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, no.c_str()}};
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
void MenuBar::PopBackWindow(int &btn, std::string title, std::string message,
                            std::string yes) {
  SDL_MessageBoxData messageboxdata;
  messageboxdata.flags = SDL_MESSAGEBOX_WARNING;
  messageboxdata.window = _windowEditor->getWindow();
  messageboxdata.title = title.c_str();
  messageboxdata.message = message.c_str();
  SDL_MessageBoxButtonData buttons[] = {
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, yes.c_str()}};
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
