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

    puts("Loading BOOT rom...");

    loadBootRom(&sys.mem);

    puts("Executing boot sequence");

    for (int i = 0; i < 10; i++) {
            printf("Memory %d: 0x%02X\n", i, sys.mem.BOOT_ROM[i]);
    }
    opCode* operation = NULL;
    
    for (int i = 0; i < 8; i++)
    {
        sys.regs.r[i] = 0;
    }
    sys.regs.PC = sys.mem.BOOT_ROM;
    int count = 0;
    while(1)
    {
        count += 1;
        printf("Count: %x\n", count);
        uint8_t opCode = *sys.regs.PC;
        if (opCode == 0xCB) // CB prefixed opcode
        {
            sys.regs.PC += 1;
            opCode = *sys.regs.PC;
            operation = &CBopCodes[opCode];
            printf("PC: %d, OP: cb %x", sys.regs.PC-sys.mem.BOOT_ROM, opCode);

        } else
        {
            operation = &opCodes[opCode];
            printf("PC: %d, OP: %x", sys.regs.PC-sys.mem.BOOT_ROM, opCode);
        }
        printf(" FLAGS: %x\n", sys.regs.r[F]);
        printf("HL: %d\n", *sys.regs.HL);
        executeOpcode(operation, &sys);
        
    }



    return 0;    

}