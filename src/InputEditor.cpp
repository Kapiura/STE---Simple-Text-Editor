#include "../include/InputEditor.h"
#include "../include/EditorWindow.h"
#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <sys/types.h>

// INIT

InputEditor::InputEditor(SDL_Renderer *renderer,
                         const EditorWindow &editorWindow)
    : _renderer(renderer), _font(nullptr), _editorWindow(editorWindow),
      fontSize(24), cursorOnCurrentLine(0), cursonOnCurrentChar(-1),
      _cursorVisible(true) {
  startY = 10;
  std::cout << "TextEditor object has been created\n";
  _textArea.h = editorWindow.getWindowHeight();
  _textArea.w = editorWindow.getWindowWidth();
  _textArea.x = 0;
  _textArea.y = 0;

  loadFont("assets/jetbrainsmono/JetBrainsMono-Regular.ttf", fontSize);

  _textInput.push_back("");
  for (auto &line : _textInput) {
    line = "";
  }
}

InputEditor::~InputEditor() {
  TTF_CloseFont(_font);
  std::cout << "TextEditor object has been destroyed\n";
}

void InputEditor::loadFont(const std::string &fontPath, int fontSize) {
  _font = TTF_OpenFont(fontPath.c_str(), fontSize);
  if (!_font) {
    std::cout << "SDL TTF error loading font: " << SDL_GetError() << "\n";
    exit(-1);
  }
  for (auto &line : _textInput) {
    line = "";
  }
}

// IN/OUT HANDLE

void InputEditor::handleEvents(SDL_Event &e) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_RETURN:
      handleReturnKey();
      break;
    case SDLK_UP:
      handleUpKey();
      break;
    case SDLK_DOWN:
      handleDownKey();
      break;
    case SDLK_RIGHT:
      handleRightKey();
      break;
    case SDLK_LEFT:
      handleLeftKey();
      break;
    case SDLK_BACKSPACE:
      handleBackspaceKey();
      break;
    case SDLK_v:
      if (SDL_GetModState() & KMOD_CTRL) {
        handleCtrlV();
      } else {
        char pressedChar = static_cast<char>(e.key.keysym.sym);
        _textInput[cursorOnCurrentLine] += pressedChar;
        cursonOnCurrentChar += 1;
      }
      break;
    case SDLK_z:
      if (SDL_GetModState() & KMOD_CTRL) {
        handleCtrlZ();
      } else {
        char pressedChar = static_cast<char>(e.key.keysym.sym);
        _textInput[cursorOnCurrentLine] += pressedChar;
        cursonOnCurrentChar += 1;
      }
      break;
    case SDLK_c:
      if (SDL_GetModState() & KMOD_CTRL) {
        handleCtrlCX(false);
      } else {
        char pressedChar = static_cast<char>(e.key.keysym.sym);
        _textInput[cursorOnCurrentLine] += pressedChar;
        cursonOnCurrentChar += 1;
      }
      break;
    case SDLK_x:
      if (SDL_GetModState() & KMOD_CTRL) {
        handleCtrlCX(true);
      } else {
        char pressedChar = static_cast<char>(e.key.keysym.sym);
        _textInput[cursorOnCurrentLine] += pressedChar;
        cursonOnCurrentChar += 1;
      }
      break;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
      this->handleShiftButton();
      break;
    default:
      if ((e.key.keysym.sym >= SDLK_SPACE && e.key.keysym.sym <= SDLK_z)) {
        char pressedChar;
        if (SDL_GetModState() & KMOD_SHIFT) {
          pressedChar = static_cast<char>(std::toupper(e.key.keysym.sym));
        } else {
          pressedChar = static_cast<char>(e.key.keysym.sym);
        }
        _textInput[cursorOnCurrentLine].insert(
            static_cast<int>(cursonOnCurrentChar) + 1, 1, pressedChar);
        cursonOnCurrentChar += 1;
      }
      break;
    }
  } else if (e.type == SDL_KEYUP) {
    switch (e.key.keysym.sym) {
    case SDLK_RSHIFT:
    case SDLK_LSHIFT:
      selShift.endLine = cursorOnCurrentLine;
      selShift.endChar = cursonOnCurrentChar + 1;
      std::cout << "Stop seletcing\n";
      std::cout << "Line: " << selShift.endLine
                << "\t character: " << selShift.endChar << "\n";
      break;
    }
  }
}

