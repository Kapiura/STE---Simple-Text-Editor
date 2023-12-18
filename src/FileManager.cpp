#include "../include/FileManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <filesystem>
#include <immintrin.h>
#include <string>

FileManager::FileManager (EditorWindow *w, InputEditor *iw,
                          std::filesystem::path path)
    : _file_name ("New_file.txt"), _path (path), _windowSaving (w),
      _savingInput (iw),
      currentCursorPosition (static_cast<int> (_file_name.size ()) - 1)

{
  fontSize = 11;
  std::cout << "FileManager object has been created\n";
  _renderer = _windowSaving->getRenderer ();
  loadFont ("assets/jetbrainsmono/JetBrainsMono-Regular.ttf", fontSize);
  int wD, wH;
  SDL_GetWindowSize (_windowSaving->getWindow (), &wD, &wH);
  currPath = 0;
  startY = 10;
  pathHistory.push_back (_path);
  // Next button
  btnXY.push_back ({ wD - 45, 5 });
  btnWH.push_back ({ 35, 15 });
  btnNames.push_back (">");
  // Prev button
  btnXY.push_back ({ wD - 85, 5 });
  btnWH.push_back ({ 35, 15 });
  btnNames.push_back ("<");
  // Close button
  btnXY.push_back ({ 10, wH - 35 });
  btnWH.push_back ({ 70, 25 });
  btnNames.push_back ("Close");
  // Save button
  btnXY.push_back ({ wD - 85, wH - 35 });
  btnWH.push_back ({ 70, 25 });
  btnNames.push_back ("Save");

  for (int i = 0; i < 4; ++i)
    {
      btnGroup.push_back ({ btnXY[i][0],
                            btnXY[i][1],
                            btnWH[i][0],
                            btnWH[i][1],
                            btnNames[i],
                            { 255, 255, 255, 255 } });
    }
}
FileManager::~FileManager ()
{
  std::cout << "FileManager object has been deleted\n";
  TTF_CloseFont (_font);
}

void
FileManager::loadFont (const std::string &fontPath, int fontSize)
{
  _font = TTF_OpenFont (fontPath.c_str (), fontSize);
  if (!_font)
    {
      std::cout << "SDL TTF error loading font: " << SDL_GetError () << "\n";
      exit (-1);
    }
}
void
FileManager::renderCurrentPath ()
{
  int textWidth, textHeight;
  SDL_Surface *tempSurface = TTF_RenderText_Solid (
      _font, _path.string ().c_str (), { 255, 255, 255, 255 });
  SDL_Texture *tempTexture
      = SDL_CreateTextureFromSurface (_renderer, tempSurface);
  SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect tempRect = { 10, 5, textWidth, textHeight };
  SDL_RenderCopy (_renderer, tempTexture, NULL, &tempRect);
  SDL_DestroyTexture (tempTexture);
  SDL_FreeSurface (tempSurface);
}

void
FileManager::renderFiles ()
{
  int textWidth, textHeight;
  int i = 1;

  for (const auto &entry : std::filesystem::directory_iterator (_path))
    {

      SDL_Color textColor;
      SDL_Color backgroundColor;

      if (IsMouseOverFolderFile (entry, i))
        {
          backgroundColor = { 255, 255, 0, 255 };
        }
      else
        {
          backgroundColor = { 255, 255, 255, 255 };
        }

      if (std::filesystem::is_directory (entry))
        {
          textColor = { 0, 0, 255, 255 };
        }
      else
        {
          textColor = { 0, 0, 0, 255 };
        }

      std::string temp = entry.path ().filename ().string ();
      SDL_Surface *tempSurface
          = TTF_RenderText_Solid (_font, temp.c_str (), textColor);
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurface);
      SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);

      int posY = startY + static_cast<int> (i * 17);
      SDL_Rect tempRect = { 10, posY, textWidth, textHeight };

      SDL_SetRenderDrawColor (_renderer, backgroundColor.r, backgroundColor.g,
                              backgroundColor.b, backgroundColor.a);
      SDL_RenderFillRect (_renderer, &tempRect);

      SDL_RenderCopy (_renderer, tempTexture, NULL, &tempRect);
      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurface);
      ++i;
    }
  maxY = i * 17;
}

