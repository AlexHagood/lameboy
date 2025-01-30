#include <SDL2/SDL.h>

#define COLOR0 155, 188, 15
#define COLOR1 139, 172, 15
#define COLOR2 48, 98, 48
#define COLOR3 15, 56, 15

#define SCREENBUF_W 40
#define SCREENBUF_H 144

#define CIRCULAR_SHIFT_LEFT(val, shift, bits) \
    (((val) << (shift)) | ((val) >> ((bits) - (shift))))

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 576;

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Event event;

void drawScreen(uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H], SDL_Renderer *renderer);

int main()
{

    uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H];

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
    SDL_RenderSetLogicalSize(renderer, 160, 144);
    SDL_SetRenderDrawColor(renderer, COLOR3, 255);

    int running = 1;
    while (running)
    {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        drawScreen(screenBuffer, renderer);
        SDL_RenderPresent(renderer);
        for (int i = 0; i < SCREENBUF_W; i++)
        {
        for (int j = 0; j < SCREENBUF_H; j++)
        {
        screenBuffer[i][j] = CIRCULAR_SHIFT_LEFT(screenBuffer[i][j], 1, 8);
        }}


        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawScreen(uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H], SDL_Renderer *renderer)
{
    for (int x = 0; x < SCREENBUF_W; x++)
    {
        for (int y = 0; y < SCREENBUF_H; y++)
        {
            for (int k = 0; k < 4; k++)
            {
                int shift = 0b11 << (k * 2);
                int color = (screenBuffer[x][y] & shift) >> (k * 2);
                switch (color)
                {
                case 0:
                    SDL_SetRenderDrawColor(renderer, COLOR0, 255);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(renderer, COLOR1, 255);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, COLOR2, 255);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer, COLOR3, 255);
                    break;
                }
                SDL_RenderDrawPoint(renderer, x * 4 + k, y);
            }
        }
    }
}