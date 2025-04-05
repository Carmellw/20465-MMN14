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
};

/*struct instruction instructions[] = {{"mov", 0},{"cmp", 1},{"add", 2},
                                {"sub", 2},{"not", 4},{"clr", 5},
                                {"lea", 5},{"inc", 5},{"dec", 5},
                                {"jmp", 9},{"bne", 9},{"red", 9},
                                {"prn", 12},{"jsr", 13},{"rts", 14},
                                {"stop", 15}
};*/


#endif // CONSTS_H
