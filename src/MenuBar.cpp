#include "../include/MenuBar.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <immintrin.h>
#include <iostream>

MenuBar::MenuBar (EditorWindow *w, InputEditor *ie)
    : _windowEditor (w), _inputEditor (ie),
      _renderer (_windowEditor->getRenderer ())
{
  int tempx = 1;
  // SDL_Color backgroundcolor = { 255, 255, 255, 255 };
  // main options
  std::vector<std::string> tempStr = { "File", "Edit", "Options" };
  for (auto &el : tempStr)
    {
      int textWidth, textHeight;
      std::string tempStr = el;
      SDL_Surface *tempSurf = TTF_RenderText_Solid (
          _inputEditor->getFont (), tempStr.c_str (), { 0, 0, 0, 255 });
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurf);
      SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);
      SDL_Color col = { 0, 0, 0, 0 };
      selOps.push_back ({ el, tempx, 0, textWidth, textHeight, col });
      tempx += textWidth + 10;

      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurf);
    }
  // File - New Open Save Save as Close
  int tempy = selOps[0].h;
  tempx = selOps[0].x;
  tempStr = { "New", "Open", "Save", "Save as", "Close" };
  for (auto &el : tempStr)
    {
      int textWidth, textHeight;
      std::string tempStr = el;
      SDL_Surface *tempSurf = TTF_RenderText_Solid (
          _inputEditor->getFont (), tempStr.c_str (), { 0, 0, 0, 255 });
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurf);
      SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);
      SDL_Color col = { 255, 255, 255, 0 };
      selFile.push_back ({ el, tempx, tempy, textWidth, textHeight, col });
      tempy += textHeight + 2;

      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurf);
    }
  // Edit Undo Paste
  tempy = selOps[1].h;
  tempx = selOps[1].x;
  tempStr = { "Undo", "Paste" };

  for (auto &el : tempStr)
    {
      int textWidth, textHeight;
      std::string tempStr = el;
      SDL_Surface *tempSurf = TTF_RenderText_Solid (
          _inputEditor->getFont (), tempStr.c_str (), { 0, 0, 0, 255 });
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurf);
      SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);
      SDL_Color col = { 255, 255, 255, 0 };
      selEdit.push_back ({ el, tempx, tempy, textWidth, textHeight, col });
      tempy += textHeight + 2;

      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurf);
    }

  tempy = selOps[2].h;
  tempx = selOps[2].x;
  tempStr = { "Customize", "Credits" };

  for (auto &el : tempStr)
    {
      int textWidth, textHeight;
      std::string tempStr = el;
      SDL_Surface *tempSurf = TTF_RenderText_Solid (
          _inputEditor->getFont (), tempStr.c_str (), { 0, 0, 0, 255 });
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurf);
      SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);
      SDL_Color col = { 255, 255, 255, 0 };
      selOptions.push_back ({ el, tempx, tempy, textWidth, textHeight, col });
      tempy += textHeight + 2;

      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurf);
    }
  std::cout << "MenuBar object has been created\n";
}

MenuBar::~MenuBar () { std::cout << "MenuBar object has been destroyed\n"; }

void
MenuBar::render ()
{
  int windowHeight, windowWidth;
  SDL_GetWindowSize (_windowEditor->getWindow (), &windowWidth, &windowHeight);
  this->lineRender (windowWidth);
  this->textsRender ();
}

void
MenuBar::lineRender (int const &windowWidth)
{
  SDL_SetRenderDrawColor (_renderer, 198, 206, 206, 255);
  SDL_Rect blankRect{ 0, 0, windowWidth, 32 };
  SDL_RenderDrawRect (_renderer, &blankRect);
  SDL_RenderFillRect (_renderer, &blankRect);
}

