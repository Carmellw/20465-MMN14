#ifndef INTSTRUCTION_H
#define INTSTRUCTION_H

struct instruction{
    char *name;
    int opcode;
    int funct;
};

enum addressing_type {
    IMMEDIATE,
    DIRECT,
    RELATIVE,
    REGISTER,
    ILLEGAL
};

extern struct instruction instructions[];

extern const int instructions_count;

#endif
