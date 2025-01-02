#include "registers.c"

typedef struct mem
{
    uint8_t memory[65536];
    uint8_t const* ROM;
    uint8_t* VRAM;
    const char* Title;
    uint8_t BOOT_ROM[256];
 
}  Mem;

void loadBootRom(Mem* memory)
{
    FILE* bootRom = fopen("roms/DMG_ROM.bin", "rb");
    fread(memory->BOOT_ROM, 256, 1, bootRom);
    fclose(bootRom);
}

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