void
FileManager::render ()
{
  this->renderFiles ();
  this->renderBlankSpaces ();
  this->renderCurrentPath ();
  for (int i = 0; i < 4; ++i)
    {
      this->btnRender (btnGroup[i]);
    }
  this->renderNewFile ();
  this->renderCursor ();
  SDL_SetRenderDrawColor (_renderer, 255, 255, 255, 255);
  SDL_RenderPresent (_renderer);
  std::cout << "Current Cursor Pos = " << currentCursorPosition << "\n";
}
void
FileManager::renderNewFile ()
{
  int windowWidth, windowHeight;
  SDL_GetWindowSize (_windowSaving->getWindow (), &windowWidth, &windowHeight);

  int textWidth, textHeight;
  SDL_Surface *tempSurface = TTF_RenderText_Solid (_font, _file_name.c_str (),
                                                   { 255, 255, 255, 255 });
  SDL_Texture *tempTexture
      = SDL_CreateTextureFromSurface (_renderer, tempSurface);
  SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect tempRect = { 85, windowHeight - 30, textWidth, textHeight };
  SDL_RenderCopy (_renderer, tempTexture, NULL, &tempRect);
  SDL_DestroyTexture (tempTexture);
  SDL_FreeSurface (tempSurface);
}
void
FileManager::renderBlankSpaces ()
{
  int windowWidth, windowHeight;
  SDL_GetWindowSize (_windowSaving->getWindow (), &windowWidth, &windowHeight);
  SDL_SetRenderDrawColor (_renderer, 80, 80, 80, 255);
  SDL_Rect blankRect{ 0, 0, windowWidth, 25 };
  SDL_RenderDrawRect (_renderer, &blankRect);
  SDL_RenderFillRect (_renderer, &blankRect);

  SDL_SetRenderDrawColor (_renderer, 80, 80, 80, 255);
  SDL_Rect blankRect2{ 0, windowHeight - 40, windowWidth, windowHeight };
  SDL_RenderDrawRect (_renderer, &blankRect2);
  SDL_RenderFillRect (_renderer, &blankRect2);
}
void
FileManager::btnRender (MyButton butt)
{
  int windowWidth, windowHeight;
  SDL_GetWindowSize (_windowSaving->getWindow (), &windowWidth, &windowHeight);

  SDL_SetRenderDrawColor (_renderer, 0, 0, 0, 255);

  SDL_Rect buttonBorder{ butt.btnX, butt.btnY, butt.btnW, butt.btnH };
  SDL_RenderDrawRect (_renderer, &buttonBorder);

  SDL_SetRenderDrawColor (_renderer, butt.buttonColor.r, butt.buttonColor.g,
                          butt.buttonColor.b, butt.buttonColor.a);

  SDL_Rect buttonFillRect{ butt.btnX + 1, butt.btnY + 1, butt.btnW - 2,
                           butt.btnH - 2 };
  SDL_RenderFillRect (_renderer, &buttonFillRect);

  SDL_Surface *textSurface
      = TTF_RenderText_Solid (_font, butt.name.c_str (), { 0, 0, 0, 255 });
  SDL_Texture *textTexture
      = SDL_CreateTextureFromSurface (_renderer, textSurface);

  int textX = butt.btnX + (butt.btnW - textSurface->w) / 2;
  int textY = butt.btnY + (butt.btnH - textSurface->h) / 2;

  SDL_Rect textRect = { textX, textY, textSurface->w, textSurface->h };
  SDL_RenderCopy (_renderer, textTexture, NULL, &textRect);

  SDL_DestroyTexture (textTexture);
  SDL_FreeSurface (textSurface);
}
bool
FileManager::IsMouseOver (int mouseX, int mouseY, MyButton btn) const
{
  return mouseX >= btn.btnX && mouseX <= btn.btnX + btn.btnW
         && mouseY >= btn.btnY && mouseY <= btn.btnY + btn.btnH;
}

void
FileManager::changeButtonColor (MyButton &btn, SDL_Color col)
{
  btn.buttonColor = col;
}
void
FileManager::handleEventMouse (SDL_Event &e, bool &q)
{
  if (e.type == SDL_MOUSEMOTION)
    {
      int mouseX = e.motion.x;
      int mouseY = e.motion.y;

      for (int i = 0; i < 4; ++i)
        {

          if (IsMouseOver (mouseX, mouseY, btnGroup[i]))
            {
              changeButtonColor (btnGroup[i], { 255, 255, 0, 255 });
            }
          else
            {

              changeButtonColor (btnGroup[i], { 255, 255, 255, 255 });
            }
        }
    }
  else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      int mouseX = e.button.x;
      int mouseY = e.button.y;

      for (int i = 0; i < 4; ++i)
        {
          if (IsMouseOver (mouseX, mouseY, btnGroup[i]))
            {
              handleButtonClick (btnGroup[i], q);
            }
        }
      int i = 1;
      for (const auto &entry : std::filesystem::directory_iterator (_path))
        {
          if (IsMouseOverFolderFile (entry, i))
            {
              if (std::filesystem::is_directory (entry))
                {
                  std::string tempPath = _path.string ();
                  std::string tempEntry = entry.path ().filename ().string ();
                  tempPath = tempPath + "/" + tempEntry;
                  _path = tempPath;
                  startY = 10;
                  break;
                }
              else
                {
                  {
                    _file_name = entry.path ().filename ();
                    break;
                  }
                }
            }
          ++i;
        }
    }

  else if (e.type == SDL_MOUSEWHEEL)
    {
      int count = std::distance (std::filesystem::directory_iterator (_path),
                                 std::filesystem::directory_iterator{});
      int scrollY = e.wheel.y;

      if (scrollY < 0 && startY < 10)
        {
          std::cout << "Scroll down" << std::endl;
          startY += 17;
        }
      else if (scrollY > 0 && count > 11 && 10 - (count - 11) * 17 < startY)
        {
          std::cout << "Scroll Up" << std::endl;
          startY -= 17;
        }
      std::cout << "StartY = " << startY << "\n";
      std::cout << "Count = " << count << "\n";
    }
}
void
FileManager::handleButtonClick (const MyButton &btn, bool &q)
{
  // next
  if (btn.name == ">")
    {
      if (currPath > 0)
        {
          currPath -= 1;
          startY = 10;
        }
      _path = pathHistory[currPath];
    }
  else if (btn.name == "<")
    // prev
    {
      std::filesystem::path temppatj = _path;
      _path = _path.parent_path ();
      if (_path != temppatj)
        {
          pathHistory.push_back (_path);
          currPath += 1;
          startY = 10;
        }
    }
  else if (btn.name == "Close")
    {
      q = true;
    }
  else if (btn.name == "Save")
    {
      SaveManager savingProc (_file_name, _savingInput->getTextContent (),
                              _path);
      savingProc.saveFile (q, _windowSaving->getWindow ());
      _windowSaving->changeNewFileName (_file_name);
    }
}

