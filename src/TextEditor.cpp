#include "../include/TextEditor.h"
#include "../include/EditorWindow.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <iostream>

TextEditor::TextEditor (SDL_Renderer *renderer,
                        const EditorWindow &editorWindow)
    : _renderer (renderer), _font (nullptr), _editorWindow (editorWindow),
      fontSize (24), cursorOnCurrentLine (0), cursonOnCurrentChar (0),
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

TextEditor::~TextEditor ()
{
  std::cout << "TextEditor object has been destroyed\n";
  TTF_CloseFont (_font);
}

void
TextEditor::loadFont (const std::string &fontPath, int fontSize)
{
  _font = TTF_OpenFont (fontPath.c_str (), fontSize);
  if (!_font)
    {
      std::cout << "SDL TTF error loading font: " << SDL_GetError () << "\n";
      exit (-1);
    }
}

void
TextEditor::renderCursor ()
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
TextEditor::renderTextArea ()
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
TextEditor::render ()
{
  SDL_SetRenderDrawColor (_renderer, 255, 255, 255, 255);
  this->renderTextArea ();
  this->renderCursor ();
  SDL_RenderPresent (_renderer);
  SDL_Delay (0);
}

void
TextEditor::handleEvents (SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
        {
        case SDLK_RETURN:
          cursorOnCurrentLine += 1;
          cursonOnCurrentChar = 0;
          _textInput.push_back ("");
          break;
        case SDLK_UP:
          if (cursorOnCurrentLine > 0)
            {
              cursorOnCurrentLine -= 1;
            }
          break;
        case SDLK_DOWN:
          if (static_cast<int> (_textInput.size ()) < cursorOnCurrentLine)
            {
              cursorOnCurrentLine += 1;
            }
          break;
        case SDLK_RIGHT:
          if (static_cast<int> (_textInput[cursorOnCurrentLine].length ())
              < cursonOnCurrentChar)
            {
              cursonOnCurrentChar += 1;
            }
          break;
        case SDLK_LEFT:
          if (cursonOnCurrentChar > 0)
            {
              cursonOnCurrentChar -= 1;
            }
          break;
        case SDLK_BACKSPACE:
          if (!_textInput[cursorOnCurrentLine].empty ())
            {
              if (cursonOnCurrentChar > 0)
                {
                  _textInput[cursorOnCurrentLine].erase (cursonOnCurrentChar,
                                                         1);
                  cursonOnCurrentChar -= 1;
                }
            }
          break;
        default:
          char pressedChar = static_cast<char> (e.key.keysym.sym);
          _textInput[cursorOnCurrentLine] += pressedChar;
          cursonOnCurrentChar += 1;

          break;
        }
    }
  // if (e.type == SDL_KEYDOWN)
  //   {
  //     else if (e.key.keysym.sym == SDLK_BACKSPACE)
  //       {
  //         if (!_textInput.empty ())
  //           {
  //             if (!_textInput[cursorOnCurrentLine].empty ())
  //               _textInput[cursorOnCurrentLine].erase (cursonOnCurrentChar,
  //               1);
  //             // _textInput[cursorOnCurrentLine].pop_back ();
  //             if (cursonOnCurrentChar > 0)
  //               cursonOnCurrentChar -= 1;
  //           }
  //       }
  //   else
  //     {
  //       char pressedChar = static_cast<char> (e.key.keysym.sym);
  //       _textInput[cursorOnCurrentLine] += pressedChar;
  //       cursonOnCurrentChar += 1;
  //     }
  // }
}

void
TextEditor::update ()
{
  // this->changeCursorTimer ();
  // this->checkVisibleCursor();

  int textLenght = _textInput[cursorOnCurrentLine].length ();
  int textAreaWidth = _textArea.w;

  if (textLenght * fontSize > textAreaWidth)
    {
      _textInput.push_back ("");
    }
  std::cout << "cursor: " << cursonOnCurrentChar << "\n";
  std::cout << "------------------------------------------------\n";
  for (auto &line : _textInput)
    {
      std::cout << "\"" << line << "\""
                << "\n";
    }
}

// void
// TextEditor::checkVisibleCursor ()
// {
//   if (_cursorTimer % 5 == 0)
//     {
//       _cursorVisible = !_cursorVisible;
//     }
// }
