#pragma once
#include "CustomizationApp.h"
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
  void handleEventMouse(SDL_Event &e, bool &q);

private:
  // variables
  EditorWindow *_windowEditor;
  InputEditor *_inputEditor;
  SDL_Renderer *_renderer;
  TTF_Font *_font;

  InputEditor *_savingInput;
  FileManager *_filemanager;
  EditorWindow *_savingWindow;

  EditorWindow *_customWindow;
  CustomizationApp *_custom;

  // menu bar selection options
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

  // variables for scrolling
  int startY;
  int maxY;
  int startMaxY;

  // vairables - displaying options
  bool fileOps = false;
  bool editOps = false;
  bool opsOps = false;
  // pop back window
  void PopBackWindow(int &btn, std::string title, std::string message,
                     std::string yes, std::string no);
  void PopBackWindow(int &btn, std::string title, std::string message,
                     std::string yes);

  // handle mouse events
  bool isMouseOver(int mouseX, int mouseY, selectOption btn) const;
  void changeButtonColor(selectOption &btn, SDL_Color col) { btn.clr = col; }
  void handleButtonClick(const selectOption &btn);
  void renderOpsOption(std::vector<selectOption> &vecOps);
  void handleCloseClickInFile(bool &q, selectOption &el);
  void handleMouseMotion(SDL_Event &e);

  // font color
  SDL_Color _fontColor = {0, 0, 0, 255};
  SDL_Color returnFontColor() const { return _fontColor; }
  void setFontColor(SDL_Color color) { _fontColor = color; }
  // menu bar color
  SDL_Color _barColor = {198, 206, 206, 255};
  SDL_Color returnBarColor() const { return _barColor; }
  void setBarColor(SDL_Color color) { _barColor = color; }
};

#endif // MENUBAR_H
