#include "../include/CustomizationApp.h"
#include "../include/Slider.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>

CustomizationApp::CustomizationApp (EditorWindow *edit, InputEditor *in)
	: _editorWindow (edit), _editorInput (in), isBackgroundSelected (1)
{

	loadFont ("assets/jetbrainsmono/JetBrainsMono-Regular.ttf", 21);
	// window, font, x, w, y, h
	sliderRed = new Slider (_editorWindow, _editorInput, 10, 10, 10, 265);
	sliderGreen = new Slider (_editorWindow, _editorInput, 80, 10, 10, 265);
	sliderBlue = new Slider (_editorWindow, _editorInput, 150, 10, 10, 265);
	sliderRed->setSliderColor (255, 0, 0);
	sliderGreen->setSliderColor (0, 255, 0);
	sliderBlue->setSliderColor (0, 0, 255);

	btnSetCurrent = {210, 20, 150, 50};
	btnSetDefault = {210, 80, 150, 50};
	btnSelectFont = {210, 140, 150, 50};
	btnSelectBackground = {210, 200, 150, 50};
	changeBackgroundColor (true);

	std::cout << "CustomizationApp object has been created\n";
}
CustomizationApp::~CustomizationApp ()
{
	delete sliderRed;
	delete sliderGreen;
	delete sliderBlue;
	std::cout << "CustomizationApp object has been deleted\n";
}
void CustomizationApp::loadFont (const std::string &fontPath, int fontSize)
{
	_font = TTF_OpenFont (fontPath.c_str (), fontSize);
	if (! _font)
	{
		std::cout << "SDL TTF error loading font: " << SDL_GetError () << "\n";
		exit (-1);
	}
}

void CustomizationApp::render (int &mouseX, int &mouseY, SDL_Event &e)
{

	SDL_RenderClear (_editorWindow->getRenderer ());
	SDL_SetRenderDrawColor (_editorWindow->getRenderer (), backgroundColor.r, backgroundColor.g, backgroundColor.b,
							backgroundColor.a);

	sliderRed->renderSlider ();
	sliderGreen->renderSlider ();
	sliderBlue->renderSlider ();
	sliderRed->renderSliderMove (mouseX, mouseY);
	sliderGreen->renderSliderMove (mouseX, mouseY);
	sliderBlue->renderSliderMove (mouseX, mouseY);
	sliderRed->renderValueText ();
	sliderGreen->renderValueText ();
	sliderBlue->renderValueText ();
	renderButtons (mouseX, mouseY);
	buttonFun (mouseX, mouseY, e);
	SDL_SetRenderDrawColor (_editorWindow->getRenderer (), backgroundColor.r, backgroundColor.g, backgroundColor.b,
							backgroundColor.a);
}

void CustomizationApp::changeSliderValue (int &mouseX, int &mouseY, bool isCliked)
{
	if (true == false)
		std::cout << mouseX << "\n";
	sliderRed->setSliderValue (mouseY, isCliked);
	sliderBlue->setSliderValue (mouseY, isCliked);
	sliderGreen->setSliderValue (mouseY, isCliked);
}

void CustomizationApp::renderButtons (int &mouseX, int &mouseY)
{
	SDL_Rect temp[ 4 ] = {btnSetCurrent, btnSetDefault, btnSelectFont, btnSelectBackground};
	std::string tempstr[ 4 ] = {"Set", "Default", "Font", "Background"};

	for (int i = 0; i < 4; ++i)
	{
		if (this->isMouseOverBtns (mouseX, mouseY, temp[ i ]))
		{
			SDL_SetRenderDrawColor (_editorWindow->getRenderer (), 255, 255, 0, 255);
		}
		else
		{
			SDL_SetRenderDrawColor (_editorWindow->getRenderer (), 255, 255, 255, 255);
		}

		SDL_RenderFillRect (_editorWindow->getRenderer (), &temp[ i ]);
		SDL_SetRenderDrawColor (_editorWindow->getRenderer (), 0, 0, 0, 255);
		SDL_RenderDrawRect (_editorWindow->getRenderer (), &temp[ i ]);

		int textWidth, textHeight;
		TTF_SizeText (_font, tempstr[ i ].c_str (), &textWidth, &textHeight);

		int textX = temp[ i ].x + (temp[ i ].w - textWidth) / 2;
		int textY = temp[ i ].y + (temp[ i ].h - textHeight) / 2;

		SDL_Surface *surface = TTF_RenderText_Solid (_font, tempstr[ i ].c_str (), {0, 0, 0, 255});

		SDL_Texture *texture = SDL_CreateTextureFromSurface (_editorWindow->getRenderer (), surface);
		SDL_FreeSurface (surface);

		SDL_Rect textDestRect = {textX, textY, textWidth, textHeight};
		SDL_RenderCopy (_editorWindow->getRenderer (), texture, nullptr, &textDestRect);

		SDL_DestroyTexture (texture);
	}
}

