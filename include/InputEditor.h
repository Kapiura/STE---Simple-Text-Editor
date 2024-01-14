#pragma once
#include "EditorWindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
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
  void setCursorDefaulr() {
    cursonOnCurrentChar = -1;
    cursorOnCurrentLine = 0;
  };
  void handleCtrlV();
  void handleCtrlZ();
  void handleEventMouse(SDL_Event &e);

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
};

#endif // TEXTEDITOR_H
