#include "../include/InputEditor.h"
#include "../include/EditorWindow.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <iostream>

InputEditor::InputEditor (SDL_Renderer *renderer,
                          const EditorWindow &editorWindow)
    : _renderer (renderer), _font (nullptr), _editorWindow (editorWindow),
      fontSize (24), cursorOnCurrentLine (0), cursonOnCurrentChar (-1),
      _cursorVisible (true)
{
  std::cout << "TextEditor object has been created\n";
  _textArea.h = editorWindow.getWindowHeight ();
  _textArea.w = editorWindow.getWindowWidth ();
  _textArea.x = 0;
  _textArea.y = 0;

  loadFont ("assets/jetbrainsmono/JetBrainsMono-Regular.ttf", fontSize);

  _textInput.push_back ("");
  for (auto &line : _textInput)
    {
      line = "";
    }
}

InputEditor::~InputEditor ()
{
  TTF_CloseFont (_font);
  std::cout << "TextEditor object has been destroyed\n";
}

void
InputEditor::loadFont (const std::string &fontPath, int fontSize)
{
  _font = TTF_OpenFont (fontPath.c_str (), fontSize);
  if (!_font)
    {
      std::cout << "SDL TTF error loading font: " << SDL_GetError () << "\n";
      exit (-1);
    }
  for (auto &line : _textInput)
    {
      line = "";
    }
}

void
InputEditor::renderCursor ()
{
  int textWidth, textHeight;
  if (_cursorVisible)
    {
      SDL_Surface *indexSurface
          = TTF_RenderText_Solid (_font, "|", { 0, 0, 0, 0 });
      SDL_Texture *indexTexture
          = SDL_CreateTextureFromSurface (_renderer, indexSurface);
      SDL_QueryTexture (indexTexture, NULL, NULL, &textWidth, &textHeight);
      SDL_Rect indexRect = { (cursonOnCurrentChar * 14) + 7,
                             cursorOnCurrentLine * 32, textWidth, textHeight };
      SDL_RenderCopy (_renderer, indexTexture, NULL, &indexRect);
      SDL_DestroyTexture (indexTexture);
      SDL_FreeSurface (indexSurface);
    }
}

void
InputEditor::renderTextArea ()
{
  int textWidth, textHeight;
  for (size_t i = 0; i < _textInput.size (); ++i)
    {
      SDL_Surface *tempSurface = TTF_RenderText_Solid (
          _font, _textInput[i].c_str (), { 0, 0, 0, 0 });
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurface);
      SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);
      SDL_Rect tempRect
          = { 0, static_cast<int> (i * 32), textWidth, textHeight };
      SDL_RenderCopy (_renderer, tempTexture, NULL, &tempRect);
      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurface);
    }
}

void
InputEditor::render ()
{
  SDL_SetRenderDrawColor (_renderer, 255, 255, 255, 255);
  this->renderTextArea ();
  this->renderCursor ();
  SDL_RenderPresent (_renderer);
}

void
InputEditor::handleEvents (SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
        {
        case SDLK_RETURN:
          handleReturnKey ();
          break;
        case SDLK_UP:
          handleUpKey ();
          break;
        case SDLK_DOWN:
          handleDownKey ();
          break;
        case SDLK_RIGHT:
          handleRightKey ();
          break;
        case SDLK_LEFT:
          handleLeftKey ();
          break;
        case SDLK_BACKSPACE:
          handleBackspaceKey ();
          break;
        case SDLK_v:
          if (SDL_GetModState () & KMOD_CTRL)
            {
              handleCtrlV ();
            }
          else
            {
              char pressedChar = static_cast<char> (e.key.keysym.sym);
              _textInput[cursorOnCurrentLine] += pressedChar;
              cursonOnCurrentChar += 1;
            }
          break;
        default:
          if ((e.key.keysym.sym >= SDLK_SPACE && e.key.keysym.sym <= SDLK_z))
            {
              char pressedChar = static_cast<char> (e.key.keysym.sym);
              _textInput[cursorOnCurrentLine] += pressedChar;
              cursonOnCurrentChar += 1;
            }
          break;
        }
    }
}

void
InputEditor::update ()
{

  std::cout << "------------------------------------------------\n";
  std::cout << "cursor: " << cursonOnCurrentChar << "\n";
  std::cout << "line: " << cursorOnCurrentLine << "\n";
  for (auto &line : _textInput)
    {
      std::cout << "\"" << line << "\""
                << "\n";
    }
  std::cout << "------------------------------------------------\n";
}

std::string
InputEditor::getTextContent ()
{
  std::string result;
  for (auto it = _textInput.begin (); it != _textInput.end (); ++it)
    {
      std::string temp = *it;
      if (it != std::prev (_textInput.end ()))
        {
          result += *it + "\n";
        }
      else
        {
          result += *it;
        }
    }
  return result;
}

void
InputEditor::handleReturnKey ()
{
  cursorOnCurrentLine += 1;
  cursonOnCurrentChar = -1;
  _textInput.push_back ("");
}

void
InputEditor::handleUpKey ()
{
  if (cursorOnCurrentLine > 0)
    {
      cursorOnCurrentLine -= 1;
    }
}

void
InputEditor::handleDownKey ()
{
  if (cursorOnCurrentLine < static_cast<int> (_textInput.size ()) - 1)
    {
      cursorOnCurrentLine += 1;
    }
}

void
InputEditor::handleRightKey ()
{
  if (cursonOnCurrentChar
      < static_cast<int> (_textInput[cursorOnCurrentLine].size ()) - 1)
    {
      cursonOnCurrentChar += 1;
    }
}

void
InputEditor::handleLeftKey ()
{
  if (cursonOnCurrentChar >= 0)
    {
      cursonOnCurrentChar -= 1;
    }
}

void
InputEditor::handleBackspaceKey ()
{
  if (!_textInput[cursorOnCurrentLine].empty ())
    {
      if (cursonOnCurrentChar > -1)
        {
          _textInput[cursorOnCurrentLine].erase (cursonOnCurrentChar, 1);
          cursonOnCurrentChar -= 1;
        }
    }
  else if (_textInput[cursorOnCurrentLine].empty () && cursorOnCurrentLine > 0)
    {
      _textInput.erase (_textInput.begin () + cursorOnCurrentLine);
      cursorOnCurrentLine -= 1;
      cursonOnCurrentChar
          = static_cast<int> (_textInput[cursorOnCurrentLine].size () - 1);
    }
}

void
InputEditor::handleCtrlV ()
{
  const char *clipboardText = SDL_GetClipboardText ();
  if (clipboardText != nullptr)
    {
      _textInput[cursorOnCurrentLine].insert (cursonOnCurrentChar + 1,
                                              clipboardText);
      cursonOnCurrentChar += strlen (clipboardText);
      SDL_free (const_cast<char *> (clipboardText));
    }
  std::cout << "CTRL+V has been pressed\n";
}