#include "EditorWindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#pragma once
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

class TextEditor {
public:
  TextEditor(SDL_Renderer *renderer, const EditorWindow &editorWindow);
  ~TextEditor();

  void handleEvents(SDL_Event &e);
  void update();
  void render();

  void loadFont(const std::string &fontPath, int fontSize);
  void setText(const std::string &text);

  void checkVisibleCursor();
  void changeCursorTimer();

  void renderCursor();
  void renderTextArea();

private:
  SDL_Renderer *_renderer;
  SDL_Rect _textArea;
  std::string *_fontPath;
  TTF_Font *_font;
  EditorWindow _editorWindow;
  std::vector<std::string> _textInput;
  int fontSize;
  int cursorOnCurrentLine;
  int cursonOnCurrentChar;

  bool _cursorVisible;
};

#endif // TEXTEDITOR_H
