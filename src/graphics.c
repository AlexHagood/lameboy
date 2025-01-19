#include <SDL2/SDL.h>

#define COLOR0 155, 188, 15
#define COLOR1 139, 172, 15
#define COLOR2 48, 98, 48
#define COLOR3 15, 56, 15

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 288;

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Event event;
int main(){


    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("LameBoy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, COLOR3, 255);

    while (1) {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}