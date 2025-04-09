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
    REGISTER
};

struct instruction instructions[];

const int instructions_count;

#endif //INTSTRUCTION_H
