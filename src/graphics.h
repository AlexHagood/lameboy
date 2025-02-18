#include <stdint.h>
#include "sys.h"
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
SDL_Renderer *renderer = NULL;
SDL_Event event;


int display();
void drawSprites(uint8_t tileData[0xfff], uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H]);
void set_tile_color(__uint128_t tile, uint8_t pixelNumber);
void init_graphics();
void draw_bg();
void draw_sprites();
void init_background(uint8_t** tileMapTable, uint8_t* tileMapAddress);
struct tile {
    uint16_t line[8];
};

typedef struct sprite {
    uint8_t x;
    uint8_t y;
    union{
        uint8_t pattern;
        struct {
            uint8_t ignored: 1;
            uint8_t patternBig: 7;
        };
    };
    struct 
    {
        uint8_t ignored2: 4;
        uint8_t pallete: 1;
        uint8_t xflip: 1;
        uint8_t yflip: 1;
        uint8_t priority: 1;
    };
    
} Sprite;


