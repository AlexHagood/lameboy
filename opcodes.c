#include <stdint.h>
#include <string.h>
#include "sys.c"
enum Flags
{
    Z = 7,
    N = 6,
    Hf = 5,
    Cf = 4,
};

const uint8_t bitSets[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const uint8_t iBitSets[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

enum Opcode
{

    ILLEGAL = -1,
    NOP,
    LD,
    LDD,
    ADD,
    SUB,
    IF,
    DEC,
    RLCA,
    RRCA,
    RLA,
    RRA,
    STOP,
    JR,
    JRS, // Jump if flag is set
    JRR, // Jump if flag is reset
    DAA,
    CPL,
    SCF,
    CCF,
    HALT,
    SBC,
    ADC,
    AND,
    XOR,
    CP,
    OR,
    RET,
    POP,
    PUSH,
    CALL,
    JP,
    RST,
    PREFIX,
    DI,
    EI,
    RETI,
    LDH,
    RLC,
    RRC,
    SWAP,
    SRA,
    SLA,
    SET,
    BIT,
    RL,
    RR,
    SRL,
    RES
};

typedef struct OPCODE
{
    uint16_t *reg1; // Points to register to operate on
    uint16_t *reg2; // Points to register, or 0 for one argument instructions, or SP for immediates.

    uint8_t iSize;
    // Bit 0 indicates if reg1 is 16bit or 8bit.
    // bit 1 indicates if reg2 is 16bit or 8bit.
    uint8_t cycles;
    int mnemonic;
} opCode;

void initOpcode(opCode *op, uint16_t *reg1, uint16_t *reg2, uint8_t isize, uint8_t cycles, int mnemonic)
{
    op->reg1 = reg1;
    op->reg2 = reg2;
    op->iSize = isize;
    op->cycles = cycles;
    op->mnemonic = mnemonic;
}

void initOps(opCode *opCodes, opCode *CBopCodes, Registers *Regs)
{
    // NON PREFIXED OPCODES
    initOpcode(&opCodes[0x0], 0, 0, 0, 4, NOP);
    initOpcode(&opCodes[0x1], Regs->BC, &Regs->PC, 3, 12, LD);
    initOpcode(&opCodes[0x2], Regs->BC, Regs->A, 1, 8, LD);
    initOpcode(&opCodes[0x3], Regs->BC, 0, 1, 8, IF);
    initOpcode(&opCodes[0x4], Regs->B, 0, 0, 4, IF);
    initOpcode(&opCodes[0x5], Regs->B, 0, 0, 4, DEC);
    initOpcode(&opCodes[0x6], Regs->B, &Regs->PC, 0, 8, LD);
    initOpcode(&opCodes[0x7], 0, 0, 0, 4, RLCA);
    initOpcode(&opCodes[0x8], &Regs->SP, &Regs->PC, 3, 20, LD);
    initOpcode(&opCodes[0x9], Regs->HL, Regs->BC, 3, 8, ADD);
    initOpcode(&opCodes[0xa], Regs->A, Regs->BC, 2, 8, LD);
    initOpcode(&opCodes[0xb], Regs->BC, 0, 1, 8, DEC);
    initOpcode(&opCodes[0xc], Regs->C, 0, 0, 4, IF);
    initOpcode(&opCodes[0xd], Regs->C, 0, 0, 4, DEC);
    initOpcode(&opCodes[0xe], Regs->C, &Regs->PC, 0, 8, LD);
    initOpcode(&opCodes[0xf], 0, 0, 0, 4, RRCA);
    initOpcode(&opCodes[0x10], &Regs->PC, 0, 0, 4, STOP);
    initOpcode(&opCodes[0x11], Regs->DE, &Regs->PC, 3, 12, LD);
    initOpcode(&opCodes[0x12], Regs->DE, Regs->A, 1, 8, LD);
    initOpcode(&opCodes[0x13], Regs->DE, 0, 1, 8, IF);
    initOpcode(&opCodes[0x14], Regs->D, 0, 0, 4, IF);
    initOpcode(&opCodes[0x15], Regs->D, 0, 0, 4, DEC);
    initOpcode(&opCodes[0x16], Regs->D, &Regs->PC, 0, 8, LD);
    initOpcode(&opCodes[0x17], 0, 0, 0, 4, RLA);
    initOpcode(&opCodes[0x18], &Regs->PC, 0, 0, 12, JR);
    initOpcode(&opCodes[0x19], Regs->HL, Regs->DE, 3, 8, ADD);
    initOpcode(&opCodes[0x1a], Regs->A, Regs->DE, 2, 8, LD);
    initOpcode(&opCodes[0x1b], Regs->DE, 0, 1, 8, DEC);
    initOpcode(&opCodes[0x1c], Regs->E, 0, 0, 4, IF);
    initOpcode(&opCodes[0x1d], Regs->E, 0, 0, 4, DEC);
    initOpcode(&opCodes[0x1e], Regs->E, &Regs->PC, 0, 8, LD);
    initOpcode(&opCodes[0x1f], 0, 0, 0, 4, RRA);
    initOpcode(&opCodes[0x20], Regs->PC+1, &bitSets[Z], 0, 12, JRR);
    initOpcode(&opCodes[0x21], Regs->HL, &Regs->PC, 3, 12, LD);
    initOpcode(&opCodes[0x22], Regs->HL, Regs->A, 1, 8, LD);
    initOpcode(&opCodes[0x23], Regs->HL, 0, 1, 8, IF);
    initOpcode(&opCodes[0x24], Regs->H, 0, 0, 4, IF);
    initOpcode(&opCodes[0x25], Regs->H, 0, 0, 4, DEC);
    initOpcode(&opCodes[0x26], Regs->H, &Regs->PC, 0, 8, LD);
    initOpcode(&opCodes[0x27], 0, 0, 0, 4, DAA);
    initOpcode(&opCodes[0x28], &Regs->PC, &bitSets[Z], 0, 12, JRS);
    initOpcode(&opCodes[0x29], Regs->HL, Regs->HL, 3, 8, ADD);
    initOpcode(&opCodes[0x2a], Regs->A, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x2b], Regs->HL, 0, 1, 8, DEC);
    initOpcode(&opCodes[0x2c], Regs->L, 0, 0, 4, IF);
    initOpcode(&opCodes[0x2d], Regs->L, 0, 0, 4, DEC);
    initOpcode(&opCodes[0x2e], Regs->L, &Regs->PC, 0, 8, LD);
    initOpcode(&opCodes[0x2f], 0, 0, 0, 4, CPL);
    initOpcode(&opCodes[0x30], &Regs->PC, &bitSets[Cf], 0, 12, JRR);
    initOpcode(&opCodes[0x31], &Regs->SP, &Regs->PC, 3, 12, LD);
    initOpcode(&opCodes[0x32], Regs->HL, Regs->A, 1, 8, LDD);
    initOpcode(&opCodes[0x33], &Regs->PC, 0, 1, 8, IF);
    initOpcode(&opCodes[0x34], Regs->HL, 0, 1, 12, IF);
    initOpcode(&opCodes[0x35], Regs->HL, 0, 1, 12, DEC);
    initOpcode(&opCodes[0x36], Regs->HL, &Regs->PC, 1, 12, LD);
    initOpcode(&opCodes[0x37], 0, 0, 0, 4, SCF);
    initOpcode(&opCodes[0x38], &Regs->PC, &bitSets[Cf], 0, 12, JRS);
    initOpcode(&opCodes[0x39], Regs->HL, &Regs->PC, 3, 8, ADD);
    initOpcode(&opCodes[0x3a], Regs->A, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x3b], &Regs->PC, 0, 1, 8, DEC);
    initOpcode(&opCodes[0x3c], Regs->A, 0, 0, 4, IF);
    initOpcode(&opCodes[0x3d], Regs->A, 0, 0, 4, DEC);
    initOpcode(&opCodes[0x3e], Regs->A, &Regs->PC, 0, 8, LD);
    initOpcode(&opCodes[0x3f], 0, 0, 0, 4, CCF);
    initOpcode(&opCodes[0x40], Regs->B, Regs->B, 0, 4, LD);
    initOpcode(&opCodes[0x41], Regs->B, Regs->C, 0, 4, LD);
    initOpcode(&opCodes[0x42], Regs->B, Regs->D, 0, 4, LD);
    initOpcode(&opCodes[0x43], Regs->B, Regs->E, 0, 4, LD);
    initOpcode(&opCodes[0x44], Regs->B, Regs->H, 0, 4, LD);
    initOpcode(&opCodes[0x45], Regs->B, Regs->L, 0, 4, LD);
    initOpcode(&opCodes[0x46], Regs->B, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x47], Regs->B, Regs->A, 0, 4, LD);
    initOpcode(&opCodes[0x48], Regs->C, Regs->B, 0, 4, LD);
    initOpcode(&opCodes[0x49], Regs->C, Regs->C, 0, 4, LD);
    initOpcode(&opCodes[0x4a], Regs->C, Regs->D, 0, 4, LD);
    initOpcode(&opCodes[0x4b], Regs->C, Regs->E, 0, 4, LD);
    initOpcode(&opCodes[0x4c], Regs->C, Regs->H, 0, 4, LD);
    initOpcode(&opCodes[0x4d], Regs->C, Regs->L, 0, 4, LD);
    initOpcode(&opCodes[0x4e], Regs->C, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x4f], Regs->C, Regs->A, 0, 4, LD);
    initOpcode(&opCodes[0x50], Regs->D, Regs->B, 0, 4, LD);
    initOpcode(&opCodes[0x51], Regs->D, Regs->C, 0, 4, LD);
    initOpcode(&opCodes[0x52], Regs->D, Regs->D, 0, 4, LD);
    initOpcode(&opCodes[0x53], Regs->D, Regs->E, 0, 4, LD);
    initOpcode(&opCodes[0x54], Regs->D, Regs->H, 0, 4, LD);
    initOpcode(&opCodes[0x55], Regs->D, Regs->L, 0, 4, LD);
    initOpcode(&opCodes[0x56], Regs->D, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x57], Regs->D, Regs->A, 0, 4, LD);
    initOpcode(&opCodes[0x58], Regs->E, Regs->B, 0, 4, LD);
    initOpcode(&opCodes[0x59], Regs->E, Regs->C, 0, 4, LD);
    initOpcode(&opCodes[0x5a], Regs->E, Regs->D, 0, 4, LD);
    initOpcode(&opCodes[0x5b], Regs->E, Regs->E, 0, 4, LD);
    initOpcode(&opCodes[0x5c], Regs->E, Regs->H, 0, 4, LD);
    initOpcode(&opCodes[0x5d], Regs->E, Regs->L, 0, 4, LD);
    initOpcode(&opCodes[0x5e], Regs->E, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x5f], Regs->E, Regs->A, 0, 4, LD);
    initOpcode(&opCodes[0x60], Regs->H, Regs->B, 0, 4, LD);
    initOpcode(&opCodes[0x61], Regs->H, Regs->C, 0, 4, LD);
    initOpcode(&opCodes[0x62], Regs->H, Regs->D, 0, 4, LD);
    initOpcode(&opCodes[0x63], Regs->H, Regs->E, 0, 4, LD);
    initOpcode(&opCodes[0x64], Regs->H, Regs->H, 0, 4, LD);
    initOpcode(&opCodes[0x65], Regs->H, Regs->L, 0, 4, LD);
    initOpcode(&opCodes[0x66], Regs->H, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x67], Regs->H, Regs->A, 0, 4, LD);
    initOpcode(&opCodes[0x68], Regs->L, Regs->B, 0, 4, LD);
    initOpcode(&opCodes[0x69], Regs->L, Regs->C, 0, 4, LD);
    initOpcode(&opCodes[0x6a], Regs->L, Regs->D, 0, 4, LD);
    initOpcode(&opCodes[0x6b], Regs->L, Regs->E, 0, 4, LD);
    initOpcode(&opCodes[0x6c], Regs->L, Regs->H, 0, 4, LD);
    initOpcode(&opCodes[0x6d], Regs->L, Regs->L, 0, 4, LD);
    initOpcode(&opCodes[0x6e], Regs->L, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x6f], Regs->L, Regs->A, 0, 4, LD);
    initOpcode(&opCodes[0x70], Regs->HL, Regs->B, 1, 8, LD);
    initOpcode(&opCodes[0x71], Regs->HL, Regs->C, 1, 8, LD);
    initOpcode(&opCodes[0x72], Regs->HL, Regs->D, 1, 8, LD);
    initOpcode(&opCodes[0x73], Regs->HL, Regs->E, 1, 8, LD);
    initOpcode(&opCodes[0x74], Regs->HL, Regs->H, 1, 8, LD);
    initOpcode(&opCodes[0x75], Regs->HL, Regs->L, 1, 8, LD);
    initOpcode(&opCodes[0x76], 0, 0, 0, 4, HALT);
    initOpcode(&opCodes[0x77], Regs->HL, Regs->A, 1, 8, LD);
    initOpcode(&opCodes[0x78], Regs->A, Regs->B, 0, 4, LD);
    initOpcode(&opCodes[0x79], Regs->A, Regs->C, 0, 4, LD);
    initOpcode(&opCodes[0x7a], Regs->A, Regs->D, 0, 4, LD);
    initOpcode(&opCodes[0x7b], Regs->A, Regs->E, 0, 4, LD);
    initOpcode(&opCodes[0x7c], Regs->A, Regs->H, 0, 4, LD);
    initOpcode(&opCodes[0x7d], Regs->A, Regs->L, 0, 4, LD);
    initOpcode(&opCodes[0x7e], Regs->A, Regs->HL, 2, 8, LD);
    initOpcode(&opCodes[0x7f], Regs->A, Regs->A, 0, 4, LD);
    initOpcode(&opCodes[0x80], Regs->A, Regs->B, 0, 4, ADD);
    initOpcode(&opCodes[0x81], Regs->A, Regs->C, 0, 4, ADD);
    initOpcode(&opCodes[0x82], Regs->A, Regs->D, 0, 4, ADD);
    initOpcode(&opCodes[0x83], Regs->A, Regs->E, 0, 4, ADD);
    initOpcode(&opCodes[0x84], Regs->A, Regs->H, 0, 4, ADD);
    initOpcode(&opCodes[0x85], Regs->A, Regs->L, 0, 4, ADD);
    initOpcode(&opCodes[0x86], Regs->A, Regs->HL, 2, 8, ADD);
    initOpcode(&opCodes[0x87], Regs->A, Regs->A, 0, 4, ADD);
    initOpcode(&opCodes[0x88], Regs->A, Regs->B, 0, 4, ADC);
    initOpcode(&opCodes[0x89], Regs->A, Regs->C, 0, 4, ADC);
    initOpcode(&opCodes[0x8a], Regs->A, Regs->D, 0, 4, ADC);
    initOpcode(&opCodes[0x8b], Regs->A, Regs->E, 0, 4, ADC);
    initOpcode(&opCodes[0x8c], Regs->A, Regs->H, 0, 4, ADC);
    initOpcode(&opCodes[0x8d], Regs->A, Regs->L, 0, 4, ADC);
    initOpcode(&opCodes[0x8e], Regs->A, Regs->HL, 2, 8, ADC);
    initOpcode(&opCodes[0x8f], Regs->A, Regs->A, 0, 4, ADC);
    initOpcode(&opCodes[0x90], Regs->A, Regs->B, 0, 4, SUB);
    initOpcode(&opCodes[0x91], Regs->A, Regs->C, 0, 4, SUB);
    initOpcode(&opCodes[0x92], Regs->A, Regs->D, 0, 4, SUB);
    initOpcode(&opCodes[0x93], Regs->A, Regs->E, 0, 4, SUB);
    initOpcode(&opCodes[0x94], Regs->A, Regs->H, 0, 4, SUB);
    initOpcode(&opCodes[0x95], Regs->A, Regs->L, 0, 4, SUB);
    initOpcode(&opCodes[0x96], Regs->A, Regs->HL, 2, 8, SUB);
    initOpcode(&opCodes[0x97], Regs->A, Regs->A, 0, 4, SUB);
    initOpcode(&opCodes[0x98], Regs->A, Regs->B, 0, 4, SBC);
    initOpcode(&opCodes[0x99], Regs->A, Regs->C, 0, 4, SBC);
    initOpcode(&opCodes[0x9a], Regs->A, Regs->D, 0, 4, SBC);
    initOpcode(&opCodes[0x9b], Regs->A, Regs->E, 0, 4, SBC);
    initOpcode(&opCodes[0x9c], Regs->A, Regs->H, 0, 4, SBC);
    initOpcode(&opCodes[0x9d], Regs->A, Regs->L, 0, 4, SBC);
    initOpcode(&opCodes[0x9e], Regs->A, Regs->HL, 2, 8, SBC);
    initOpcode(&opCodes[0x9f], Regs->A, Regs->A, 0, 4, SBC);
    initOpcode(&opCodes[0xa0], Regs->A, Regs->B, 0, 4, AND);
    initOpcode(&opCodes[0xa1], Regs->A, Regs->C, 0, 4, AND);
    initOpcode(&opCodes[0xa2], Regs->A, Regs->D, 0, 4, AND);
    initOpcode(&opCodes[0xa3], Regs->A, Regs->E, 0, 4, AND);
    initOpcode(&opCodes[0xa4], Regs->A, Regs->H, 0, 4, AND);
    initOpcode(&opCodes[0xa5], Regs->A, Regs->L, 0, 4, AND);
    initOpcode(&opCodes[0xa6], Regs->A, Regs->HL, 2, 8, AND);
    initOpcode(&opCodes[0xa7], Regs->A, Regs->A, 0, 4, AND);
    initOpcode(&opCodes[0xa8], Regs->A, Regs->B, 0, 4, XOR);
    initOpcode(&opCodes[0xa9], Regs->A, Regs->C, 0, 4, XOR);
    initOpcode(&opCodes[0xaa], Regs->A, Regs->D, 0, 4, XOR);
    initOpcode(&opCodes[0xab], Regs->A, Regs->E, 0, 4, XOR);
    initOpcode(&opCodes[0xac], Regs->A, Regs->H, 0, 4, XOR);
    initOpcode(&opCodes[0xad], Regs->A, Regs->L, 0, 4, XOR);
    initOpcode(&opCodes[0xae], Regs->A, Regs->HL, 2, 8, XOR);
    initOpcode(&opCodes[0xaf], Regs->A, Regs->A, 0, 4, XOR);
    initOpcode(&opCodes[0xb0], Regs->A, Regs->B, 0, 4, OR);
    initOpcode(&opCodes[0xb1], Regs->A, Regs->C, 0, 4, OR);
    initOpcode(&opCodes[0xb2], Regs->A, Regs->D, 0, 4, OR);
    initOpcode(&opCodes[0xb3], Regs->A, Regs->E, 0, 4, OR);
    initOpcode(&opCodes[0xb4], Regs->A, Regs->H, 0, 4, OR);
    initOpcode(&opCodes[0xb5], Regs->A, Regs->L, 0, 4, OR);
    initOpcode(&opCodes[0xb6], Regs->A, Regs->HL, 2, 8, OR);
    initOpcode(&opCodes[0xb7], Regs->A, Regs->A, 0, 4, OR);
    initOpcode(&opCodes[0xb8], Regs->A, Regs->B, 0, 4, CP);
    initOpcode(&opCodes[0xb9], Regs->A, Regs->C, 0, 4, CP);
    initOpcode(&opCodes[0xba], Regs->A, Regs->D, 0, 4, CP);
    initOpcode(&opCodes[0xbb], Regs->A, Regs->E, 0, 4, CP);
    initOpcode(&opCodes[0xbc], Regs->A, Regs->H, 0, 4, CP);
    initOpcode(&opCodes[0xbd], Regs->A, Regs->L, 0, 4, CP);
    initOpcode(&opCodes[0xbe], Regs->A, Regs->HL, 2, 8, CP);
    initOpcode(&opCodes[0xbf], Regs->A, Regs->A, 0, 4, CP);
    initOpcode(&opCodes[0xc0], Regs->F, 0, 0, 20, RET);
    initOpcode(&opCodes[0xc1], Regs->BC, 0, 1, 12, POP);
    initOpcode(&opCodes[0xc2], Regs->F, &Regs->PC, 2, 16, JP);
    initOpcode(&opCodes[0xc3], &Regs->PC, 0, 1, 16, JP);
    initOpcode(&opCodes[0xc4], Regs->F, &Regs->PC, 2, 24, CALL);
    initOpcode(&opCodes[0xc5], Regs->BC, 0, 1, 16, PUSH);
    initOpcode(&opCodes[0xc6], Regs->A, &Regs->PC, 0, 8, ADD);
    initOpcode(&opCodes[0xc7], &Regs->PC, 0, 0, 16, RST);
    initOpcode(&opCodes[0xc8], Regs->F, 0, 0, 20, RET);
    initOpcode(&opCodes[0xc9], 0, 0, 0, 16, RET);
    initOpcode(&opCodes[0xca], Regs->F, &Regs->PC, 2, 16, JP);
    initOpcode(&opCodes[0xcb], 0, 0, 0, 4, PREFIX);
    initOpcode(&opCodes[0xcc], Regs->F, &Regs->PC, 2, 24, CALL);
    initOpcode(&opCodes[0xcd], &Regs->PC, 0, 1, 24, CALL);
    initOpcode(&opCodes[0xce], Regs->A, &Regs->PC, 0, 8, ADC);
    initOpcode(&opCodes[0xcf], &Regs->PC, 0, 0, 16, RST);
    initOpcode(&opCodes[0xd0], Regs->F, 0, 0, 20, RET);
    initOpcode(&opCodes[0xd1], Regs->DE, 0, 1, 12, POP);
    initOpcode(&opCodes[0xd2], Regs->F, &Regs->PC, 2, 16, JP);
    initOpcode(&opCodes[0xd3], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xd4], Regs->F, &Regs->PC, 2, 24, CALL);
    initOpcode(&opCodes[0xd5], Regs->DE, 0, 1, 16, PUSH);
    initOpcode(&opCodes[0xd6], Regs->A, &Regs->PC, 0, 8, SUB);
    initOpcode(&opCodes[0xd7], &Regs->PC, 0, 0, 16, RST);
    initOpcode(&opCodes[0xd8], Regs->C, 0, 0, 20, RET);
    initOpcode(&opCodes[0xd9], 0, 0, 0, 16, RETI);
    initOpcode(&opCodes[0xda], Regs->C, &Regs->PC, 2, 16, JP);
    initOpcode(&opCodes[0xdb], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xdc], Regs->C, &Regs->PC, 2, 24, CALL);
    initOpcode(&opCodes[0xdd], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xde], Regs->A, &Regs->PC, 0, 8, SBC);
    initOpcode(&opCodes[0xdf], &Regs->PC, 0, 0, 16, RST);
    initOpcode(&opCodes[0xe0], &Regs->PC, Regs->A, 0, 12, LDH);
    initOpcode(&opCodes[0xe1], Regs->HL, 0, 1, 12, POP);
    initOpcode(&opCodes[0xe2], Regs->C, Regs->A, 0, 8, LD);
    initOpcode(&opCodes[0xe3], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xe4], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xe5], Regs->HL, 0, 1, 16, PUSH);
    initOpcode(&opCodes[0xe6], Regs->A, &Regs->PC, 0, 8, AND);
    initOpcode(&opCodes[0xe7], &Regs->PC, 0, 0, 16, RST);
    initOpcode(&opCodes[0xe8], &Regs->PC, &Regs->PC, 1, 16, ADD);
    initOpcode(&opCodes[0xe9], Regs->HL, 0, 1, 4, JP);
    initOpcode(&opCodes[0xea], &Regs->PC, Regs->A, 1, 16, LD);
    initOpcode(&opCodes[0xeb], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xec], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xed], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xee], Regs->A, &Regs->PC, 0, 8, XOR);
    initOpcode(&opCodes[0xef], &Regs->PC, 0, 0, 16, RST);
    initOpcode(&opCodes[0xf0], Regs->A, &Regs->PC, 0, 12, LDH);
    initOpcode(&opCodes[0xf1], Regs->AF, 0, 1, 12, POP);
    initOpcode(&opCodes[0xf2], Regs->A, Regs->C, 0, 8, LD);
    initOpcode(&opCodes[0xf3], 0, 0, 0, 4, DI);
    initOpcode(&opCodes[0xf4], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xf5], Regs->AF, 0, 1, 16, PUSH);
    initOpcode(&opCodes[0xf6], Regs->A, &Regs->PC, 0, 8, OR);
    initOpcode(&opCodes[0xf7], &Regs->PC, 0, 0, 16, RST);
    initOpcode(&opCodes[0xf8], Regs->HL, &Regs->SP, 3, 12, LD);
    initOpcode(&opCodes[0xf9], &Regs->SP, Regs->HL, 3, 8, LD);
    initOpcode(&opCodes[0xfa], Regs->A, &Regs->PC, 2, 16, LD);
    initOpcode(&opCodes[0xfb], 0, 0, 0, 4, EI);
    initOpcode(&opCodes[0xfc], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xfd], 0, 0, 0, 4, ILLEGAL);
    initOpcode(&opCodes[0xfe], Regs->A, &Regs->PC, 0, 8, CP);
    initOpcode(&opCodes[0xff], &Regs->PC, 0, 0, 16, RST);

    // prefixed opcodes
    initOpcode(&CBopCodes[0x0], Regs->B, 0, 0, 8, RLC);
    initOpcode(&CBopCodes[0x1], Regs->C, 0, 0, 8, RLC);
    initOpcode(&CBopCodes[0x2], Regs->D, 0, 0, 8, RLC);
    initOpcode(&CBopCodes[0x3], Regs->E, 0, 0, 8, RLC);
    initOpcode(&CBopCodes[0x4], Regs->H, 0, 0, 8, RLC);
    initOpcode(&CBopCodes[0x5], Regs->L, 0, 0, 8, RLC);
    initOpcode(&CBopCodes[0x6], Regs->HL, 0, 1, 16, RLC);
    initOpcode(&CBopCodes[0x7], Regs->A, 0, 0, 8, RLC);
    initOpcode(&CBopCodes[0x8], Regs->B, 0, 0, 8, RRC);
    initOpcode(&CBopCodes[0x9], Regs->C, 0, 0, 8, RRC);
    initOpcode(&CBopCodes[0xa], Regs->D, 0, 0, 8, RRC);
    initOpcode(&CBopCodes[0xb], Regs->E, 0, 0, 8, RRC);
    initOpcode(&CBopCodes[0xc], Regs->H, 0, 0, 8, RRC);
    initOpcode(&CBopCodes[0xd], Regs->L, 0, 0, 8, RRC);
    initOpcode(&CBopCodes[0xe], Regs->HL, 0, 1, 16, RRC);
    initOpcode(&CBopCodes[0xf], Regs->A, 0, 0, 8, RRC);
    initOpcode(&CBopCodes[0x10], Regs->B, 0, 0, 8, RL);
    initOpcode(&CBopCodes[0x11], Regs->C, 0, 0, 8, RL);
    initOpcode(&CBopCodes[0x12], Regs->D, 0, 0, 8, RL);
    initOpcode(&CBopCodes[0x13], Regs->E, 0, 0, 8, RL);
    initOpcode(&CBopCodes[0x14], Regs->H, 0, 0, 8, RL);
    initOpcode(&CBopCodes[0x15], Regs->L, 0, 0, 8, RL);
    initOpcode(&CBopCodes[0x16], Regs->HL, 0, 1, 16, RL);
    initOpcode(&CBopCodes[0x17], Regs->A, 0, 0, 8, RL);
    initOpcode(&CBopCodes[0x18], Regs->B, 0, 0, 8, RR);
    initOpcode(&CBopCodes[0x19], Regs->C, 0, 0, 8, RR);
    initOpcode(&CBopCodes[0x1a], Regs->D, 0, 0, 8, RR);
    initOpcode(&CBopCodes[0x1b], Regs->E, 0, 0, 8, RR);
    initOpcode(&CBopCodes[0x1c], Regs->H, 0, 0, 8, RR);
    initOpcode(&CBopCodes[0x1d], Regs->L, 0, 0, 8, RR);
    initOpcode(&CBopCodes[0x1e], Regs->HL, 0, 1, 16, RR);
    initOpcode(&CBopCodes[0x1f], Regs->A, 0, 0, 8, RR);
    initOpcode(&CBopCodes[0x20], Regs->B, 0, 0, 8, SLA);
    initOpcode(&CBopCodes[0x21], Regs->C, 0, 0, 8, SLA);
    initOpcode(&CBopCodes[0x22], Regs->D, 0, 0, 8, SLA);
    initOpcode(&CBopCodes[0x23], Regs->E, 0, 0, 8, SLA);
    initOpcode(&CBopCodes[0x24], Regs->H, 0, 0, 8, SLA);
    initOpcode(&CBopCodes[0x25], Regs->L, 0, 0, 8, SLA);
    initOpcode(&CBopCodes[0x26], Regs->HL, 0, 1, 16, SLA);
    initOpcode(&CBopCodes[0x27], Regs->A, 0, 0, 8, SLA);
    initOpcode(&CBopCodes[0x28], Regs->B, 0, 0, 8, SRA);
    initOpcode(&CBopCodes[0x29], Regs->C, 0, 0, 8, SRA);
    initOpcode(&CBopCodes[0x2a], Regs->D, 0, 0, 8, SRA);
    initOpcode(&CBopCodes[0x2b], Regs->E, 0, 0, 8, SRA);
    initOpcode(&CBopCodes[0x2c], Regs->H, 0, 0, 8, SRA);
    initOpcode(&CBopCodes[0x2d], Regs->L, 0, 0, 8, SRA);
    initOpcode(&CBopCodes[0x2e], Regs->HL, 0, 1, 16, SRA);
    initOpcode(&CBopCodes[0x2f], Regs->A, 0, 0, 8, SRA);
    initOpcode(&CBopCodes[0x30], Regs->B, 0, 0, 8, SWAP);
    initOpcode(&CBopCodes[0x31], Regs->C, 0, 0, 8, SWAP);
    initOpcode(&CBopCodes[0x32], Regs->D, 0, 0, 8, SWAP);
    initOpcode(&CBopCodes[0x33], Regs->E, 0, 0, 8, SWAP);
    initOpcode(&CBopCodes[0x34], Regs->H, 0, 0, 8, SWAP);
    initOpcode(&CBopCodes[0x35], Regs->L, 0, 0, 8, SWAP);
    initOpcode(&CBopCodes[0x36], Regs->HL, 0, 1, 16, SWAP);
    initOpcode(&CBopCodes[0x37], Regs->A, 0, 0, 8, SWAP);
    initOpcode(&CBopCodes[0x38], Regs->B, 0, 0, 8, SRL);
    initOpcode(&CBopCodes[0x39], Regs->C, 0, 0, 8, SRL);
    initOpcode(&CBopCodes[0x3a], Regs->D, 0, 0, 8, SRL);
    initOpcode(&CBopCodes[0x3b], Regs->E, 0, 0, 8, SRL);
    initOpcode(&CBopCodes[0x3c], Regs->H, 0, 0, 8, SRL);
    initOpcode(&CBopCodes[0x3d], Regs->L, 0, 0, 8, SRL);
    initOpcode(&CBopCodes[0x3e], Regs->HL, 0, 1, 16, SRL);
    initOpcode(&CBopCodes[0x3f], Regs->A, 0, 0, 8, SRL);
    initOpcode(&CBopCodes[0x40], Regs->B,  &bitSets[0], 0, 8, BIT);
    initOpcode(&CBopCodes[0x41], Regs->C,  &bitSets[0], 0, 8, BIT);
    initOpcode(&CBopCodes[0x42], Regs->D,  &bitSets[0], 0, 8, BIT);
    initOpcode(&CBopCodes[0x43], Regs->E,  &bitSets[0], 0, 8, BIT);
    initOpcode(&CBopCodes[0x44], Regs->H,  &bitSets[0], 0, 8, BIT);
    initOpcode(&CBopCodes[0x45], Regs->L,  &bitSets[0], 0, 8, BIT);
    initOpcode(&CBopCodes[0x46], Regs->HL, &bitSets[0], 2, 12, BIT);
    initOpcode(&CBopCodes[0x47], Regs->A, &bitSets[0], 0, 8, BIT);
    initOpcode(&CBopCodes[0x48], Regs->B, &bitSets[1], 0, 8, BIT);
    initOpcode(&CBopCodes[0x49], Regs->C, &bitSets[1], 0, 8, BIT);
    initOpcode(&CBopCodes[0x4a], Regs->D, &bitSets[1], 0, 8, BIT);
    initOpcode(&CBopCodes[0x4b], Regs->E, &bitSets[1], 0, 8, BIT);
    initOpcode(&CBopCodes[0x4c], Regs->H, &bitSets[1], 0, 8, BIT);
    initOpcode(&CBopCodes[0x4d], Regs->L, &bitSets[1], 0, 8, BIT);
    initOpcode(&CBopCodes[0x4e], Regs->HL,&bitSets[1], 2, 12, BIT);
    initOpcode(&CBopCodes[0x4f], Regs->A, &bitSets[1], 0, 8, BIT);
    initOpcode(&CBopCodes[0x50], Regs->B, &bitSets[2], 0, 8, BIT);
    initOpcode(&CBopCodes[0x51], Regs->C, &bitSets[2], 0, 8, BIT);
    initOpcode(&CBopCodes[0x52], Regs->D, &bitSets[2], 0, 8, BIT);
    initOpcode(&CBopCodes[0x53], Regs->E, &bitSets[2], 0, 8, BIT);
    initOpcode(&CBopCodes[0x54], Regs->H, &bitSets[2], 0, 8, BIT);
    initOpcode(&CBopCodes[0x55], Regs->L, &bitSets[2], 0, 8, BIT);
    initOpcode(&CBopCodes[0x56], Regs->HL, &bitSets[2], 2, 12, BIT);
    initOpcode(&CBopCodes[0x57], Regs->A, &bitSets[2], 0, 8, BIT);
    initOpcode(&CBopCodes[0x58], Regs->B, &bitSets[3], 0, 8, BIT);
    initOpcode(&CBopCodes[0x59], Regs->C, &bitSets[3], 0, 8, BIT);
    initOpcode(&CBopCodes[0x5a], Regs->D, &bitSets[3], 0, 8, BIT);
    initOpcode(&CBopCodes[0x5b], Regs->E, &bitSets[3], 0, 8, BIT);
    initOpcode(&CBopCodes[0x5c], Regs->H, &bitSets[3], 0, 8, BIT);
    initOpcode(&CBopCodes[0x5d], Regs->L, &bitSets[3], 0, 8, BIT);
    initOpcode(&CBopCodes[0x5e], Regs->HL, &bitSets[3], 2, 12, BIT);
    initOpcode(&CBopCodes[0x5f], Regs->A, &bitSets[3], 0, 8, BIT);
    initOpcode(&CBopCodes[0x60], Regs->B, &bitSets[4], 0, 8, BIT);
    initOpcode(&CBopCodes[0x61], Regs->C, &bitSets[4], 0, 8, BIT);
    initOpcode(&CBopCodes[0x62], Regs->D, &bitSets[4], 0, 8, BIT);
    initOpcode(&CBopCodes[0x63], Regs->E, &bitSets[4], 0, 8, BIT);
    initOpcode(&CBopCodes[0x64], Regs->H, &bitSets[4], 0, 8, BIT);
    initOpcode(&CBopCodes[0x65], Regs->L, &bitSets[4], 0, 8, BIT);
    initOpcode(&CBopCodes[0x66], Regs->HL, &bitSets[4], 2, 12, BIT);
    initOpcode(&CBopCodes[0x67], Regs->A, &bitSets[4], 0, 8, BIT);
    initOpcode(&CBopCodes[0x68], Regs->B, &bitSets[5], 0, 8, BIT);
    initOpcode(&CBopCodes[0x69], Regs->C, &bitSets[5], 0, 8, BIT);
    initOpcode(&CBopCodes[0x6a], Regs->D, &bitSets[5], 0, 8, BIT);
    initOpcode(&CBopCodes[0x6b], Regs->E, &bitSets[5], 0, 8, BIT);
    initOpcode(&CBopCodes[0x6c], Regs->H, &bitSets[5], 0, 8, BIT);
    initOpcode(&CBopCodes[0x6d], Regs->L, &bitSets[5], 0, 8, BIT);
    initOpcode(&CBopCodes[0x6e], Regs->HL, &bitSets[5], 2, 12, BIT);
    initOpcode(&CBopCodes[0x6f], Regs->A, &bitSets[5], 0, 8, BIT);
    initOpcode(&CBopCodes[0x70], Regs->B, &bitSets[6], 0, 8, BIT);
    initOpcode(&CBopCodes[0x71], Regs->C, &bitSets[6], 0, 8, BIT);
    initOpcode(&CBopCodes[0x72], Regs->D, &bitSets[6], 0, 8, BIT);
    initOpcode(&CBopCodes[0x73], Regs->E, &bitSets[6], 0, 8, BIT);
    initOpcode(&CBopCodes[0x74], Regs->H, &bitSets[6], 0, 8, BIT);
    initOpcode(&CBopCodes[0x75], Regs->L, &bitSets[6], 0, 8, BIT);
    initOpcode(&CBopCodes[0x76], Regs->HL, &bitSets[6], 2, 12, BIT);
    initOpcode(&CBopCodes[0x77], Regs->A, &bitSets[6], 0, 8, BIT);
    initOpcode(&CBopCodes[0x78], Regs->B, &bitSets[7], 0, 8, BIT);
    initOpcode(&CBopCodes[0x79], Regs->C, &bitSets[7], 0, 8, BIT);
    initOpcode(&CBopCodes[0x7a], Regs->D, &bitSets[7], 0, 8, BIT);
    initOpcode(&CBopCodes[0x7b], Regs->E, &bitSets[7], 0, 8, BIT);
    initOpcode(&CBopCodes[0x7c], Regs->H, &bitSets[7], 0, 8, BIT);
    initOpcode(&CBopCodes[0x7d], Regs->L, &bitSets[7], 0, 8, BIT);
    initOpcode(&CBopCodes[0x7e], Regs->HL, &bitSets[7], 2, 12, BIT);
    initOpcode(&CBopCodes[0x7f], Regs->A, &bitSets[7], 0, 8, BIT);
    initOpcode(&CBopCodes[0x80], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x81], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x82], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x83], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x84], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x85], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x86], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0x87], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x88], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x89], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x8a], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x8b], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x8c], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x8d], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x8e], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0x8f], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x90], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x91], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x92], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x93], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x94], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x95], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x96], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0x97], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x98], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x99], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x9a], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x9b], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x9c], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x9d], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0x9e], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0x9f], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa0], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa1], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa2], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa3], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa4], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa5], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa6], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0xa7], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa8], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xa9], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xaa], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xab], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xac], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xad], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xae], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0xaf], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb0], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb1], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb2], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb3], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb4], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb5], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb6], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0xb7], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb8], Regs->B, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xb9], Regs->C, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xba], Regs->D, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xbb], Regs->E, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xbc], Regs->H, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xbd], Regs->L, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xbe], Regs->HL, 0, 2, 16, RES);
    initOpcode(&CBopCodes[0xbf], Regs->A, 0, 0, 8, RES);
    initOpcode(&CBopCodes[0xc0], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc1], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc2], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc3], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc4], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc5], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc6], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xc7], Regs->A, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc8], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xc9], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xca], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xcb], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xcc], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xcd], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xce], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xcf], Regs->A, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd0], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd1], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd2], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd3], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd4], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd5], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd6], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xd7], Regs->A, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd8], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xd9], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xda], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xdb], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xdc], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xdd], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xde], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xdf], Regs->A, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe0], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe1], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe2], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe3], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe4], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe5], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe6], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xe7], Regs->A, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe8], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xe9], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xea], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xeb], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xec], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xed], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xee], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xef], Regs->A, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf0], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf1], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf2], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf3], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf4], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf5], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf6], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xf7], Regs->A, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf8], Regs->B, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xf9], Regs->C, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xfa], Regs->D, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xfb], Regs->E, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xfc], Regs->H, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xfd], Regs->L, 0, 0, 8, SET);
    initOpcode(&CBopCodes[0xfe], Regs->HL, 0, 2, 16, SET);
    initOpcode(&CBopCodes[0xff], Regs->A, 0, 0, 8, SET);
}

