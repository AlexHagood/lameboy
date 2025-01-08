#include <stdint.h>

typedef enum {
    F, A, B, C, E, D, L, H, AF = 0, BC = 2, DE = 4, HL = 6
} RegisterName;

typedef struct registers
{
    union {
        struct {
            uint8_t F;
            uint8_t A;
        };
        uint16_t AF;
    };

    union {
        struct {
            uint8_t C;
            uint8_t B;
        };
        uint16_t BC;
    };

    union {
        struct {
            uint8_t E;
            uint8_t D;
        };
        uint16_t DE;
    };

    union {
        struct {
            uint8_t L;
            uint8_t H;
        };
        uint16_t HL;
    };

    // Special Purpose Registers
    uint8_t* PC;
    uint16_t SP;
    
} Registers;

void initRegs(Registers* regBank)
{
    regBank->SP = 0xFEFE;
};