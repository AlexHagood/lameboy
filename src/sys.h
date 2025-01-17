#ifndef SYS_H
#define SYS_H

#include <stdint.h>
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
    uint8_t *PC;
    uint16_t SP;

} Registers;

typedef struct mem
{
    uint8_t memory[65536];
    uint8_t const* ROM;
    uint8_t* VRAM;
    const char* Title;
    uint8_t BOOT_ROM[256];
 
}  Mem;

typedef struct system
{
    Mem mem;
    Registers regs;
    long int cycles;
    
} System;

#endif // SYS_H