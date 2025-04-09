//
// Created by Carmell Wasserman on 04/04/2025.
//

#ifndef ENTRY_H
#define ENTRY_H

#include "consts.h"

struct extern_struct{
    char name[MAX_LABEL_LEN];
    struct extern_struct *next_extern;
};

#endif //ENTRY_H
