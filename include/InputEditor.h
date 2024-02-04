#pragma once
#include "EditorWindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

class InputEditor {
public:
  // constructors, desctructor
  InputEditor(SDL_Renderer *renderer, const EditorWindow &editorWindow);
  ~InputEditor();

  // rendering
  void update();
  void render();

  // returning
  void setText(std::vector<std::string> &text);
  std::string getTextContent();
  bool checkFileSaved(std::string fileName, std::string context);
  TTF_Font *getFont() { return _font; };
  void setCursorDefault() {
    cursonOnCurrentChar = -1;
    cursorOnCurrentLine = 0;
  };
  // colors
  SDL_Color returnBackgroundColor() const { return _backgroundColor; }
  void setBackgroundColor(SDL_Color color) { _backgroundColor = color; }
  SDL_Color returnFontColor() const { return _fontColor; }
  void setFontColor(SDL_Color color) { _fontColor = color; }

  // keyboard, mouse event handling
  void handleCtrlV();
  void handleCtrlZ();
  void handleEventMouse(SDL_Event &e);
  void handleEvents(SDL_Event &e);
  void resetHistory();

private:
  // variables
  SDL_Renderer *_renderer;
  SDL_Rect _textArea;
  TTF_Font *_font;
  EditorWindow _editorWindow;
  std::string *_fontPath;
  std::vector<std::string> _textInput;
  int fontSize;
  int cursorOnCurrentLine;
  int cursonOnCurrentChar;
  int startY;
  int startX;
  bool _cursorVisible;
  std::vector<std::string> selectedText;
  // selection vars
  struct selectionShift {
    int startLine;
    int startChar;
    int endLine;
    int endChar;
  };
  selectionShift selShift;
  selectionShift prevShift;
  selectionShift zeroShift = {0, 0, 0, 0};
  std::string copiedText;

  SDL_Color _fontColor = {0, 0, 0, 255};
  SDL_Color _barColor = {198, 206, 206, 255};
  SDL_Color returnBarColor() const { return _barColor; }
  void setBarColor(SDL_Color color) { _barColor = color; }
  SDL_Color _backgroundColor = {255, 255, 255, 255};
  SDL_Color selectedBackColor;

  void loadFont(const std::string &fontPath, int fontSize);

  // history - variables
  std::vector<int> historyCursor;
  std::vector<int> historyLine;
  std::vector<std::vector<std::string>> historyText;

  // history - methods
  void addHistory();

  // handle keyboard, mouse events
  void handleReturnKey();
  void handleUpKey();
  void handleDownKey();
  void handleRightKey();
  void handleLeftKey();
  void handleBackspaceKey();
  void handleShiftButton();
  void handleCtrlCX(bool isItCtrlX);
  void deleteSelectionShift();
  bool shiftKeyDown;

  // rendering
  void lineNumber();
  void renderBlankSpaces();
  void renderCursor();
  void renderSelecedTextArea();
  void renderTextArea();

  // unused methods
  // void checkVisibleCursor();
  // void changeCursorTimer();
};
#endif // TEXTEDITOR_H