void
MenuBar::textsRender ()
{
  for (auto &el : selOps)
    {
      int mouseX, mouseY;
      SDL_Rect tempRect;
      SDL_GetMouseState (&mouseX, &mouseY);

      SDL_SetRenderDrawColor (_renderer, el.clr.r, el.clr.g, el.clr.b,
                              el.clr.a);
      SDL_Rect blankRect{ el.x, el.y, el.w, el.h };
      SDL_RenderDrawRect (_renderer, &blankRect);
      SDL_RenderFillRect (_renderer, &blankRect);
      SDL_Surface *tempSurf = TTF_RenderText_Solid (
          _inputEditor->getFont (), el.name.c_str (), { 0, 0, 0, 255 });
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurf);
      tempRect = { el.x, el.y, el.w, el.h };
      SDL_RenderCopy (_renderer, tempTexture, NULL, &tempRect);
      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurf);
    }
}

void
MenuBar::renderOpsOption (std::vector<selectOption> &vecOps)
{
  for (auto &el : vecOps)
    {
      int mouseX, mouseY;
      SDL_Rect tempRect;
      SDL_GetMouseState (&mouseX, &mouseY);

      SDL_SetRenderDrawColor (_renderer, el.clr.r, el.clr.g, el.clr.b,
                              el.clr.a);
      SDL_Rect blankRect{ el.x, el.y, el.w, el.h };
      SDL_RenderDrawRect (_renderer, &blankRect);
      SDL_RenderFillRect (_renderer, &blankRect);
      SDL_Surface *tempSurf = TTF_RenderText_Solid (
          _inputEditor->getFont (), el.name.c_str (), { 0, 0, 0, 255 });
      SDL_Texture *tempTexture
          = SDL_CreateTextureFromSurface (_renderer, tempSurf);
      tempRect = { el.x, el.y, el.w, el.h };
      SDL_RenderCopy (_renderer, tempTexture, NULL, &tempRect);
      SDL_DestroyTexture (tempTexture);
      SDL_FreeSurface (tempSurf);
    }
}

bool
MenuBar::isMouseOver (int mouseX, int mouseY, selectOption btn) const
{
  return mouseX >= btn.x && mouseX <= btn.x + btn.w && mouseY >= btn.y
         && mouseY <= btn.y + btn.h;
}

