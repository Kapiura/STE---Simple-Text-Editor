#include <SDL.h>

class SDLApplication {
public:
    SDLApplication() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            // You might want to handle the initialization failure here.
        }

        window = SDL_CreateWindow(
            "SDL Window",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_SHOWN
        );

        if (!window) {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            // You might want to handle the window creation failure here.
        }
    }

    ~SDLApplication() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Run() {
        bool quit = false;
        SDL_Event event;

        while (!quit) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }
    }

private:
    SDL_Window* window;
};

int main() {
    SDLApplication app;
    app.Run();
    return 0;
}

