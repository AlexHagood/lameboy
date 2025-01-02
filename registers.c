#include <stdint.h>

typedef enum {
    A, F, B, C, D, E, H, L, AF = 0, BC = 2, DE = 4, HL = 6
} RegisterName;

typedef struct registers
{

    uint8_t r[8];

    // BASE GAMEBOY REGISTERS
    const uint8_t* A;
    const uint8_t* F;
    const uint8_t* B;
    const uint8_t* C;
    const uint8_t* D;
    const uint8_t* E;
    const uint8_t* H;
    const uint8_t* L;

    // 16 BIT REGISTER VIEWS
    const uint16_t* AF;
    const uint16_t* BC;
    const uint16_t* DE;
    const uint16_t* HL;

    // Special Purpose Registers
    uint8_t* PC;
    uint16_t SP;
    
} Registers;

void initRegs(Registers* regBank)
{
    // init register pointer values
    regBank->A = &regBank->r[A];
    regBank->F = &regBank->r[F];
    regBank->B = &regBank->r[B];
    regBank->C = &regBank->r[C];
    regBank->D = &regBank->r[D];
    regBank->E = &regBank->r[E];
    regBank->H = &regBank->r[H];
    regBank->L = &regBank->r[L];


    // init register views
    regBank->AF = (uint16_t *)&regBank->r[AF];
    regBank->BC = (uint16_t *)&regBank->r[BC];
    regBank->DE = (uint16_t *)&regBank->r[DE];
    regBank->HL = (uint16_t *)&regBank->r[HL];

    //init special registers
    regBank->SP = 0xFEFE;

};