void
MenuBar::handleEventMouse (SDL_Event &e, bool &q)
{
  // Reset colors for all options
  for (auto &el : selFile)
    el.clr = { 198, 206, 206, 255 };
  for (auto &el : selEdit)
    el.clr = { 198, 206, 206, 255 };
  for (auto &el : selOptions)
    el.clr = { 198, 206, 206, 255 };

  if (e.type == SDL_MOUSEMOTION)
    {
      int mouseX = e.motion.x;
      int mouseY = e.motion.y;

      // Handling File option
      if (isMouseOver (mouseX, mouseY, selOps[0]))
        {
          changeButtonColor (selOps[0], { 255, 255, 0, 255 });
          renderOpsOption (selFile);
        }
      else
        {
          // Check if the mouse is over any element in selFile
          bool mouseOverSelFile = false;
          for (auto &el : selFile)
            {
              if (isMouseOver (mouseX, mouseY, el))
                {
                  changeButtonColor (el, { 255, 255, 0, 255 });
                  mouseOverSelFile = true;
                  break; // No need to check further once we find a match
                }
              else
                {
                  changeButtonColor (el, { 198, 206, 206, 255 });
                }
            }

          if (mouseOverSelFile)
            {
              changeButtonColor (selOps[0], { 255, 255, 0, 255 });
              renderOpsOption (selFile);
            }
          else
            {
              changeButtonColor (selOps[0], { 198, 206, 206, 255 });
            }
        }

      // Handling Edit option
      if (isMouseOver (mouseX, mouseY, selOps[1]))
        {
          changeButtonColor (selOps[1], { 255, 255, 0, 255 });
          renderOpsOption (selEdit);
        }
      else
        {
          // Check if the mouse is over any element in selEdit
          bool mouseOverSelEdit = false;
          for (auto &el : selEdit)
            {
              if (isMouseOver (mouseX, mouseY, el))
                {
                  changeButtonColor (el, { 255, 255, 0, 255 });
                  mouseOverSelEdit = true;
                  break; // No need to check further once we find a match
                }
              else
                {
                  changeButtonColor (el, { 198, 206, 206, 255 });
                }
            }

          if (mouseOverSelEdit)
            {
              changeButtonColor (selOps[1], { 255, 255, 0, 255 });
              renderOpsOption (selEdit);
            }
          else
            {
              changeButtonColor (selOps[1], { 198, 206, 206, 255 });
            }
        }

      // Handling Options option
      if (isMouseOver (mouseX, mouseY, selOps[2]))
        {
          changeButtonColor (selOps[2], { 255, 255, 0, 255 });
          renderOpsOption (selOptions);
        }
      else
        {
          // Check if the mouse is over any element in selOptions
          bool mouseOverSelOptions = false;
          for (auto &el : selOptions)
            {
              if (isMouseOver (mouseX, mouseY, el))
                {
                  changeButtonColor (el, { 255, 255, 0, 255 });
                  mouseOverSelOptions = true;
                  break; // No need to check further once we find a match
                }
              else
                {
                  changeButtonColor (el, { 198, 206, 206, 255 });
                }
            }

          if (mouseOverSelOptions)
            {
              changeButtonColor (selOps[2], { 255, 255, 0, 255 });
              renderOpsOption (selOptions);
            }
          else
            {
              changeButtonColor (selOps[2], { 198, 206, 206, 255 });
            }
        }
    }
  else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
      int mouseX = e.button.x;
      int mouseY = e.button.y;

      // Check which option is clicked and handle the event
      for (auto &el : selOps)
        {

          if (isMouseOver (mouseX, mouseY, el))
            {
              handleButtonClick (el);
              break;
            }
        }

      // Check if any file option is clicked
      for (auto &el : selFile)
        {
          if (isMouseOver (mouseX, mouseY, el) && el.name == "New")
            {
              int btn;
              this->PopBackWindow (
                  btn, "Creating new file",
                  "Are you really want to create new file and leave current?",
                  "Yes", "No");
              if (btn == 0)
                {
                  std::vector<std::string> tempTextVector = { "" };
                  std::cout << "New file\n";
                  _inputEditor->setText (tempTextVector);
                  _inputEditor->setCursorDefaulr ();
                }
            }
          if (isMouseOver (mouseX, mouseY, el) && el.name == "Save")
            {
              SaveManager savingProc (_windowEditor->getFileName (),
                                      _inputEditor->getTextContent (),
                                      _windowEditor->getPath ());
              savingProc.saveFile (_windowEditor->getWindow ());
            }

          if (isMouseOver (mouseX, mouseY, el) && el.name == "Save as")
            {
              _savingWindow = new EditorWindow ("Saving", 250, 400);
              _filemanager = new FileManager (_savingWindow, _inputEditor,
                                              _windowEditor->getPath ());
              bool sQuit = false;
              SDL_Event sEvent;
              while (!sQuit)
                {
                  while (SDL_PollEvent (&sEvent) != 0)
                    {
                      _filemanager->handleEventMouse (sEvent, sQuit);
                      _filemanager->handleEventKeyboard (sEvent, sQuit);
                      if (sEvent.type == SDL_QUIT)
                        {
                          sQuit = true;
                        }
                      else if (sEvent.window.event == SDL_WINDOWEVENT_CLOSE
                               && sEvent.window.windowID
                                      == SDL_GetWindowID (
                                          _savingWindow->getWindow ()))
                        {
                          sQuit = true;
                        }
                      _savingWindow->render ();
                      _filemanager->render ();
                    }
                }
              delete _filemanager;
              delete _savingWindow;
            }
          if (isMouseOver (mouseX, mouseY, el) && el.name == "Close")
            {
              handleButtonClick (el);
              q = true;
            }
        }

      // Check if any edit option is clicked
      for (auto &el : selEdit)
        {
          if (isMouseOver (mouseX, mouseY, el) && el.name == "Undo")
            {
              std::cout << "Undo\n";
            }
          if (isMouseOver (mouseX, mouseY, el) && el.name == "Paste")
            {
              _inputEditor->handleCtrlV ();
            }
        }

      // Check if any options option is clicked
      for (auto &el : selOptions)
        {
          if (isMouseOver (mouseX, mouseY, el) && el.name == "Credits")
            {
              int btn;
              this->PopBackWindow (btn, "Credits",
                                   "Text editor made by Kapiura\nAll is "
                                   "written in C++ by using SDL library.",
                                   "Ok");
            }
          if (isMouseOver (mouseX, mouseY, el) && el.name == "Customize")
            {
              int btn;
              this->PopBackWindow (
                  btn, "Customization window",
                  "Here you will be able to customize font, colors etc.\n:)",
                  "Soon");
            }
        }
    }
}
void
MenuBar::handleButtonClick (const selectOption &btn)

