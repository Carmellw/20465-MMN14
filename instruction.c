#include "instruction.h"

struct instruction instructions[] =
{
    {"mov", 0, 0}, {"cmp", 1, 0}, {"add", 2, 1},
    {"sub", 2, 2}, {"lea", 4, 0}, {"clr", 5, 1},
    {"not", 5, 2}, {"inc", 5, 3}, {"dec", 5, 4},
    {"jmp", 9, 1}, {"bne", 9, 2}, {"jsr", 9, 3},
    {"red", 12, 0}, {"prn", 13, 0}, {"rts", 14, 0},
    {"stop", 15, 0}
};

const int instructions_count = sizeof(instructions) / sizeof(instructions[0]);
