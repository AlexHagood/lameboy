#include <stdint.h>
#include "sys.h"


int display(System sys);

struct tile {
    uint16_t line[8];
};