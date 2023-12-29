#pragma once
#include "EditorWindow.h"
#include "FileManager.h"
#include "InputEditor.h"
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

  struct selectOption {
    std::string name;
    int x;
    int y;
    int w;
    int h;
    SDL_Color clr;
  };
  std::vector<selectOption> selOps;
  std::vector<selectOption> selFile;
  std::vector<selectOption> selEdit;
  std::vector<selectOption> selOptions;
  int startY;
  int maxY;
  int startMaxY;

  InputEditor *_savingInput;
  FileManager *_filemanager;
  EditorWindow *_savingWindow;

  void PopBackWindow(int &btn, std::string title, std::string message,
                     std::string yes, std::string no);

public:
  bool isMouseOver(int mouseX, int mouseY, selectOption btn) const;
  void handleEventMouse(SDL_Event &e, bool &q);
  void changeButtonColor(selectOption &btn, SDL_Color col) { btn.clr = col; }
  void handleButtonClick(const selectOption &btn);
  void renderOpsOption(std::vector<selectOption> &vecOps);
  void handleCloseClickInFile(bool &q, selectOption &el);
};

#endif // MENUBAR_H
