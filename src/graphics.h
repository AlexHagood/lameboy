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

uint8_t backgroundTileMap[32][32];

int display(System sys);
void drawSprites(uint8_t tileData[0xfff], uint8_t screenBuffer[SCREENBUF_W][SCREENBUF_H]);

struct tile {
    uint16_t line[8];
};


