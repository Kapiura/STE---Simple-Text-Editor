#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "EditorWindow.h"
// #include "MenuBar.h"
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

class InputEditor {
public:
  InputEditor(SDL_Renderer *renderer, const EditorWindow &editorWindow);
  ~InputEditor();

  void handleEvents(SDL_Event &e);
  void update();
  void render();

  void setText(std::vector<std::string> &text);

  std::string getTextContent();

  bool checkFileSaved(std::string fileName, std::string context);

  TTF_Font *getFont() { return _font; };
  void setCursorDefault() {
    cursonOnCurrentChar = -1;
    cursorOnCurrentLine = 0;
  };
  void handleCtrlV();
  void handleCtrlZ();
  void handleEventMouse(SDL_Event &e);
  SDL_Color returnBackgroundColor() const { return _backgroundColor; }
  void setBackgroundColor(SDL_Color color) { _backgroundColor = color; }
  SDL_Color returnFontColor() const { return _fontColor; }
  void setFontColor(SDL_Color color) { _fontColor = color; }

protected:
  void renderCursor();
  void renderTextArea();

  void checkVisibleCursor();
  void changeCursorTimer();

  void loadFont(const std::string &fontPath, int fontSize);

  SDL_Renderer *_renderer;
  SDL_Rect _textArea;
  TTF_Font *_font;
  EditorWindow _editorWindow;
  std::string *_fontPath;

  void handleReturnKey();
  void handleUpKey();
  void handleDownKey();
  void handleRightKey();
  void handleLeftKey();
  void handleBackspaceKey();
  void handleShiftButton();
  void handleCtrlCX(bool isItCtrlX);
  void deleteSelectionShift();

  void lineNumber();
  void renderBlankSpaces();

private:
  std::vector<std::string> _textInput;
  int fontSize;
  int cursorOnCurrentLine;
  int cursonOnCurrentChar;
  int startY;
  bool _cursorVisible;
  std::vector<std::string> selectedText;
  struct selectionShift {
    int startLine;
    int startChar;
    int endLine;
    int endChar;
  };
  selectionShift selShift;
  std::string copiedText;

  void renderSelectShift();

  SDL_Color _fontColor = {0, 0, 0, 255};
  SDL_Color _barColor = {198, 206, 206, 255};
  SDL_Color returnBarColor() const { return _barColor; }
  SDL_Color _backgroundColor = {255, 255, 255, 255};
};

#endif // TEXTEDITOR_H
