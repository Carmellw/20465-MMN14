#ifndef LABEL_H
#define LABEL_H
#include "consts.h"

enum line_type{
    CODE,
    DATA,
    EXTERN,
    ENTRY
};

struct label{
    char name[MAX_LABEL_LEN];
    enum line_type type;
    int address;
    struct label *next_label;
};

enum data_type {
    DEFAULT,
    STRING
};
#endif // LABEL_H
