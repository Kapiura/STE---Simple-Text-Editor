#include <SDL2/SDL_error.h>
#include <iostream>
#include <SDL2/SDL.h>

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << "\n";
		return 1;
	}
    std::cout << "Testowy main.cpp\n";
  return 0;
}
