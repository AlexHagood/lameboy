#include "registers.c"

typedef struct mem
{
    uint8_t memory[65536];
    uint8_t const* ROM;
    uint8_t* VRAM;
    const char* Title;
 
}  Mem;

void initMem(Mem* memory)
{
    memory->ROM = memory->memory;
    memory->Title = (char*) &memory->ROM[0x134];
}

typedef struct system
{
    Mem mem;
    Registers regs;
    long int cycles;
    
} System;




