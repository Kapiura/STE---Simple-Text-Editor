#pragma once
#include "EditorWindow.h"
#include "FileManager.h"
#include "InputEditor.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <iterator>
#include <vector>
#ifndef MENUBAR_H
#define MENUBAR_H

class MenuBar {
public:
  MenuBar(EditorWindow *w, InputEditor *ie);
  ~MenuBar();

  void render();
  void update();
  void lineRender(int const &windowWidth);
  void textsRender();
  bool isMouseOverSelect();

private:
  EditorWindow *_windowEditor;
  InputEditor *_inputEditor;
  SDL_Renderer *_renderer;
  TTF_Font *_font;

  InputEditor *_savingInput;
  FileManager *_filemanager;
  EditorWindow *_savingWindow;

  struct selectOption {
    std::string name;
    int x;
    int y;
    int w;
    int h;
    SDL_Color clr;
    bool visible;
    SDL_Rect rect;
  };
  std::vector<selectOption> selOps;
  std::vector<selectOption> selFile;
  std::vector<selectOption> selEdit;
  std::vector<selectOption> selOptions;
  int startY;
  int maxY;
  int startMaxY;

  bool fileOps = false;
  bool editOps = false;
  bool opsOps = false;
  void PopBackWindow(int &btn, std::string title, std::string message,
                     std::string yes, std::string no);
  void PopBackWindow(int &btn, std::string title, std::string message,
                     std::string yes);

public:
  bool isMouseOver(int mouseX, int mouseY, selectOption btn) const;
  void handleEventMouse(SDL_Event &e, bool &q);
  void changeButtonColor(selectOption &btn, SDL_Color col) { btn.clr = col; }
  void handleButtonClick(const selectOption &btn);
  void renderOpsOption(std::vector<selectOption> &vecOps);
  void handleCloseClickInFile(bool &q, selectOption &el);
  void handleMouseMotion(SDL_Event &e);

  SDL_Color _fontColor = {0, 0, 0, 255};
  SDL_Color returnFontColor() const { return _fontColor; }
  void setFontColor(SDL_Color color) { _fontColor = color; }

  SDL_Color _barColor = {198, 206, 206, 255};
  SDL_Color returnBarColor() const { return _barColor; }
  void setBarColor(SDL_Color color) { _barColor = color; }
};

#endif // MENUBAR_H
