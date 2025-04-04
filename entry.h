//
// Created by Carmell Wasserman on 04/04/2025.
//

#ifndef ENTRY_H
#define ENTRY_H

#include "consts.h"

struct entry{
    char name[MAX_LABEL_LEN];
    struct entry *next_entry;
};

#endif //ENTRY_H