void executeOpcode(opCode *operation, System *sys)
{
    if (operation->reg2 == &sys->regs.PC)
    {
        operation->reg2 = sys->regs.PC+1;
    }
    printf("Executing mnemonic %d\n", operation->mnemonic);
    switch (operation->mnemonic)
    {
    case NOP:
        sys->cycles += 4;
        break;
    case LD:
        printf("LOAD\n");
        Load(operation, sys);
        break;
    case LDD:
        LoadDec(operation, sys);
        break;
    case JRR:
        JumpConditionReset(operation, sys);
        break;
    case JRS:
        JumpConditionSet(operation, sys);
        break;
    case XOR:
        ExclusiveOR(operation, sys);
        break;
    case BIT:
        testBit(operation, sys);
        break;
    default:
        printf("Instruction %d not found or implemented!\n", operation->mnemonic); // Code for handling illegal opcode
        exit(1);
        break;
    }
}

// If the Nth bit at the given register is 0, set the Z flag to 1
void testBit(opCode *operation, System *sys){
    printf("Testing bit %x\n", sys->regs.r[H]);
    if (!(*(uint8_t*)operation->reg1 & *(uint8_t*)operation->reg2))
    {
        printf("%d,,,%d", *(uint8_t*)operation->reg2, *operation->reg2);
        sys->regs.r[F] |= bitSets[Z];
    }
    sys->regs.r[F] |= bitSets[Hf];
    sys->regs.r[F] &= iBitSets[N];
    printf("Flag: %d\n", sys->regs.r[F]);
    sys->regs.PC += 1;
}


