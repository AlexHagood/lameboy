#include "stdint.h"
#include "sys.h"

void exit(int status);

void load16(uint16_t *dest, uint16_t src)
{
    *dest = src;
}

void xorA(uint8_t n, System *sys)
{
    sys->regs.A ^= n;
    if (sys->regs.A == 0)
    {
        sys->regs.Zf = 1;
    }
    sys->regs.Nf = 0, sys->regs.Hf = 0, sys->regs.Cf = 0;
    sys->regs.PC += 1;
}

void ldd(System *sys)
{
    if (*sys->regs.PC == 0x3a)
    {
        sys->regs.A = sys->mem.memory[sys->regs.HL];

    }
    else if (*sys->regs.PC == 0x32)
    {
        sys->mem.memory[sys->regs.HL] = sys->regs.A;
    }
    else
    {
        exit(32);
    };

    sys->regs.HL -= 1;
    sys->regs.PC += 1;
}

void bit(System *sys, uint8_t bit)
{
    uint8_t op = *sys->regs.PC;
    op -= 0x40;
    

}