bool
FileManager::IsMouseOverFolderFile (
    const std::filesystem::directory_entry &entry, int index) const
{
  int mouseX, mouseY;
  SDL_GetMouseState (&mouseX, &mouseY);

  int posY = startY + static_cast<int> (index * 17);

  std::string temp = entry.path ().filename ().string ();
  int textWidth, textHeight;
  TTF_SizeText (_font, temp.c_str (), &textWidth, &textHeight);

  return mouseX >= 10 && mouseX <= 10 + textWidth && mouseY >= posY
         && mouseY <= posY + textHeight;
}

void
FileManager::handleEventKeyboard (SDL_Event &e, bool &q)
{
  if (e.type == SDL_QUIT)
    {
      q = true;
    }
  if (e.type == SDL_KEYDOWN)
    {

      switch (e.key.keysym.sym)
        {
          // right
        case SDLK_RIGHT:
          handleRight ();
          break;
          // left
        case SDLK_LEFT:
          handleLeft ();
          break;
          // backspace
        case SDLK_BACKSPACE:
          handleBackspace ();
          break;
          // defualt
        default:
          handleKeyboard ();
          break;
        }
    }
}
//
// void
// FileManager::handleRight ()
// {
//   currentCursorPosition += 1;
//   std::cout << "=>\n";
// }
//
// void
// FileManager::handleLeft ()
// {
//   currentCursorPosition -= 1;
//   std::cout << "<=\n";
// }
//
// void
// FileManager::handleBackspace ()
// {
//   _file_name.erase (currentCursorPosition, 1);
//   std::cout << "backspace\n";
// }
//
void
FileManager::handleKeyboard ()
{
  _file_name.append (currentCursorPosition, 1);
  std::cout << "Key\n";
}

void
FileManager::renderCursor ()
{
  int textWidth, textHeight;
  int windowHeight, windowWidth;
  SDL_GetWindowSize (_windowSaving->getWindow (), &windowWidth, &windowHeight);
  SDL_Surface *indexSurface
      = TTF_RenderText_Solid (_font, "|", { 255, 255, 255, 255 });
  SDL_Texture *indexTexture
      = SDL_CreateTextureFromSurface (_renderer, indexSurface);
  SDL_QueryTexture (indexTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect tempRect = { 85 + (currentCursorPosition * 7), windowHeight - 30,
                        textWidth, textHeight };
  SDL_RenderCopy (_renderer, indexTexture, NULL, &tempRect);
  SDL_DestroyTexture (indexTexture);
  SDL_FreeSurface (indexSurface);
}

void
FileManager::handleRight ()
{
  if (currentCursorPosition < static_cast<int> (_file_name.size ()) - 1)
    {
      currentCursorPosition += 1;
    }
}

void
FileManager::handleLeft ()
{
  if (currentCursorPosition >= 0)
    {
      currentCursorPosition -= 1;
    }
}

void
FileManager::handleBackspace ()
{
  if (!_file_name.empty ())
    {
      if (currentCursorPosition > -1)
        {
          _file_name.erase (currentCursorPosition, 1);
          currentCursorPosition -= 1;
        }
    }
  else if (_file_name.empty () && currentCursorPosition > 0)
    {
      _file_name.erase (_file_name.begin () + currentCursorPosition);
      currentCursorPosition -= 1;
      currentCursorPosition = static_cast<int> (_file_name.size () - 1);
    }
}
