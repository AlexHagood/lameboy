#ifndef SYS_H
#define SYS_H


#include <stdint.h>

union lcdc
{
    struct 
    {
        uint8_t BackgroundWindowDisplay: 1;
        uint8_t SpriteDisplay: 1;
        uint8_t SpriteSize: 1; // 0: short, 1: tall
        uint8_t BackgroundTileMapSelect: 1;
        uint8_t BackgroundWindowTileData: 1;
        uint8_t WindowDisplay: 1;
        uint8_t WindowTileMapSelect: 1;
        uint8_t LcdControl: 1;
    };
    uint8_t LCDC;
};

typedef struct registers
{
    union
    {
        struct
        {
            union
            {
                struct
                {
                    uint8_t unused : 4;
                    uint8_t Cf : 1;
                    uint8_t Hf : 1;
                    uint8_t Nf : 1;
                    uint8_t Zf : 1;
                };
                uint8_t F;
            };
            uint8_t A;
        };
        uint16_t AF;
    };

    union
    {
        struct
        {
            uint8_t C;
            uint8_t B;
        };
        uint16_t BC;
    };

    union
    {
        struct
        {
            uint8_t E;
            uint8_t D;
        };
        uint16_t DE;
    };

    union
    {
        struct
        {
            uint8_t L;
            uint8_t H;
        };
        uint16_t HL;
    };

    // Special Purpose Registers
    uint8_t *MemZero;
    uint8_t *PC;
    uint8_t *SP;
    uint8_t** ordered;

    // IO Registers
    uint8_t* DIV; // Divider Register
    uint8_t* TIMA; // Timer Counter
    uint8_t* TMA; // Timer Modulo
    uint8_t* TAC; // Timer Control
    uint8_t* IF; // Interrupt Flag

    union lcdc* LCDC; // LCD Control
    uint8_t* SCY; // Scroll Y
    uint8_t* SCX; // Scroll X
    uint8_t* LY;
    uint8_t* LYC;



} Registers;

typedef struct mem
{
    uint8_t* memory;
    uint8_t const* ROM;
    uint8_t* VRAM;
    const char* Title;
    uint8_t* BOOT_ROM;
 
}  Mem;

typedef struct system
{
    Mem mem;
    Registers regs;
    long int cycles;
    
} System;


extern System sys;



#endif // SYS_H