bool CustomizationApp::isMouseOverBtns (int &mouseX, int &mouseY, SDL_Rect &temp)
{
	return mouseX >= temp.x && mouseX <= (temp.x + temp.w) && mouseY >= temp.y && mouseY <= (temp.y + temp.h);
}

void CustomizationApp::buttonFun (int &mouseX, int &mouseY, SDL_Event &e)
{
	SDL_Rect temp[ 4 ] = {btnSetCurrent, btnSetDefault, btnSelectFont, btnSelectBackground};
	for (int i = 0; i < 4; ++i)
	{
		if (isMouseOverBtns (mouseX, mouseY, temp[ i ]))
		{
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
			{
				switch (i)
				{
				case 0:
					if (isBackgroundSelected)
					{
						Uint8 red = static_cast<Uint8> (std::max (0, std::min (255, sliderRed->getValue ())));
						Uint8 green = static_cast<Uint8> (std::max (0, std::min (255, sliderGreen->getValue ())));
						Uint8 blue = static_cast<Uint8> (std::max (0, std::min (255, sliderBlue->getValue ())));

						SDL_Color temp = {red, green, blue, 255};
						_editorInput->setBackgroundColor (temp);
					}
					else
					{
						Uint8 red = static_cast<Uint8> (std::max (0, std::min (255, sliderRed->getValue ())));
						Uint8 green = static_cast<Uint8> (std::max (0, std::min (255, sliderGreen->getValue ())));
						Uint8 blue = static_cast<Uint8> (std::max (0, std::min (255, sliderBlue->getValue ())));

						SDL_Color temp = {red, green, blue, 255};
						_editorInput->setFontColor (temp);
					}
					std::cout << "Set button clicked\n";
					break;
				case 1:
					if (isBackgroundSelected == true)
					{
						setSliderColorBackground ();
						_editorInput->setBackgroundColor ({255, 255, 255, 255});
						changeBackgroundColor (true);
					}
					else
					{
						setSliderColorFont ();
						_editorInput->setFontColor ({0, 0, 0, 255});
						changeBackgroundColor (false);
					}
					std::cout << "Default button clicked\n";
					break;
				case 2:
					isBackgroundSelected = false;
					changeBackgroundColor (false);
					std::cout << "Font button clicked\n";
					break;
				case 3:
					isBackgroundSelected = true;
					changeBackgroundColor (true);
					std::cout << "Background button clicked\n";
					break;
				}
			}
		}
	}
}

void CustomizationApp::setSliderColorBackground ()
{
	sliderRed->setMoveSliderColor (255);
	sliderRed->setSliderValue (265);
	sliderGreen->setMoveSliderColor (255);
	sliderGreen->setSliderValue (265);
	sliderBlue->setMoveSliderColor (255);
	sliderBlue->setSliderValue (265);
}
void CustomizationApp::setSliderColorFont ()
{
	sliderRed->setMoveSliderColor (0);
	sliderRed->setSliderValue (10);
	sliderGreen->setMoveSliderColor (0);
	sliderGreen->setSliderValue (10);
	sliderBlue->setMoveSliderColor (0);
	sliderBlue->setSliderValue (10);
}

void CustomizationApp::changeBackgroundColor (bool ziutek)
{
	SDL_Color temp;
	if (ziutek == true)
	{
		temp = _editorInput->returnBackgroundColor ();
	}
	else
	{
		temp = _editorInput->returnFontColor ();
	}
	sliderRed->setMoveSliderColor (temp.r);
	sliderRed->setSliderValue (temp.r + 10);
	sliderGreen->setMoveSliderColor (temp.g);
	sliderGreen->setSliderValue (temp.g + 10);
	sliderBlue->setMoveSliderColor (temp.b);
	sliderBlue->setSliderValue (temp.b + 10);
}
