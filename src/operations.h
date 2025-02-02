#include <stdint.h>
#include "sys.h"

void executeOperation(System *sys);
void executePrefixOperation(System *sys);

void xorA(uint8_t n, System *sys);
void load16(uint16_t *dest, uint16_t src);
void ldd(System *sys);
void bit(System *sys);
void jr_conditional(System *sys);
void load16(uint16_t *dest, uint16_t src);
void load8(uint8_t *dest, uint8_t src, System *sys);
void load8registers(System *sys);
void inc(uint8_t *reg, System *sys);
void call(System *sys, int condition);
void push(System *sys, uint16_t reg);
void rotate_left(System *sys, uint8_t *reg);
void pop(System* sys, uint16_t* reg);
void decrement(System *sys, uint8_t *reg);
void ldi(System *sys);
void increment(System *sys, uint16_t* reg);
void ret(System *sys);