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
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_RenderSetLogicalSize(renderer, 160, 144);
}

void draw_bg()
{

    static uint8_t* tileMapTable0[32];
    static uint8_t* tileMapTable1[32];

    static __uint128_t* tileDataTable0;
    static __uint128_t* tileDataTable1;

    static __uint128_t backgroundSprites[32][32];

    if (tileDataTable0 == NULL && tileDataTable1 == NULL)
    {
        printf("Initializing background tile data");
        init_background(tileMapTable0, &sys.mem.memory[0x9800]);
        init_background(tileMapTable0, &sys.mem.memory[0x9C00]);
        tileDataTable0 = &sys.mem.memory[0x8800];
        tileDataTable1 = &sys.mem.memory[0x8000];
    }

    uint8_t** tileMapTable;
    __uint128_t* tileDataTable;

    tileDataTable = sys.regs.LCDC->TileDataSelect ? tileDataTable1 : tileDataTable0;
    uint8_t imod = sys.regs.LCDC->TileDataSelect ? 0 : 128;
    tileMapTable = sys.regs.LCDC->BackgroundTileMapSelect ? tileMapTable1 : tileMapTable0;

    for (int x = 0; x < 32; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            backgroundSprites[x][y] = tileDataTable[tileMapTable[x][y] + imod];
        }
    }

    for (int xi = 0; xi < 160; xi++)
    {
        for (int yi = 0; yi < 144; yi++)
        {
            uint8_t x = xi + sys.regs.SCX;
            uint8_t y = yi + sys.regs.SCY;

            __uint128_t sprite = backgroundSprites[x / 32][y / 32 ];
            uint8_t pixel = (x % 8) + ((y % 8) * 8);

            uint16_t spriteRow = ((uint16_t*)&sprite)[y % 8];
            uint8_t spriteCol = x % 8;

            int pallete_lo = (spriteRow & (0x8000 >> spriteCol)) != 0;
            int pallete_hi = (spriteRow & (0x80 >> spriteCol)) != 0;
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
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}


void init_background(uint8_t*** tileMapTable, uint8_t* tileMapAddress)
{
    for (int i = 0; i < 32; i++)
    {
        *tileMapTable[i] = tileMapAddress[i*32];
    };
    return;
}

int display()
{

    uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H];
    memset(screenBuffer, 0, sizeof(screenBuffer));

    drawSprites(&sys.mem.memory[0x30ae], screenBuffer);

    


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
    return 0;
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




            }
        }
    }
}