{
  std::cout << "Button clicked\t" << btn.name << "\n";
}

void
MenuBar::PopBackWindow (int &btn, std::string title, std::string message,
                        std::string yes, std::string no)
{
  SDL_MessageBoxData messageboxdata;
  messageboxdata.flags = SDL_MESSAGEBOX_WARNING;
  messageboxdata.window = _windowEditor->getWindow ();
  messageboxdata.title = title.c_str ();
  messageboxdata.message = message.c_str ();
  SDL_MessageBoxButtonData buttons[]
      = { { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, yes.c_str () },
          { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, no.c_str () } };
  messageboxdata.buttons = buttons;
  messageboxdata.numbuttons = SDL_arraysize (buttons);
  SDL_MessageBoxColor messBackground = { 255, 255, 255 };
  SDL_MessageBoxColor messText = { 0, 0, 0 };
  SDL_MessageBoxColor messButtonBorder = { 0, 0, 0 };
  SDL_MessageBoxColor messButtonBackground = { 255, 255, 255 };
  SDL_MessageBoxColor messButtonSelected = { 150, 150, 25 };
  SDL_MessageBoxColorScheme mescolt
      = { messBackground, messText, messButtonBorder, messButtonBackground,
          messButtonSelected };
  messageboxdata.colorScheme = &mescolt;
  if (SDL_ShowMessageBox (&messageboxdata, &btn) > 0)
    {
      std::cerr << "Messagebox error " << SDL_GetError () << "\n";
      exit (-1);
    }
}
void
MenuBar::PopBackWindow (int &btn, std::string title, std::string message,
                        std::string yes)
{
  SDL_MessageBoxData messageboxdata;
  messageboxdata.flags = SDL_MESSAGEBOX_WARNING;
  messageboxdata.window = _windowEditor->getWindow ();
  messageboxdata.title = title.c_str ();
  messageboxdata.message = message.c_str ();
  SDL_MessageBoxButtonData buttons[]
      = { { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, yes.c_str () } };
  messageboxdata.buttons = buttons;
  messageboxdata.numbuttons = SDL_arraysize (buttons);
  SDL_MessageBoxColor messBackground = { 255, 255, 255 };
  SDL_MessageBoxColor messText = { 0, 0, 0 };
  SDL_MessageBoxColor messButtonBorder = { 0, 0, 0 };
  SDL_MessageBoxColor messButtonBackground = { 255, 255, 255 };
  SDL_MessageBoxColor messButtonSelected = { 150, 150, 25 };
  SDL_MessageBoxColorScheme mescolt
      = { messBackground, messText, messButtonBorder, messButtonBackground,
          messButtonSelected };
  messageboxdata.colorScheme = &mescolt;
  if (SDL_ShowMessageBox (&messageboxdata, &btn) > 0)
    {
      std::cerr << "Messagebox error " << SDL_GetError () << "\n";
      exit (-1);
    }
}
