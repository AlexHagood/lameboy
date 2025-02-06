#include "stdint.h"
#include "sys.h"
#define SET(flag) (sys->regs.flag = 1)
#define RESET(flag) (sys->regs.flag = 0)
#define FLAG_CONDITION(flag, condition) if (condition) {sys->regs.flag = 1;} else {sys->regs.flag = 0;}
#define CHECK_CARRY(N, Int1, Int2) (((Int1) & (1 << N)) + ((Int2) & (1 << N)) > (1 << N))


void exit(int status);


void inc(uint8_t *reg, System *sys)
{
    *reg += 1;
    FLAG_CONDITION(Zf, *reg == 0);
    RESET(Nf);
    FLAG_CONDITION(Hf, ((*reg - 1) & 0x0F) + 1 > 0x0F);
    sys->regs.PC += 1;
}

void load16(uint16_t *dest, uint16_t src)
{
    *dest = src;
}

void load8(uint8_t *dest, uint8_t src, System *sys)
{
    *dest = src;
    sys->regs.PC++;
}

void load8registers(System *sys)
{
    int op = *sys->regs.PC - 0x40;
    uint8_t src = *(sys->regs.ordered[op % 8]);
    uint8_t *dest = sys->regs.ordered[op / 8];
    if (src == 0)
    {
        src = sys->mem.memory[sys->regs.HL];
    }
    if (dest == 0)
    {
        dest = &sys->mem.memory[sys->regs.HL];
    } 
    load8(dest, src, sys);
}

void xorA(uint8_t n, System *sys)
{
    sys->regs.A ^= n;
    if (sys->regs.A == 0)
    {
        sys->regs.Zf = 1;
    }
    else
    {
        sys->regs.Zf = 0;
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

void ldi(System *sys)
{
    sys->mem.memory[sys->regs.HL] = sys->regs.A;
    sys->regs.HL += 1;
    sys->regs.PC += 1;
}

void bit(System *sys)
{
    uint8_t op = *sys->regs.PC;
    op -= 0x40;
    uint8_t *reg = sys->regs.ordered[op % 8];
    uint8_t bit = op / 8;
    if (!(*reg & (1 << bit)))
    {
        SET(Zf);
    }
    else
    {
        RESET(Zf);
    }
    RESET(Nf);
    SET(Hf);
    sys->regs.PC += 1;
}

 
void jr_conditional(System *sys)
{
    uint8_t op = *sys->regs.PC;
    int8_t offset = (int8_t)*(sys->regs.PC + 1);
    sys->regs.PC += 2;
    uint8_t condition = (op == 0x20 && !(sys->regs.Zf)) || (op == 0x28 && sys->regs.Zf) || (op == 0x30 && !(sys->regs.Cf)) || (op == 0x38 && sys->regs.Cf);
    if (condition)
    {
        
        sys->regs.PC =  sys->regs.PC + offset;
    }
}


void call(System *sys, int condition)
{
    uint16_t jumpAddress = *(sys->regs.PC + 1);
    if (condition)
    {
        sys->regs.SP -= 2;
        *sys->regs.SP = sys->regs.PC + 3 - sys->mem.memory;
        sys->regs.PC = sys->mem.memory + jumpAddress;
    }
    else
    {
        sys->regs.PC += 3;
    }
};


void push(System *sys, uint16_t reg)
{
    sys->regs.SP -= 2;
    *(uint16_t*)sys->regs.SP = reg;
    sys->regs.PC += 1;
}

void pop(System* sys, uint16_t* reg)
{
    *reg = *sys->regs.PC;
    sys->regs.PC += 1;
    sys->regs.SP += 2;
}

void rotate_left(System *sys, uint8_t *reg)
{
    int c = sys->regs.Cf;

    *reg = *reg << 1;
    *reg &= c;

    FLAG_CONDITION(Cf, (*reg & 0x40) != 0);
    RESET(Nf);
    RESET(Hf);
    FLAG_CONDITION(Zf, *reg == 0);

    sys->regs.PC += 1;
}

void decrement(System *sys, uint8_t *reg)
{
    int half_carry = ((*reg & 0xf) == 0 && (*--reg & 0xf) == 0xf);
    FLAG_CONDITION(Hf, half_carry);
    FLAG_CONDITION(Zf, *reg == 0);
    SET(Nf);
    sys->regs.PC += 1;
}

void increment(System *sys, uint16_t* reg)
{
    *reg += 1;
    sys->regs.PC += 1;   
}

void ret(System *sys)
{
    int address = *sys->regs.SP;
    sys->regs.SP += 2;
    sys->regs.PC = sys->mem.memory + address;
}

void cp(System *sys, uint8_t* reg)
{
    FLAG_CONDITION(Zf, (sys->regs.A - *reg) == 0);
    SET(Nf);
    FLAG_CONDITION(Hf, (sys->regs.A & 0x0F) < (*reg & 0x0F));
    FLAG_CONDITION(Cf, sys->regs.A < *reg);
    sys->regs.PC += 1;
}

void add16(System *sys, uint16_t reg)
{
    RESET(Nf);
    FLAG_CONDITION(Cf, CHECK_CARRY(15, sys->regs.HL, reg));
    FLAG_CONDITION(Hf, CHECK_CARRY(11, sys->regs.HL, reg));
    sys->regs.HL += reg;
    sys->regs.PC += 1;
}