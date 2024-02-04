#include "../include/Slider.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
Slider::Slider (EditorWindow *window, InputEditor *_editorInput, int x, int w, int y, int h)
	// r,g,b,x,w,y,h,font
	: r (255), g (255), b (255), x (x), w (w), y (y), h (h), _renderer (window->getRenderer ()),
	  _inputEditor (_editorInput)
{
	slider = {x, w, y, h};
	xMove = x + w;
	yMove = y;
	wMove = 10;
	hMove = 10;
	sliderVal = {xMove, wMove, yMove, hMove};
	if (r > 0)
	{
		yMove = _inputEditor->returnBackgroundColor ().r;
	}
	else if (g > 0)
	{

		yMove = _inputEditor->returnBackgroundColor ().g;
	}
	else if (b > 0)
	{
		yMove = _inputEditor->returnBackgroundColor ().b;
	}
	sliderVal.y = yMove + 10;
	rm = 255;
	gm = 255;
	bm = 255;

	loadFont ("assets/jetbrainsmono/JetBrainsMono-Regular.ttf", fontSize);
	// value = {x - 5, y + 40, 32 * 3, 32};
	std::cout << "Silder object has been created\n";
}

Slider::~Slider ()
{
	std::cout << "Slider object has been deleted\n";
}

void Slider::renderSlider ()
{
	SDL_SetRenderDrawColor (_renderer, r, g, b, 255);
	SDL_RenderFillRect (_renderer, &slider);
}

void Slider::setMoveSliderColor (int v)
{
	yMove = v;
}

void Slider::setSliderColor (int re, int gr, int bl)
{
	r = re;
	g = gr;
	b = bl;
}

void Slider::updateColorText ()
{
	std::string temp = std::to_string (yMove);
}

std::string Slider::returnColorText ()
{
	std::string temp = std::to_string (yMove);
	return temp;
}

void Slider::renderSliderMove (int mouseX, int mouseY)
{
	isMouseOver = this->isMouseOverSlider (mouseX, mouseY);
	if (isMouseOver)
	{
		rm = 255;
		gm = 255;
		bm = 0;
	}
	else
	{
		rm = 255;
		gm = 255;
		bm = 255;
	}
	SDL_SetRenderDrawColor (_renderer, rm, gm, bm, 255);
	SDL_RenderFillRect (_renderer, &sliderVal);
}

void Slider::loadFont (const std::string &fontPath, int fontSize)
{
	_font = TTF_OpenFont (fontPath.c_str (), fontSize);
	if (! _font)
	{
		std::cout << "SDL TTF error loading font: " << SDL_GetError () << "\n";
		exit (-1);
	}
}

void Slider::renderValueText ()
{
	SDL_SetRenderDrawColor (_renderer, textColor.r, textColor.g, textColor.b, 255);

	// Konwertuj wartość liczbową na napis.
	std::string valueText = std::to_string (yMove);

	// Renderuj tekst na powierzchni.
	SDL_Surface *tempSurf = TTF_RenderText_Solid (_font, valueText.c_str (), textColor);
	SDL_Texture *tempTexture = SDL_CreateTextureFromSurface (_renderer, tempSurf);
	int textWidth, textHeight;
	SDL_QueryTexture (tempTexture, NULL, NULL, &textWidth, &textHeight);

	// Ustaw pozycję i rozmiar dla tekstu (na środku slidera poniżej niego).
	int textX = x + (w - textWidth) / 2 + 5; // Przesunięcie o 5 pikseli w prawo.
	int textY = y + h + 10;					 // 10 pikseli poniżej slidera.

	// Utwórz prostokąt dla tekstu.
	SDL_Rect valueRect = {textX, textY, textWidth, textHeight};

	// Renderuj tekst na docelowej powierzchni.
	SDL_RenderCopy (_renderer, tempTexture, NULL, &valueRect);
	SDL_RenderDrawRect (_renderer, &valueRect);

	// Zwolnij zasoby.
	SDL_DestroyTexture (tempTexture);
	SDL_FreeSurface (tempSurf);
}

bool Slider::isMouseOverSlider (int &mouseX, int &mouseY)
{
	return mouseX >= sliderVal.x && mouseX <= (sliderVal.x + sliderVal.w) && mouseY >= sliderVal.y
		   && mouseY <= (sliderVal.y + sliderVal.h);
}

void Slider::setSliderValue (int &yy, bool isClicked)
{

	if (isClicked == true)
	{
		if (isMouseOver)
		{
			if (yy > 266)
			{

				sliderVal.y = 265;
				yMove = sliderVal.y - 10;
			}
			else if (yy < 10)
			{

				sliderVal.y = 10;
				yMove = 0;
			}
			else
			{

				sliderVal.y = yy;
				yMove = yy - 10;
			}
		}
	}
}

void Slider::setSliderValue (int v)
{
	sliderVal.y = v;
}
