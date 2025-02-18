#include <SDL2/SDL.h>
#include "sys.h"
#include "graphics.h"

void drawScreen(uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H], SDL_Renderer *renderer);

void init_graphics()
{
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 160, 144);
}

int display(System sys)
{

    uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H];
    memset(screenBuffer, 0, sizeof(screenBuffer));

    drawSprites(&sys.mem.ROM[0x30ae], screenBuffer);

    


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


        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// copy sprite data from 1d array to 2d screenbuffer array for testing
void drawSprites(uint8_t tileData[0xfff], uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H])
{
    int sX = 0;
    int sY = 0;
    for (int tile = 0; tile < 256; tile++)
    {
        uint8_t* sprite = &tileData[tile * 16];
        for (int y = 0; y < 8; y++)
        {
            screenBuffer[sX][sY + y] = sprite[y*2];
            screenBuffer[sX + 1][sY + y] = sprite[y*2 + 1];

        }
        sX += 2;
        if (sX % SCREENBUF_W == 0)
        {
            sX = 0;
            sY += 8;
        }
    }

}

void drawScreen(uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H], SDL_Renderer *renderer)
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < SCREENBUF_H; y++)
        {
            for (int k = 0; k < 8; k++)
            {

                int pallete_lo = (screenBuffer[x * 2][y] & (0x80 >> k)) != 0;
                int pallete_hi = (screenBuffer[x * 2 + 1][y] & (0x80 >> k)) != 0;
                int color = (pallete_hi << 1) | pallete_lo;

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
                SDL_RenderDrawPoint(renderer, x * 8 + k, y);
            }
        }
    }
}