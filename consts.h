#ifndef CONSTS_H
#define CONSTS_H

#define TRUE 1
#define FALSE 0

#define MAX_LINE_LEN 81

#define MAX_LABEL_LEN 32

#define MACRO_START "mcro"
#define MACRO_END "mcroend"

struct instruction{
    char *name;
    int opcode;
    int funct;
};

struct instruction instructions[] =
    {{"mov", 0, 0},{"cmp", 1, 0},{"add", 2, 1},
    {"sub", 2, 2},{"not", 4, 0},{"clr", 5, 1},
    {"lea", 5, 2},{"inc", 5, 3},{"dec", 5, 4},
    {"jmp", 9, 1},{"bne", 9, 2},{"red", 9, 3},
    {"prn", 12, 0},{"jsr", 13, 0},{"rts", 14, 0},
    {"stop", 15, 0}
};


#endif // CONSTS_H