// Does the jump happen from the adress of the instruction or the adress of the data??
void JumpConditionReset(opCode* operation, System* sys)
{
    sys->regs.PC += 2;
    printf("JZR");
    if (!(sys->regs.r[F] & *(operation->reg2)))
    {
        printf("Jumped from PC: %d", sys->regs.PC-sys->mem.BOOT_ROM);
        sys->regs.PC += *(int8_t*)(sys->regs.PC - 1);
        printf("to PC: %d\n", sys->regs.PC-sys->mem.BOOT_ROM);
    }
    else
    {
        printf(" failed\n");
        
    }
}

void JumpConditionSet(opCode* operation, System* sys)
{
    printf("jzS");
    if (sys->regs.r[F] & *(operation->reg2))
    {
        printf("Jumped from PC: %d", sys->regs.PC-sys->mem.BOOT_ROM);
        sys->regs.PC += *(int8_t*)(sys->regs.PC + 1);
        printf("to PC: %d\n", sys->regs.PC-sys->mem.BOOT_ROM);
    }
    else
    {
        printf(" failed\n");
        sys->regs.PC += 2;
    }
}

void ExclusiveOR(opCode *operation, System *sys)
{
    uint8_t *input = operation->reg2;

    sys->regs.r[A] == sys->regs.A ^ *input;

    if (sys->regs.r[A] == 0)
        sys->regs.r[F] &= bitSets[Z];

    sys->regs.PC += 1;
}

void LoadDec(opCode *operation, System *sys)
{
    printf("Load decrement store\n");
    sys->mem.memory[*sys->regs.HL] = sys->regs.r[A];
    *sys->regs.HL -= 1;
    sys->regs.PC += 1;
}

void Load(opCode *operation, System *sys)
{

    switch (operation->iSize) {
    case 0: // Two 8 bit operators
        printf("LOAD 8x8 NOT IMPLEMENTED\n");
        exit(1);
        break;
    case 1: // Reg1 is 16 bit reg2 is 8 bit
        printf("LOAD 16x8 NOT IMPLEMENTED\n");
        break;
    case 2: // reg2 is 8 bit reg1 is 16 bit
        printf("LOAD 8x16 NOT IMPLEMENTED\n");

        break;
    case 3: // Both regs 16bit

        *(operation->reg1) = *(operation->reg2);
        printf("%x\n", *(operation->reg1));

        if (operation->reg2 == sys->regs.PC+1) // We need to increment PC by 2 to get the next instruction if we load an immediate
        {
            sys->regs.PC += 3;
        } else {
            sys->regs.PC += 1;
        }
        break;
    }
}
