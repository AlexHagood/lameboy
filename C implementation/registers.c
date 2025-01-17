#include <stdint.h>

typedef enum
{
    F,
    A,
    B,
    C,
    E,
    D,
    L,
    H,
    AF = 0,
    BC = 2,
    DE = 4,
    HL = 6
} RegisterName;

typedef struct registers
{

    uint8_t r[8];

    // BASE GAMEBOY REGISTERS
    const uint8_t D;
    const uint8_t E;
    const uint8_t H;
    const uint8_t L;

    union
    {
        struct
        {
            union
            {
                struct
                {
                    uint8_t unused : 4;
                    uint8_t Cf : 1;
                    uint8_t Hf : 1;
                    uint8_t Nf : 1;
                    uint8_t Zf : 1;
                };
                uint8_t F;
            };
            uint8_t A;
        };
        uint16_t AF;
    };

    union
    {
        struct
        {
            uint8_t C;
            uint8_t B;
        };
        uint16_t BC;
    };

    union
    {
        struct
        {
            uint8_t E;
            uint8_t D;
        };
        uint16_t DE;
    };

    union
    {
        struct
        {
            uint8_t L;
            uint8_t H;
        };
        uint16_t HL;
    };

    // Special Purpose Registers
    uint8_t *PC;
    uint16_t SP;

} Registers;
