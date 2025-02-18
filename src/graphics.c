#include <SDL2/SDL.h>
#include "sys.h"
#include "graphics.h"

System sys;

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

void set_tile_color(__uint128_t tile, uint8_t pixelNumber)
{
    uint16_t spriteRow = ((uint16_t*)&tile)[pixelNumber / 8];
    uint8_t spriteCol = pixelNumber % 8;

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
        init_background(tileMapTable1, &sys.mem.memory[0x9C00]);
        tileDataTable0 = (__uint128_t*)&sys.mem.memory[0x8800];
        tileDataTable1 = (__uint128_t*)&sys.mem.memory[0x8000];
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
            uint8_t x = xi + *sys.regs.SCX;
            uint8_t y = yi + *sys.regs.SCY;

            __uint128_t sprite = backgroundSprites[x / 32][y / 32 ];
            uint8_t pixel = (x % 8) + ((y % 8) * 8);

            set_tile_color(sprite, pixel);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}


void draw_sprites()
{
    static Sprite* oam = NULL;
    if (oam == NULL)
    {
        oam = (Sprite*)&sys.mem.memory[0xFE00];
    };
    
    if (sys.regs.LCDC->SpriteSize)
    {
        printf("Big sprites not implemented");
        exit(1);
    }
    
    for (int s = 0; s < 40; s++)
    {
        int spriteX = oam[s].x - 8;
        int spriteY = oam[s].y - 16;

        __uint128_t tile = sys.mem.memory[0x8000] + oam[s].pattern;

        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                set_tile_color(tile, y*8+x);
                SDL_RenderDrawPoint(renderer, spriteX, spriteY);
            }
        }

    }


}

void init_background(uint8_t** tileMapTable, uint8_t* tileMapAddress)
{
    for (int i = 0; i < 32; i++)
    {
        tileMapTable[i] = &tileMapAddress[i*32];
    };
    return;
}

int display()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }
    }

    return 0;
}


