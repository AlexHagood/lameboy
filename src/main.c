#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "sys.h"
#include "graphics.h"

int loadrom(char* path, Mem* memory)
{
    int romPtr = open(path, 0);
    if (romPtr < 1)
    {
        puts("ERROR: ROM path invalid! Does it exist?\n");
        return 1;
    }
    int romSize = read(romPtr, memory->memory, 32767);
    if (romSize < 1)
    {
        puts("ERROR: ROM Read Failed!\n");
        return 1;
    }

    printf("ROM of size %d read!\n", romSize);
    return 0;
}



void loadBootRom(Mem* memory)
{
    FILE* bootRom = fopen("roms/DMG_ROM.bin", "rb");
    if (bootRom == NULL)
    {
        puts("ERROR: BOOT ROM not found!\n");
        exit(1);
    }
    memcpy(memory->BOOT_ROM, memory->memory, 256);
    fread(memory->memory, 256, 1, bootRom);
    fclose(bootRom);
}

void initMem(Mem* memory)
{
    memory->memory = (uint8_t*)malloc(65536 * sizeof(uint8_t));
    memory->BOOT_ROM = (uint8_t*)malloc(256 * sizeof(uint8_t));
    if (memory->memory == NULL || memory->BOOT_ROM == NULL)
    {
        puts("ERROR: Memory allocation failed!\n");
        exit(1);
    }


    memory->ROM = memory->memory;
    memory->Title = (char*) &memory->ROM[0x134];
}


int main(int argc, char** argv)
{

    if (argc < 2)
    {
        puts("ERROR: Input ROM path!\n");
        exit(1);
    }

    System sys;
    sys.regs.SP = 0xFEFE;

    initMem(&sys.mem);

    uint8_t* ordered[] = {&sys.regs.B, &sys.regs.C, &sys.regs.D, &sys.regs.E, &sys.regs.H, &sys.regs.L, NULL, &sys.regs.A};
    sys.regs.ordered = ordered;

    if (loadrom(argv[1], &sys.mem) != 0)
    {
        return 1;
    };

    puts(sys.mem.Title);

    // 0x147 determines if the game uses MBC (memory bank controller), exit if it does.
    if (sys.mem.ROM[0x147] != 0)
    {
        printf("ERROR: Only MBC type 0 is supported!\n");
        exit(1);
    };

    puts("Operations initialized!");

    puts("Loading BOOT rom...");

    loadBootRom(&sys.mem);

    puts("Executing boot sequence");

    display(sys);

    sys.regs.PC = sys.mem.memory;
    int count = 0;
    while (1)
    {
        count += 1;
        uint8_t opCode = *sys.regs.PC;

        if (opCode == 0xCB) // CB prefixed opcode
        {
            sys.regs.PC += 1;
            executePrefixOperation(&sys);
        }
        else
        {
            executeOperation(&sys);
        }
        printf("%d\n", count);
    }
    return 0;    

}