void InputEditor::handleReturnKey() {
  if (cursonOnCurrentChar ==
      static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1) {
    cursorOnCurrentLine += 1;
    cursonOnCurrentChar = -1;
    _textInput.insert(_textInput.begin() + cursorOnCurrentLine, 1, "");
  } else if (cursonOnCurrentChar == -1) {
    std::string temp = _textInput[cursorOnCurrentLine];
    _textInput[cursorOnCurrentLine] = "";
    cursorOnCurrentLine += 1;
    cursonOnCurrentChar = -1;
    _textInput.insert(_textInput.begin() + cursorOnCurrentLine, 1, temp);
  } else if (cursonOnCurrentChar > -1 ||
             cursonOnCurrentChar <
                 static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1) {
    std::string temp =
        _textInput[cursorOnCurrentLine].substr(cursonOnCurrentChar + 1);
    _textInput[cursorOnCurrentLine].erase(
        cursonOnCurrentChar + 1, _textInput[cursorOnCurrentLine].size() - 1);
    cursorOnCurrentLine += 1;
    cursonOnCurrentChar = -1;
    _textInput.insert(_textInput.begin() + cursorOnCurrentLine, 1, temp);
  }
}

void InputEditor::handleUpKey() {
  if (cursorOnCurrentLine > 0) {
    cursorOnCurrentLine -= 1;
  }
  if (cursonOnCurrentChar >
      static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1) {
    cursonOnCurrentChar =
        static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1;
  }
}

void InputEditor::handleDownKey() {
  if (cursorOnCurrentLine < static_cast<int>(_textInput.size()) - 1) {
    cursorOnCurrentLine += 1;
  }
  if (cursonOnCurrentChar >
      static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1) {
    cursonOnCurrentChar =
        static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1;
  }
}

void InputEditor::handleRightKey() {
  if (cursonOnCurrentChar <
      static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1) {
    cursonOnCurrentChar += 1;
  } else if (cursonOnCurrentChar ==
                 static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1 &&
             cursorOnCurrentLine < static_cast<int>(_textInput.size()) - 1) {
    cursorOnCurrentLine += 1;
    cursonOnCurrentChar = -1;
  }
}

void InputEditor::handleLeftKey() {
  if (cursonOnCurrentChar >= 0) {
    cursonOnCurrentChar -= 1;
  } else if (cursonOnCurrentChar == -1 && cursorOnCurrentLine > 0) {
    cursorOnCurrentLine -= 1;
    cursonOnCurrentChar =
        static_cast<int>(_textInput[cursorOnCurrentLine].size()) - 1;
  }
}

void InputEditor::handleBackspaceKey() {
  // jesli jestesmy na lini dalszej niz 1 oraz kursor jest na poczatku
  // oraz linia nie jest pusta
  // ustawiamy kursor na koncu poprzzedniej linii
  // dodajemy do poprzedniej linii zawratosc usuwanej
  // kursor leci na poprzednia linie
  // usuwamy usuwana linie
  if (cursorOnCurrentLine > 0 && cursonOnCurrentChar == -1 &&
      !_textInput.empty()) {
    cursonOnCurrentChar = _textInput[cursorOnCurrentLine - 1].size() - 1;
    _textInput[cursorOnCurrentLine - 1] += _textInput[cursorOnCurrentLine];
    _textInput.erase(_textInput.begin() + cursorOnCurrentLine);
    cursorOnCurrentLine -= 1;
  }
  // jesli linia tekstu nie jest pusta
  else if (!_textInput[cursorOnCurrentLine].empty()) {
    // jesli kursor jest dalej niz na poczatkiu linii
    // usuwamy dany znak z linii
    if (cursonOnCurrentChar > -1) {
      _textInput[cursorOnCurrentLine].erase(cursonOnCurrentChar, 1);
      cursonOnCurrentChar -= 1;
    }
    // jesli jest pusta i kursor jest na lini dalszej niz pierwsza
    // usuwa nam dany wiersz i kieruje logicznie kursor
  } else if (_textInput[cursorOnCurrentLine].empty() &&

             cursorOnCurrentLine > 0) {
    _textInput.erase(_textInput.begin() + cursorOnCurrentLine);
    cursorOnCurrentLine -= 1;
    cursonOnCurrentChar =
        static_cast<int>(_textInput[cursorOnCurrentLine].size() - 1);
  }
}

