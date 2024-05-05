#include <stdint.h>

struct registers
{

    uint8_t regs[8];

    // BASE GAMEBOY REGISTERS
    const uint8_t* a;
    const uint8_t* f;
    const uint8_t* b;
    const uint8_t* c;
    const uint8_t* d;
    const uint8_t* e;
    const uint8_t* h;
    const uint8_t* l;

    // 16 BIT REGISTER VIEWS
    const uint16_t* af;
    const uint16_t* bc;
    const uint16_t* de;
    const uint16_t* hl;

    // Special Purpose Registers
    uint16_t PC;
    uint16_t SP;
    
} typedef Registers;

void initRegs(Registers* regBank)
{
    // init register values
    regBank->a = &regBank->regs[0];
    regBank->f = &regBank->regs[1];
    regBank->b = &regBank->regs[2];
    regBank->c = &regBank->regs[3];
    regBank->d = &regBank->regs[4];
    regBank->e = &regBank->regs[5];
    regBank->h = &regBank->regs[6];
    regBank->l = &regBank->regs[7];

    // init register views
    regBank->af = (uint16_t *)&regBank->regs[0];
    regBank->bc = (uint16_t *)&regBank->regs[2];
    regBank->de = (uint16_t *)&regBank->regs[4];
    regBank->hl = (uint16_t *)&regBank->regs[6];
};

struct mem
{
    uint8_t memory[65536];
    uint8_t const* ROM;
    uint8_t* VRAM;

} typedef Mem;

initMem(Mem* memory)
{
    memory->ROM = memory->memory;
}



int loadrom(char* path, Mem* memory)
{
    int romPtr = open(path, 0);
    if (romPtr < 1)
    {
        printf("ERROR: ROM path invalid! Does it exist?");
        exit(1);
    }
    int romSize = read(romPtr, memory->memory, 32767);
    if (romSize < 1)
    {
        printf("ERROR: ROM Read Failed!");
        exit(1);
    }





}




int main(int argc, char** argv)
{

    if (argc < 2)
    {
        printf("ERROR: Input ROM path!");
        exit(1);
    }


    Registers registers;
    initRegs(&registers);

    Mem memory;
    initMem(&memory);

    


}