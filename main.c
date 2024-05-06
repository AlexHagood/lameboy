#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "opcodes.c"





int loadrom(char* path, Mem* memory)
{
    int romPtr = open(path, 0);
    if (romPtr < 1)
    {
        printf("ERROR: ROM path invalid! Does it exist?\n");
        return 1;
    }
    int romSize = read(romPtr, memory->memory, 32767);
    if (romSize < 1)
    {
        printf("ERROR: ROM Read Failed!\n");
        return 1;
    }

    printf("ROM of size %d read!\n", romSize);
    return 0;
}




int main(int argc, char** argv)
{

    if (argc < 2)
    {
        printf("ERROR: Input ROM path!\n");
        exit(1);
    }

    System sys;
    initRegs(&sys.regs);

    initMem(&sys);

    if (loadrom(argv[1], &sys.mem) != 0)
    {
        return 1;
    }
    puts(sys.mem.Title);

    // 0x147 determines if the game uses MBC (memory bank controller), exit if it does.
    if (sys.mem.ROM[0x147] != 0)
    {
        printf("ERROR: Only MBC type 0 is supported!\n");
        exit(1);
    }

    puts("Initializing operations...");

    opCode opCodes[256];
    opCode CBopCodes[256];

    initOps(opCodes, CBopCodes, &sys.regs);

    puts("Operations initialized!");


    return 0;    

}