void InputEditor::handleCtrlV() {
  const char *clipboardText = SDL_GetClipboardText();
  if (clipboardText != nullptr) {
    _textInput[cursorOnCurrentLine].insert(cursonOnCurrentChar + 1,
                                           clipboardText);
    cursonOnCurrentChar += strlen(clipboardText);
    SDL_free(const_cast<char *>(clipboardText));
  }
  std::cout << "CTRL+V has been pressed\n";
}

void InputEditor::handleCtrlZ() { std::cout << "CTRL+Z has been pressed\n"; }

bool InputEditor::checkFileSaved(std::string fileName, std::string context) {
  std::cout << "File name ; " << fileName << "\nContext : " << context << "\n";
  return false;
}

// SELECTING
void InputEditor::handleShiftButton() {
  selShift.startLine = cursorOnCurrentLine;
  selShift.startChar = cursonOnCurrentChar + 1;
  std::cout << "Start seletcing\n";
  std::cout << "Line: " << selShift.startLine
            << "\t character: " << selShift.startChar << "\n";
}
void InputEditor::handleCtrlCX(bool isItCtrlX) {
  copiedText = "";
  int startc = selShift.startChar;
  int startl = selShift.startLine;
  int endl = selShift.endLine;
  int endc = selShift.endChar;

  if (startl > endl) {
    int temp = startl;
    startl = endl;
    endl = temp;
    temp = startc;
    startc = endc;
    endc = temp;
  } else if (startl == endl && startc > endc) {
    int temp = startc;
    startc = endc;
    endc = temp;
  }

  if (startl == endl) {
    copiedText += _textInput[startl].substr(startc, endc);
  } else if (startl + 1 == endl) {
    copiedText +=
        _textInput[startl].substr(startc, _textInput[startl].size()) + " ";
    copiedText += _textInput[endl].substr(0, endc);
  } else {
    copiedText +=
        _textInput[startl].substr(startc, _textInput[startl].size()) + " ";
    for (int i = startl + 1; i < endl; ++i) {
      copiedText += _textInput[i] + " ";
    }
    copiedText += _textInput[endl].substr(0, endc);
  }
  SDL_SetClipboardText(copiedText.c_str());
  if (isItCtrlX == true) {
    if (startl == endl) {
      _textInput[startl].erase(startc, endc);
      cursonOnCurrentChar = startc - 1;
    } else if (startl + 1 == endl) {
      _textInput[startl].erase(startc, _textInput[startl].size());
      _textInput[endl].erase(0, endc);
      cursonOnCurrentChar = startc - 1;
      cursorOnCurrentLine = startl;
    } else {
      _textInput[startl].erase(startc, _textInput[startl].size());
      for (int i = startl + 1; i < endl; ++i) {
        _textInput.erase(_textInput.begin() + i);
        endl--;
      }
      _textInput[endl].erase(0, endc);
      cursonOnCurrentChar = startc - 1;
      cursorOnCurrentLine = startl;
    }
    std::cout << "Ctrl x pressed\t\"" << copiedText << "\"\n";
  } else {

    std::cout << "Ctrl c pressed\t\"" << copiedText << "\"\n";
  }
  deleteSelectionShift();
}

void InputEditor::deleteSelectionShift() { selShift = {0, 0, 0, 0}; }

void InputEditor::handleEventMouse(SDL_Event &e) {

  if (e.type == SDL_MOUSEWHEEL) {
    int count = _textInput.size();
    int scrollY = e.wheel.y;

    if (scrollY < 0 && startY < 10) {
      std::cout << "Scroll down" << std::endl;
      startY += 32;
    } else if (scrollY > 0 && count > 11 && 10 - (count - 11) * 32 < startY) {
      std::cout << "Scroll Up" << std::endl;
      startY -= 32;
    }
    std::cout << "StartY = " << startY << "\n";
    std::cout << "Count = " << count << "\n";
  }
}

// TEXT

