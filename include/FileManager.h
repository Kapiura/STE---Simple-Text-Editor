#pragma once
#include "EditorWindow.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#ifndef FILEMANAGER_H
#define FILEMANAGER

class FileManager {
public:
  FileManager(EditorWindow *w) : _windowSaving(w) {
    _path = std::filesystem::current_path();
    fontSize = 11;
    std::cout << "FileManager object has been created\n";
    _renderer = _windowSaving->getRenderer();
    loadFont("assets/jetbrainsmono/JetBrainsMono-Regular.ttf", fontSize);
  }
  ~FileManager() {
    std::cout << "FileManager object has been deleted\n";
    TTF_CloseFont(_font);
  }

  void loadFont(const std::string &fontPath, int fontSize) {
    _font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!_font) {
      std::cout << "SDL TTF error loading font: " << SDL_GetError() << "\n";
      exit(-1);
    }
  }
  void renderCurrentPath() {
    int textWidth, textHeight;
    // std::cout << _path.string().c_str() << "\n";

    SDL_Surface *tempSurface =
        TTF_RenderText_Solid(_font, _path.string().c_str(), {0, 0, 0, 0});
    SDL_Texture *tempTexture =
        SDL_CreateTextureFromSurface(_renderer, tempSurface);
    SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect tempRect = {0, static_cast<int>(0 * 32), textWidth, textHeight};
    SDL_RenderCopy(_renderer, tempTexture, NULL, &tempRect);
    SDL_DestroyTexture(tempTexture);
    SDL_FreeSurface(tempSurface);
  }
  void renderFiles() {
    int textWidth, textHeight;
    int i = 1;

    for (const auto &entry : std::filesystem::directory_iterator(_path)) {
      SDL_Color textColor;
      if (std::filesystem::is_directory(entry)) {
        textColor = {0, 0, 255, 255}; // Blue color for directories
      } else {
        textColor = {0, 0, 0, 255}; // Black color for regular files
      }
      std::string temp = entry.path().filename().string();
      SDL_Surface *tempSurface =
          TTF_RenderText_Solid(_font, temp.c_str(), textColor);
      SDL_Texture *tempTexture =
          SDL_CreateTextureFromSurface(_renderer, tempSurface);
      SDL_QueryTexture(tempTexture, NULL, NULL, &textWidth, &textHeight);
      SDL_Rect tempRect = {0, static_cast<int>(i * 16), textWidth, textHeight};
      SDL_RenderCopy(_renderer, tempTexture, NULL, &tempRect);
      SDL_DestroyTexture(tempTexture);
      SDL_FreeSurface(tempSurface);
      ++i;
    }
  };
  void render() {
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    this->renderCurrentPath();
    this->renderFiles();
    SDL_RenderPresent(_renderer);
  }
  // void handleEvents(SDL_Event &e) {
  //   // int mouseX, mouseY;
  //   // // bool isMouseOverFile = false;
  //   // if (e.type == SDL_MOUSEMOTION) {
  //   //   // Update mouse coordinates
  //   //   mouseX = e.motion.x;
  //   //   mouseY = e.motion.y;
  //
  //     // SDL_Rect firstFileRect = {10, 10, 200, 20};
  //     // isMouseOverFile = (mouseX >= firstFileRect.x &&
  //     //                    mouseX <= (firstFileRect.x + firstFileRect.w) &&
  //     //                    mouseY >= firstFileRect.y &&
  //     //                    mouseY <= (firstFileRect.y + firstFileRect.h));
  //   }
  // }

private:
  std::string _file_name;
  int fontSize;
  std::filesystem::path _path;
  EditorWindow *_windowSaving;
  SDL_Renderer *_renderer;
  TTF_Font *_font;
  struct dirent *entry;
  DIR *dir;
};

#endif // !FILEMANAGER_H
