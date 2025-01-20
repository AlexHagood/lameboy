#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sys.h"
#include "operations.h"

int between(uint8_t val, uint8_t min, uint8_t max)
{
    return val >= min && val <= max;
}

void executeOperation(System *sys)
{
    printf("OP: %x, Address: %x\n", *sys->regs.PC, (uint16_t)(sys->regs.PC - sys->mem.memory));

    if (*sys->regs.PC == 0x67)
    {
        printf("Halt\n");
        exit(1);
    }

    if (between(*sys->regs.PC, 0x40, 0x7F)){
        load8registers(sys);
        return;
    }

    switch (*sys->regs.PC)
    {
    case 0x0:
        puts("Operation 0x0, NOP(0)(0) not implemented!");
        exit(1);
        break;
    case 0x1:
        load16(&sys->regs.BC, *(++sys->regs.PC));
        sys->regs.PC += 2;
        break;
    case 0x2:
        puts("Operation 0x2, LD(Regs->BC)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x3:
        puts("Operation 0x3, INC(Regs->BC)(0) not implemented!");
        exit(1);
        break;
    case 0x4:
        inc(&sys->regs.B, sys);
        break;
    case 0x5:
        puts("Operation 0x5, DEC(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x6:
        load8(&sys->regs.B, *(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0x7:
        puts("Operation 0x7, RLCA(0)(0) not implemented!");
        exit(1);
        break;
    case 0x8:
        puts("Operation 0x8, LD(Regs->SP)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0x9:
        puts("Operation 0x9, ADD(Regs->HL)(Regs->BC) not implemented!");
        exit(1);
        break;
    case 0xa:
        load8(&sys->regs.A, sys->mem.memory[sys->regs.BC], sys);
        break;
    case 0xb:
        puts("Operation 0xb, DEC(Regs->BC)(0) not implemented!");
        exit(1);
        break;
    case 0xc:
        inc(&sys->regs.C, sys);
        break;
    case 0xd:
        puts("Operation 0xd, DEC(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0xe:
        load8(&sys->regs.C, *(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0xf:
        puts("Operation 0xf, RRCA(0)(0) not implemented!");
        exit(1);
        break;
    case 0x10:
        puts("Operation 0x10, STOP(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0x11:
        load16(&sys->regs.SP, *(sys->regs.PC + 1));
        sys->regs.PC += 3;
        break;
    case 0x12:
        puts("Operation 0x12, LD(Regs->DE)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x13:
        puts("Operation 0x13, INC(Regs->DE)(0) not implemented!");
        exit(1);
        break;
    case 0x14:
        inc(&sys->regs.D, sys);
        break;
    case 0x15:
        puts("Operation 0x15, DEC(Regs->D)(0) not implemented!");
        exit(1);
        break;
    case 0x16:
        load8(&sys->regs.D, *(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0x17:
        puts("Operation 0x17, RLA(0)(0) not implemented!");
        exit(1);
        break;
    case 0x18:
        puts("Operation 0x18, JR(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0x19:
        puts("Operation 0x19, ADD(Regs->HL)(Regs->DE) not implemented!");
        exit(1);
        break;
    case 0x1a:
        load8(&sys->regs.A, sys->mem.memory[sys->regs.DE], sys);
        break;
    case 0x1b:
        puts("Operation 0x1b, DEC(Regs->DE)(0) not implemented!");
        exit(1);
        break;
    case 0x1c:
        inc(&sys->regs.E, sys);
        break;
    case 0x1d:
        puts("Operation 0x1d, DEC(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x1e:
        load8(&sys->regs.E, *(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0x1f:
        puts("Operation 0x1f, RRA(0)(0) not implemented!");
        exit(1);
        break;
    case 0x20:
        jr_conditional(sys);
        break;
    case 0x21:
        printf("%d\n", *((uint16_t *)(sys->regs.PC + 1)));
        load16(&sys->regs.HL, *(uint16_t *)(sys->regs.PC + 1));
        sys->regs.PC += 3;
        break;
    case 0x22:
        puts("Operation 0x22, LD(Regs->HL)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x23:
        puts("Operation 0x23, INC(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x24:
        inc(&sys->regs.H, sys);
        break;
    case 0x25:
        puts("Operation 0x25, DEC(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x26:
        load8(&sys->regs.H, *(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0x27:
        puts("Operation 0x27, DAA(0)(0) not implemented!");
        exit(1);
        break;
    case 0x28:
        jr_conditional(sys);
        break;
    case 0x29:
        puts("Operation 0x29, ADD(Regs->HL)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x2a:
        load8(&sys->regs.A, sys->mem.memory[sys->regs.HL], sys);
        sys->regs.HL += 1;
        break;
    case 0x2b:
        puts("Operation 0x2b, DEC(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x2c:
        inc(&sys->regs.L, sys);
        break;
    case 0x2d:
        puts("Operation 0x2d, DEC(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x2e:
        load8(&sys->regs.L, *(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0x2f:
        puts("Operation 0x2f, CPL(0)(0) not implemented!");
        exit(1);
        break;
    case 0x30:
        jr_conditional(sys);
        break;
    case 0x31:
        load16(&sys->regs.SP, *(sys->regs.PC + 1));
        sys->regs.PC += 3;
        break;
    case 0x32:
        ldd(sys);
        break;
    case 0x33:
        puts("Operation 0x33, INC(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0x34:
        inc(&sys->mem.memory[sys->regs.HL], sys);
        break;
    case 0x35:
        puts("Operation 0x35, DEC(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x36:
        puts("Operation 0x36, LD(Regs->HL)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0x37:
        puts("Operation 0x37, SCF(0)(0) not implemented!");
        exit(1);
        break;
    case 0x38:
        jr_conditional(sys);
        break;
    case 0x39:
        puts("Operation 0x39, ADD(Regs->HL)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0x3a:
        ldd(sys);
        break;
    case 0x3b:
        puts("Operation 0x3b, DEC(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0x3c:
        inc(&sys->regs.A, sys);
        break;
    case 0x3d:
        puts("Operation 0x3d, DEC(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x3e:
        load8(&sys->regs.A, *(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0x3f:
        puts("Operation 0x3f, CCF(0)(0) not implemented!");
        exit(1);
        break;
    case 0x80:
        puts("Operation 0x80, ADD(Regs->A)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x81:
        puts("Operation 0x81, ADD(Regs->A)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x82:
        puts("Operation 0x82, ADD(Regs->A)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x83:
        puts("Operation 0x83, ADD(Regs->A)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x84:
        puts("Operation 0x84, ADD(Regs->A)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x85:
        puts("Operation 0x85, ADD(Regs->A)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x86:
        puts("Operation 0x86, ADD(Regs->A)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x87:
        puts("Operation 0x87, ADD(Regs->A)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x88:
        puts("Operation 0x88, ADC(Regs->A)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x89:
        puts("Operation 0x89, ADC(Regs->A)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x8a:
        puts("Operation 0x8a, ADC(Regs->A)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x8b:
        puts("Operation 0x8b, ADC(Regs->A)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x8c:
        puts("Operation 0x8c, ADC(Regs->A)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x8d:
        puts("Operation 0x8d, ADC(Regs->A)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x8e:
        puts("Operation 0x8e, ADC(Regs->A)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x8f:
        puts("Operation 0x8f, ADC(Regs->A)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x90:
        puts("Operation 0x90, SUB(Regs->A)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x91:
        puts("Operation 0x91, SUB(Regs->A)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x92:
        puts("Operation 0x92, SUB(Regs->A)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x93:
        puts("Operation 0x93, SUB(Regs->A)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x94:
        puts("Operation 0x94, SUB(Regs->A)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x95:
        puts("Operation 0x95, SUB(Regs->A)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x96:
        puts("Operation 0x96, SUB(Regs->A)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x97:
        puts("Operation 0x97, SUB(Regs->A)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x98:
        puts("Operation 0x98, SBC(Regs->A)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x99:
        puts("Operation 0x99, SBC(Regs->A)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x9a:
        puts("Operation 0x9a, SBC(Regs->A)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x9b:
        puts("Operation 0x9b, SBC(Regs->A)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x9c:
        puts("Operation 0x9c, SBC(Regs->A)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x9d:
        puts("Operation 0x9d, SBC(Regs->A)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x9e:
        puts("Operation 0x9e, SBC(Regs->A)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x9f:
        puts("Operation 0x9f, SBC(Regs->A)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xa0:
        puts("Operation 0xa0, AND(Regs->A)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xa1:
        puts("Operation 0xa1, AND(Regs->A)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xa2:
        puts("Operation 0xa2, AND(Regs->A)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xa3:
        puts("Operation 0xa3, AND(Regs->A)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xa4:
        puts("Operation 0xa4, AND(Regs->A)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xa5:
        puts("Operation 0xa5, AND(Regs->A)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xa6:
        puts("Operation 0xa6, AND(Regs->A)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xa7:
        puts("Operation 0xa7, AND(Regs->A)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xa8:
        xorA(sys->regs.B, sys);
        break;
    case 0xa9:
        xorA(sys->regs.C, sys);
        break;
    case 0xaa:
        xorA(sys->regs.D, sys);
        break;
    case 0xab:
        xorA(sys->regs.E, sys);
        break;
    case 0xac:
        xorA(sys->regs.H, sys);
        break;
    case 0xad:
        xorA(sys->regs.L, sys);
        break;
    case 0xae:
        xorA(sys->mem.memory[sys->regs.HL], sys);
        break;
    case 0xaf:
        xorA(sys->regs.A, sys);
        break;
    case 0xb0:
        puts("Operation 0xb0, OR(Regs->A)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xb1:
        puts("Operation 0xb1, OR(Regs->A)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xb2:
        puts("Operation 0xb2, OR(Regs->A)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xb3:
        puts("Operation 0xb3, OR(Regs->A)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xb4:
        puts("Operation 0xb4, OR(Regs->A)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xb5:
        puts("Operation 0xb5, OR(Regs->A)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xb6:
        puts("Operation 0xb6, OR(Regs->A)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xb7:
        puts("Operation 0xb7, OR(Regs->A)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xb8:
        puts("Operation 0xb8, CP(Regs->A)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xb9:
        puts("Operation 0xb9, CP(Regs->A)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xba:
        puts("Operation 0xba, CP(Regs->A)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xbb:
        puts("Operation 0xbb, CP(Regs->A)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xbc:
        puts("Operation 0xbc, CP(Regs->A)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xbd:
        puts("Operation 0xbd, CP(Regs->A)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xbe:
        puts("Operation 0xbe, CP(Regs->A)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xbf:
        puts("Operation 0xbf, CP(Regs->A)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xc0:
        puts("Operation 0xc0, RET(Regs->NZ)(0) not implemented!");
        exit(1);
        break;
    case 0xc1:
        puts("Operation 0xc1, POP(Regs->BC)(0) not implemented!");
        exit(1);
        break;
    case 0xc2:
        puts("Operation 0xc2, JP(Regs->NZ)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xc3:
        puts("Operation 0xc3, JP(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xc4:
        puts("Operation 0xc4, CALL(Regs->NZ)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xc5:
        puts("Operation 0xc5, PUSH(Regs->BC)(0) not implemented!");
        exit(1);
        break;
    case 0xc6:
        puts("Operation 0xc6, ADD(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xc7:
        puts("Operation 0xc7, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xc8:
        puts("Operation 0xc8, RET(Regs->Z)(0) not implemented!");
        exit(1);
        break;
    case 0xc9:
        puts("Operation 0xc9, RET(0)(0) not implemented!");
        exit(1);
        break;
    case 0xca:
        puts("Operation 0xca, JP(Regs->Z)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xcb:
        puts("Operation 0xcb, PREFIX(0)(0) not implemented!");
        exit(1);
        break;
    case 0xcc:
        puts("Operation 0xcc, CALL(Regs->Z)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xcd:
        puts("Operation 0xcd, CALL(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xce:
        puts("Operation 0xce, ADC(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xcf:
        puts("Operation 0xcf, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xd0:
        puts("Operation 0xd0, RET(Regs->NC)(0) not implemented!");
        exit(1);
        break;
    case 0xd1:
        puts("Operation 0xd1, POP(Regs->DE)(0) not implemented!");
        exit(1);
        break;
    case 0xd2:
        puts("Operation 0xd2, JP(Regs->NC)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xd3:
        puts("Operation 0xd3, ILLEGAL_D3(0)(0) not implemented!");
        exit(1);
        break;
    case 0xd4:
        puts("Operation 0xd4, CALL(Regs->NC)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xd5:
        puts("Operation 0xd5, PUSH(Regs->DE)(0) not implemented!");
        exit(1);
        break;
    case 0xd6:
        puts("Operation 0xd6, SUB(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xd7:
        puts("Operation 0xd7, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xd8:
        puts("Operation 0xd8, RET(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0xd9:
        puts("Operation 0xd9, RETI(0)(0) not implemented!");
        exit(1);
        break;
    case 0xda:
        puts("Operation 0xda, JP(Regs->C)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xdb:
        puts("Operation 0xdb, ILLEGAL_DB(0)(0) not implemented!");
        exit(1);
        break;
    case 0xdc:
        puts("Operation 0xdc, CALL(Regs->C)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xdd:
        puts("Operation 0xdd, ILLEGAL_DD(0)(0) not implemented!");
        exit(1);
        break;
    case 0xde:
        puts("Operation 0xde, SBC(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xdf:
        puts("Operation 0xdf, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xe0:
        load8(&sys->mem.memory[0xFF00 + *(sys->regs.PC + 1)], sys->regs.A, sys);
        sys->regs.PC += 1;
        break;
    case 0xe1:
        puts("Operation 0xe1, POP(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0xe2:
        load8(&sys->mem.memory[0xFF00 + sys->regs.C], sys->regs.A, sys);
        break;
    case 0xe3:
        puts("Operation 0xe3, ILLEGAL_E3(0)(0) not implemented!");
        exit(1);
        break;
    case 0xe4:
        puts("Operation 0xe4, ILLEGAL_E4(0)(0) not implemented!");
        exit(1);
        break;
    case 0xe5:
        puts("Operation 0xe5, PUSH(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0xe6:
        puts("Operation 0xe6, AND(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xe7:
        puts("Operation 0xe7, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xe8:
        puts("Operation 0xe8, ADD(Regs->SP)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xe9:
        puts("Operation 0xe9, JP(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0xea:
        puts("Operation 0xea, LD(Regs->SP)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xeb:
        puts("Operation 0xeb, ILLEGAL_EB(0)(0) not implemented!");
        exit(1);
        break;
    case 0xec:
        puts("Operation 0xec, ILLEGAL_EC(0)(0) not implemented!");
        exit(1);
        break;
    case 0xed:
        puts("Operation 0xed, ILLEGAL_ED(0)(0) not implemented!");
        exit(1);
        break;
    case 0xee:
        xorA(*(sys->regs.PC + 1), sys);
        sys->regs.PC += 1;
        break;
    case 0xef:
        puts("Operation 0xef, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xf0:
        load8(&sys->regs.A, sys->mem.memory[0xFF00 + *(sys->regs.PC + 1)], sys);
        sys->regs.PC += 1;
        break;
    case 0xf1:
        puts("Operation 0xf1, POP(Regs->AF)(0) not implemented!");
        exit(1);
        break;
    case 0xf2:
        load8(&sys->regs.A, sys->mem.memory[0xFF00 + sys->regs.C], sys);
        break;
    case 0xf3:
        puts("Operation 0xf3, DI(0)(0) not implemented!");
        exit(1);
        break;
    case 0xf4:
        puts("Operation 0xf4, ILLEGAL_F4(0)(0) not implemented!");
        exit(1);
        break;
    case 0xf5:
        puts("Operation 0xf5, PUSH(Regs->AF)(0) not implemented!");
        exit(1);
        break;
    case 0xf6:
        puts("Operation 0xf6, OR(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xf7:
        puts("Operation 0xf7, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    case 0xf8:
        puts("Operation 0xf8, LD(Regs->HL)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xf9:
        puts("Operation 0xf9, LD(Regs->SP)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xfa:
        puts("Operation 0xfa, LD(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xfb:
        puts("Operation 0xfb, EI(0)(0) not implemented!");
        exit(1);
        break;
    case 0xfc:
        puts("Operation 0xfc, ILLEGAL_FC(0)(0) not implemented!");
        exit(1);
        break;
    case 0xfd:
        puts("Operation 0xfd, ILLEGAL_FD(0)(0) not implemented!");
        exit(1);
        break;
    case 0xfe:
        puts("Operation 0xfe, CP(Regs->A)(Regs->SP) not implemented!");
        exit(1);
        break;
    case 0xff:
        puts("Operation 0xff, RST(Regs->SP)(0) not implemented!");
        exit(1);
        break;
    }
}

void executePrefixOperation(System *sys)
{
    printf("OP: %x, Address: %d\n", *sys->regs.PC, (uint16_t)(sys->regs.PC - sys->mem.memory));
    uint8_t op = *sys->regs.PC;

    if (between(op, 0x40, 0x7f))
    {
        bit(sys);
        return;
    }

    switch (*sys->regs.PC)
    {

    case 0x0:
        puts("Operation CB 0x0, RLC(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x1:
        puts("Operation CB 0x1, RLC(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0x2:
        puts("Operation CB 0x2, RLC(Regs->D)(0) not implemented!");
        exit(1);
        break;
    case 0x3:
        puts("Operation CB 0x3, RLC(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x4:
        puts("Operation CB 0x4, RLC(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x5:
        puts("Operation CB 0x5, RLC(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x6:
        puts("Operation CB 0x6, RLC(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x7:
        puts("Operation CB 0x7, RLC(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x8:
        puts("Operation CB 0x8, RRC(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x9:
        puts("Operation CB 0x9, RRC(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0xa:
        puts("Operation CB 0xa, RRC(Regs->D)(0) not implemented!");
        exit(1);
        break;
    case 0xb:
        puts("Operation CB 0xb, RRC(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0xc:
        puts("Operation CB 0xc, RRC(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0xd:
        puts("Operation CB 0xd, RRC(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0xe:
        puts("Operation CB 0xe, RRC(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0xf:
        puts("Operation CB 0xf, RRC(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x10:
        puts("Operation CB 0x10, RL(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x11:
        exit(11);
        break;
    case 0x12:
        puts("Operation CB 0x12, RL(Regs->D)(0) not implemented!");
        exit(1);
        break;
    case 0x13:
        puts("Operation CB 0x13, RL(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x14:
        puts("Operation CB 0x14, RL(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x15:
        puts("Operation CB 0x15, RL(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x16:
        puts("Operation CB 0x16, RL(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x17:
        puts("Operation CB 0x17, RL(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x18:
        puts("Operation CB 0x18, RR(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x19:
        puts("Operation CB 0x19, RR(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0x1a:
        puts("Operation CB 0x1a, RR(Regs->D)(0) not implemented!");
        exit(1);
        break;
    case 0x1b:
        puts("Operation CB 0x1b, RR(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x1c:
        puts("Operation CB 0x1c, RR(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x1d:
        puts("Operation CB 0x1d, RR(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x1e:
        puts("Operation CB 0x1e, RR(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x1f:
        puts("Operation CB 0x1f, RR(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x20:
        puts("Operation CB 0x20, SLA(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x21:
        puts("Operation 0x21, CB 21 not implemented!");
        exit(1);
        break;
    case 0x22:
        load8(&sys->mem.memory[sys->regs.HL] ,sys->regs.A, sys);
        sys->regs.HL += 1;
        break;
    case 0x23:
        puts("Operation CB 0x23, SLA(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x24:
        puts("Operation CB 0x24, SLA(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x25:
        puts("Operation CB 0x25, SLA(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x26:
        puts("Operation CB 0x26, SLA(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x27:
        puts("Operation CB 0x27, SLA(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x28:
        puts("Operation CB 0x28, SRA(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x29:
        puts("Operation CB 0x29, SRA(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0x2a:
        puts("Operation CB 0x2a, SRA(Regs->D)(0) not implemented!");
        exit(1);
        break;
    case 0x2b:
        puts("Operation CB 0x2b, SRA(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x2c:
        puts("Operation CB 0x2c, SRA(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x2d:
        puts("Operation CB 0x2d, SRA(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x2e:
        puts("Operation CB 0x2e, SRA(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x2f:
        puts("Operation CB 0x2f, SRA(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x30:
        puts("Operation CB 0x30, SWAP(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x31:
        puts("Operation CB 0x31, SWAP(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0x32:
        load8(&sys->mem.memory[sys->regs.HL] ,sys->regs.A, sys);
        sys->regs.HL -= 1;
        break;
    case 0x33:
        puts("Operation CB 0x33, SWAP(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x34:
        puts("Operation CB 0x34, SWAP(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x35:
        puts("Operation CB 0x35, SWAP(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x36:
        puts("Operation CB 0x36, SWAP(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x37:
        puts("Operation CB 0x37, SWAP(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x38:
        puts("Operation CB 0x38, SRL(Regs->B)(0) not implemented!");
        exit(1);
        break;
    case 0x39:
        puts("Operation CB 0x39, SRL(Regs->C)(0) not implemented!");
        exit(1);
        break;
    case 0x3a:
        puts("Operation CB 0x3a, SRL(Regs->D)(0) not implemented!");
        exit(1);
        break;
    case 0x3b:
        puts("Operation CB 0x3b, SRL(Regs->E)(0) not implemented!");
        exit(1);
        break;
    case 0x3c:
        puts("Operation CB 0x3c, SRL(Regs->H)(0) not implemented!");
        exit(1);
        break;
    case 0x3d:
        puts("Operation CB 0x3d, SRL(Regs->L)(0) not implemented!");
        exit(1);
        break;
    case 0x3e:
        puts("Operation CB 0x3e, SRL(Regs->HL)(0) not implemented!");
        exit(1);
        break;
    case 0x3f:
        puts("Operation CB 0x3f, SRL(Regs->A)(0) not implemented!");
        exit(1);
        break;
    case 0x71:
        puts("Operation CB 0x71, BIT(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x72:
        puts("Operation CB 0x72, BIT(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x73:
        puts("Operation CB 0x73, BIT(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x74:
        puts("Operation CB 0x74, BIT(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x75:
        puts("Operation CB 0x75, BIT(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x76:
        puts("Operation CB 0x76, BIT(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x77:
        puts("Operation CB 0x77, BIT(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x78:
        puts("Operation CB 0x78, BIT(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x79:
        puts("Operation CB 0x79, BIT(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x7a:
        puts("Operation CB 0x7a, BIT(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x7b:
        puts("Operation CB 0x7b, BIT(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x7c:
        puts("Operation CB 0x7c, BIT(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x7d:
        puts("Operation CB 0x7d, BIT(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x7e:
        puts("Operation CB 0x7e, BIT(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x7f:
        puts("Operation CB 0x7f, BIT(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x80:
        puts("Operation CB 0x80, RES(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x81:
        puts("Operation CB 0x81, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x82:
        puts("Operation CB 0x82, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x83:
        puts("Operation CB 0x83, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x84:
        puts("Operation CB 0x84, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x85:
        puts("Operation CB 0x85, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x86:
        puts("Operation CB 0x86, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x87:
        puts("Operation CB 0x87, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x88:
        puts("Operation CB 0x88, RES(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x89:
        puts("Operation CB 0x89, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x8a:
        puts("Operation CB 0x8a, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x8b:
        puts("Operation CB 0x8b, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x8c:
        puts("Operation CB 0x8c, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x8d:
        puts("Operation CB 0x8d, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x8e:
        puts("Operation CB 0x8e, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x8f:
        puts("Operation CB 0x8f, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x90:
        puts("Operation CB 0x90, RES(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x91:
        puts("Operation CB 0x91, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x92:
        puts("Operation CB 0x92, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x93:
        puts("Operation CB 0x93, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x94:
        puts("Operation CB 0x94, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x95:
        puts("Operation CB 0x95, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x96:
        puts("Operation CB 0x96, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x97:
        puts("Operation CB 0x97, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0x98:
        puts("Operation CB 0x98, RES(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0x99:
        puts("Operation CB 0x99, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0x9a:
        puts("Operation CB 0x9a, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0x9b:
        puts("Operation CB 0x9b, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0x9c:
        puts("Operation CB 0x9c, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0x9d:
        puts("Operation CB 0x9d, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0x9e:
        puts("Operation CB 0x9e, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0x9f:
        puts("Operation CB 0x9f, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xa0:
        puts("Operation CB 0xa0, RES(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xa1:
        puts("Operation CB 0xa1, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xa2:
        puts("Operation CB 0xa2, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xa3:
        puts("Operation CB 0xa3, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xa4:
        puts("Operation CB 0xa4, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xa5:
        puts("Operation CB 0xa5, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xa6:
        puts("Operation CB 0xa6, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xa7:
        puts("Operation CB 0xa7, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xa8:
        xorA(sys->regs.B, sys);
        break;
    case 0xa9:
        puts("Operation CB 0xa9, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xaa:
        puts("Operation CB 0xaa, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xab:
        puts("Operation CB 0xab, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xac:
        puts("Operation CB 0xac, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xad:
        puts("Operation CB 0xad, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xae:
        puts("Operation CB 0xae, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xaf:
        puts("Operation CB 0xaf, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xb0:
        puts("Operation CB 0xb0, RES(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xb1:
        puts("Operation CB 0xb1, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xb2:
        puts("Operation CB 0xb2, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xb3:
        puts("Operation CB 0xb3, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xb4:
        puts("Operation CB 0xb4, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xb5:
        puts("Operation CB 0xb5, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xb6:
        puts("Operation CB 0xb6, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xb7:
        puts("Operation CB 0xb7, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xb8:
        puts("Operation CB 0xb8, RES(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xb9:
        puts("Operation CB 0xb9, RES(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xba:
        puts("Operation CB 0xba, RES(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xbb:
        puts("Operation CB 0xbb, RES(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xbc:
        puts("Operation CB 0xbc, RES(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xbd:
        puts("Operation CB 0xbd, RES(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xbe:
        puts("Operation CB 0xbe, RES(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xbf:
        puts("Operation CB 0xbf, RES(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xc0:
        puts("Operation CB 0xc0, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xc1:
        puts("Operation CB 0xc1, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xc2:
        puts("Operation CB 0xc2, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xc3:
        puts("Operation CB 0xc3, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xc4:
        puts("Operation CB 0xc4, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xc5:
        puts("Operation CB 0xc5, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xc6:
        puts("Operation CB 0xc6, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xc7:
        puts("Operation CB 0xc7, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xc8:
        puts("Operation CB 0xc8, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xc9:
        puts("Operation CB 0xc9, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xca:
        puts("Operation CB 0xca, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xcb:
        puts("Operation CB 0xcb, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xcc:
        puts("Operation CB 0xcc, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xcd:
        puts("Operation CB 0xcd, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xce:
        puts("Operation CB 0xce, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xcf:
        puts("Operation CB 0xcf, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xd0:
        puts("Operation CB 0xd0, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xd1:
        puts("Operation CB 0xd1, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xd2:
        puts("Operation CB 0xd2, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xd3:
        puts("Operation CB 0xd3, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xd4:
        puts("Operation CB 0xd4, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xd5:
        puts("Operation CB 0xd5, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xd6:
        puts("Operation CB 0xd6, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xd7:
        puts("Operation CB 0xd7, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xd8:
        puts("Operation CB 0xd8, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xd9:
        puts("Operation CB 0xd9, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xda:
        puts("Operation CB 0xda, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xdb:
        puts("Operation CB 0xdb, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xdc:
        puts("Operation CB 0xdc, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xdd:
        puts("Operation CB 0xdd, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xde:
        puts("Operation CB 0xde, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xdf:
        puts("Operation CB 0xdf, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xe0:
        puts("Operation CB 0xe0, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xe1:
        puts("Operation CB 0xe1, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xe2:
        puts("Operation CB 0xe2, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xe3:
        puts("Operation CB 0xe3, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xe4:
        puts("Operation CB 0xe4, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xe5:
        puts("Operation CB 0xe5, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xe6:
        puts("Operation CB 0xe6, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xe7:
        puts("Operation CB 0xe7, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xe8:
        puts("Operation CB 0xe8, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xe9:
        puts("Operation CB 0xe9, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xea:
        puts("Operation CB 0xea, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xeb:
        puts("Operation CB 0xeb, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xec:
        puts("Operation CB 0xec, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xed:
        puts("Operation CB 0xed, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xee:
        puts("Operation CB 0xee, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xef:
        puts("Operation CB 0xef, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xf0:
        puts("Operation CB 0xf0, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xf1:
        puts("Operation CB 0xf1, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xf2:
        puts("Operation CB 0xf2, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xf3:
        puts("Operation CB 0xf3, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xf4:
        puts("Operation CB 0xf4, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xf5:
        puts("Operation CB 0xf5, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xf6:
        puts("Operation CB 0xf6, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xf7:
        puts("Operation CB 0xf7, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    case 0xf8:
        puts("Operation CB 0xf8, SET(0)(Regs->B) not implemented!");
        exit(1);
        break;
    case 0xf9:
        puts("Operation CB 0xf9, SET(0)(Regs->C) not implemented!");
        exit(1);
        break;
    case 0xfa:
        puts("Operation CB 0xfa, SET(0)(Regs->D) not implemented!");
        exit(1);
        break;
    case 0xfb:
        puts("Operation CB 0xfb, SET(0)(Regs->E) not implemented!");
        exit(1);
        break;
    case 0xfc:
        puts("Operation CB 0xfc, SET(0)(Regs->H) not implemented!");
        exit(1);
        break;
    case 0xfd:
        puts("Operation CB 0xfd, SET(0)(Regs->L) not implemented!");
        exit(1);
        break;
    case 0xfe:
        puts("Operation CB 0xfe, SET(0)(Regs->HL) not implemented!");
        exit(1);
        break;
    case 0xff:
        puts("Operation CB 0xff, SET(0)(Regs->A) not implemented!");
        exit(1);
        break;
    }
}

// // If the Nth bit at the given register is 0, set the Z flag to 1
// void testBit(opCode *operation, System *sys){
//     printf("Testing bit %x\n", sys->regs.r[H]);
//     if (!(*(uint8_t*)operation->reg1 & *(uint8_t*)operation->reg2))
//     {
//         printf("%d,,,%d", *(uint8_t*)operation->reg2, *operation->reg2);
//         sys->regs.r[F] |= bitSets[Z];
//     }
//     sys->regs.r[F] |= bitSets[Hf];
//     sys->regs.r[F] &= iBitSets[N];
//     printf("Flag: %d\n", sys->regs.r[F]);
//     sys->regs.PC += 1;
// }

// // Does the jump happen from the adress of the instruction or the adress of the data??
// void JumpConditionReset(opCode* operation, System* sys)
// {
//     sys->regs.PC += 2;
//     printf("JZR");
//     if (!(sys->regs.r[F] & *(operation->reg2)))
//     {
//         printf("Jumped from PC: %d", sys->regs.PC-sys->mem.BOOT_ROM);
//         sys->regs.PC += *(int8_t*)(sys->regs.PC - 1);
//         printf("to PC: %d\n", sys->regs.PC-sys->mem.BOOT_ROM);
//     }
//     else
//     {
//         printf(" failed\n");

//     }
// }

// void JumpConditionSet(opCode* operation, System* sys)
// {
//     printf("jzS");
//     if (sys->regs.r[F] & *(operation->reg2))
//     {
//         printf("Jumped from PC: %d", sys->regs.PC-sys->mem.BOOT_ROM);
//         sys->regs.PC += *(int8_t*)(sys->regs.PC + 1);
//         printf("to PC: %d\n", sys->regs.PC-sys->mem.BOOT_ROM);
//     }
//     else
//     {
//         printf(" failed\n");
//         sys->regs.PC += 2;
//     }
// }

// void ExclusiveOR(opCode *operation, System *sys)
// {
//     uint8_t *input = operation->reg2;

//     sys->regs.r[A] == sys->regs.A ^ *input;

//     if (sys->regs.r[A] == 0)
//         sys->regs.r[F] &= bitSets[Z];

//     sys->regs.PC += 1;
// }

// void LoadDec(opCode *operation, System *sys)
// {
//     printf("Load decrement store\n");
//     sys->mem.memory[*sys->regs.HL] = sys->regs.r[A];
//     *sys->regs.HL -= 1;
//     sys->regs.PC += 1;
// }

// void Load(opCode *operation, System *sys)
// {

//     switch (operation->iSize) {
//     case 0: // Two 8 bit operators
//         printf("LOAD 8x8 NOT IMPLEMENTED\n");
//     exit(1);
//         break;
//     case 1: // Reg1 is 16 bit reg2 is 8 bit
//         printf("LOAD 16x8 NOT IMPLEMENTED\n");
//         break;
//     case 2: // reg2 is 8 bit reg1 is 16 bit
//         printf("LOAD 8x16 NOT IMPLEMENTED\n");

//         break;
//     case 3: // Both regs 16bit

//         *(operation->reg1) = *(operation->reg2);
//         printf("%x\n", *(operation->reg1));

//         if (operation->reg2 == sys->regs.PC+1) // We need to increment PC by 2 to get the next instruction if we load an immediate
//         {
//             sys->regs.PC += 3;
//         } else {
//             sys->regs.PC += 1;
//         }
//         break;
//     }