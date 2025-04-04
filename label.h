#ifndef LABEL_H
#define LABEL_H
#include "consts.h"

enum label_type{
    CODE_TYPE,
    DATA_TYPE,
    EXTERN_TYPE,
    ENTRY_TYPE
};

struct label{
    char name[MAX_LABEL_LEN];
    enum label_type type;
    int address;
    struct label *next_label;
};

#endif // LABEL_H
