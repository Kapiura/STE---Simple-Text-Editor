#include "../include/TextEditor.h"
#include "../include/EditorWindow.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

TextEditor::TextEditor (SDL_Renderer *renderer,
                        const EditorWindow &editorWindow)
    : _renderer (renderer), _font (nullptr), _editorWindow (editorWindow)
{
  std::cout << "TextEditor object has been created\n";
  _textArea.h = editorWindow.getWindowHeight ();
  _textArea.w = editorWindow.getWindowWidth ();
  _textArea.x = 0;
  _textArea.y = 0;

  loadFont ("assets/jetbrainsmono/JetBrainsMono-Regular.ttf", 24);
  _textInput = "";
}

TextEditor::~TextEditor ()
{
  std::cout << "TextEditor object has been destroyed\n";
  TTF_CloseFont (_font);
}

void
TextEditor::loadFont (const std::string &fontPath, int fontSize)
{
  // Lodaing default font
  _font = TTF_OpenFont (fontPath.c_str (), fontSize);
  // Check if font is valid
  if (!_font)
    {
      std::cout << "SDL TTF error loading font: " << SDL_GetError () << "\n";
      exit (-1);
    }
}

void
TextEditor::render ()
{
  SDL_SetRenderDrawColor (_renderer, 255, 255, 255, 255);
  // Render the Text
  SDL_Surface *textSurface
      = TTF_RenderText_Solid (_font, _textInput.c_str (), { 0, 0, 0, 0 });
  SDL_Texture *textTexture
      = SDL_CreateTextureFromSurface (_renderer, textSurface);

  int textWidth, textHeight;
  SDL_QueryTexture (textTexture, NULL, NULL, &textWidth, &textHeight);

  // Set the position to render the text
  SDL_Rect textRect;
  textRect.x = 0; // Adjust the x-coordinate as needed
  textRect.y = 0; // Adjust the y-coordinate as needed
  textRect.w = textWidth;
  textRect.h = textHeight;

  // Render the texture
  SDL_RenderCopy (_renderer, textTexture, NULL, &textRect);

  if (_cursorVisible)
    {
      int cursorX = _textArea.x + 24 * static_cast<int> (_textInput.length ());
      int cursorY = _textArea.y + (_textArea.h - TTF_FontHeight (_font)) / 2;

      SDL_RenderDrawLine (_renderer, cursorX, cursorY, cursorX,
                          cursorY + TTF_FontHeight (_font));
    }

  SDL_DestroyTexture (textTexture);

  SDL_FreeSurface (textSurface);

  SDL_RenderPresent (_renderer);
}

void
TextEditor::handleEvents (SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN)
    {
      if (e.key.keysym.sym == SDLK_RETURN)
        {
        }
      else if (e.key.keysym.sym == SDLK_BACKSPACE)
        {
          if (!_textInput.empty ())
            {
              _textInput.pop_back ();
            }
        }
      else
        {
          char pressedChar = static_cast<char> (e.key.keysym.sym);
          _textInput += pressedChar;
        }
    }
}

void
TextEditor::update ()
{
  _cursorTimer += 1;

  if (_cursorTimer % 25 == 0)
    {
      _cursorVisible = !_cursorVisible;
    }
}
