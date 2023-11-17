#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <string>
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class FileManager {
public:
  FileManager(std::string title, std::string name, int width, int height);
  ~FileManager();

private:
  std::string _pop_up_window_title;
  std::string _file_name;
  int _width;
  int _height;
  TTF_Font *_font;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
};

#endif // FILEMANAGER_H
