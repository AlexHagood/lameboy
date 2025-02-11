#include <stdint.h>
#include "sys.h"

void executeOperation();
void executePrefixOperation();

void xorA(uint8_t n);
void load16(uint16_t *dest, uint16_t src);
void ldd();
void bit();
void jr_conditional();
void load16(uint16_t *dest, uint16_t src);
void load8(uint8_t *dest, uint8_t src);
void load8registers();
void inc(uint8_t *reg);
void call(int condition);
void push(uint16_t reg);
void rotate_left(uint8_t *reg);
void pop(uint16_t* reg);
void decrement(uint8_t *reg);
void ldi();
void increment(uint16_t* reg);
void ret();
void cp(uint8_t* reg);
void add16(uint16_t reg);