void InputEditor::setText(std::vector<std::string> &text) { _textInput = text; }

std::string InputEditor::getTextContent() {
  std::string result;
  for (auto it = _textInput.begin(); it != _textInput.end(); ++it) {
    std::string temp = *it;
    if (it != std::prev(_textInput.end())) {
      result += *it + "\n";
    } else {
      result += *it;
    }
  }
  return result;
}

// RENDERING

void InputEditor::renderSelectShift() {}

void InputEditor::renderBlankSpaces() {
  // render menu space and space for line and char number of text
  // current size of window
  int windowWidth, windowHeight;
  SDL_GetWindowSize(_editorWindow.getWindow(), &windowWidth, &windowHeight);
  // creating rect of size for menu and numbers
  SDL_Rect blankRect{0, windowHeight - 40, windowWidth, 40};
  SDL_SetRenderDrawColor(_renderer, _barColor.r, _barColor.g, _barColor.b,
                         _barColor.a);
  SDL_RenderDrawRect(_renderer, &blankRect);
  SDL_RenderFillRect(_renderer, &blankRect);
}
void InputEditor::lineNumber() {
  // window size
  int windowWidth, windowHeight;
  SDL_GetWindowSize(_editorWindow.getWindow(), &windowWidth, &windowHeight);
  // line and character number
  std::string tempLine = "Line : " + std::to_string(cursorOnCurrentLine + 1);
  std::string tempCharNumber =
      "Char : " + std::to_string(cursonOnCurrentChar + 1);
  // size of text's rect
  int textWidth, textHeight;
  // rendering Line number
  SDL_Surface *tempSurface =
      TTF_RenderText_Solid(_font, tempLine.c_str(), _fontColor);
  SDL_Texture *tempTexture =
      SDL_CreateTextureFromSurface(_renderer, tempSurface);
  SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect tempRect = {15, windowHeight - 32, textWidth, textHeight};
  SDL_RenderCopy(_renderer, tempTexture, NULL, &tempRect);
  SDL_DestroyTexture(tempTexture);
  SDL_FreeSurface(tempSurface);

  // rendering Char number rect
  SDL_Surface *tempSurface1 =
      TTF_RenderText_Solid(_font, tempCharNumber.c_str(), _fontColor);
  SDL_Texture *tempTexture1 =
      SDL_CreateTextureFromSurface(_renderer, tempSurface1);
  SDL_QueryTexture(tempTexture1, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect tempRect1 = {windowWidth - textWidth - 15, windowHeight - 32,
                        textWidth, textHeight};
  SDL_RenderCopy(_renderer, tempTexture1, NULL, &tempRect1);
  SDL_DestroyTexture(tempTexture1);
  SDL_FreeSurface(tempSurface1);
}
void InputEditor::render() {
  // rendering all InputEditor object
  this->renderTextArea();
  this->renderCursor();
  this->renderBlankSpaces();
  this->lineNumber();
}

void InputEditor::renderCursor() {
  // cursor size
  int textWidth, textHeight;
  // rendering cursor
  SDL_Surface *indexSurface = TTF_RenderText_Solid(_font, "|", _fontColor);
  SDL_Texture *indexTexture =
      SDL_CreateTextureFromSurface(_renderer, indexSurface);
  SDL_QueryTexture(indexTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect indexRect = {(cursonOnCurrentChar * 14) + 7,
                        (cursorOnCurrentLine + 1) * 32, textWidth, textHeight};
  SDL_RenderCopy(_renderer, indexTexture, NULL, &indexRect);
  SDL_DestroyTexture(indexTexture);
  SDL_FreeSurface(indexSurface);
}

void InputEditor::renderTextArea() {
  // size of text on text area
  int textWidth, textHeight;
  // rendering every line of text wirrten by user
  for (size_t i = 0; i < _textInput.size(); ++i) {
    SDL_Surface *tempSurface = TTF_RenderText_Solid(
        _font, _textInput[i].c_str(), _fontColor); // font colour
    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurface);
    SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect tempRect = {0, static_cast<int>((i + 1) * 32), textWidth,
                         textHeight};
    SDL_RenderCopy(_renderer, tempTexture, NULL, &tempRect);
    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurface);
  }
}
