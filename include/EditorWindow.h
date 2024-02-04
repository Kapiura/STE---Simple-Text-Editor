#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <filesystem>
#include <string>
#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

class EditorWindow {
public:
  // init
  EditorWindow(std::string title, int height, int width);
  EditorWindow(std::string t, int h, int w, TTF_Font *font);
  ~EditorWindow();

  // returns
  SDL_Renderer *getRenderer() const;
  SDL_Window *getWindow() const;
  // TTF_Font *getFont() const { return _font; };
  int getWindowHeight() const;
  int getWindowWidth() const;
  std::string getFileName() const { return _file_name; }
  std::filesystem::path getPath() const { return _path; }

  // update, render
  void changeNewFileName(std::string newFileName) { _file_name = newFileName; }
  void setPath(std::filesystem::path p) { _path = p; }
  void update();
  void render();

private:
  // variables
  std::string _title;
  std::string _file_name;
  int _height;
  int _width;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  TTF_Font *_font;
  std::filesystem::path _path;
};

#endif // EDITORWINDOW_H
