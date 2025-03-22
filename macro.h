#ifndef MACRO_H
#define MACRO_H
#include "consts.h"

struct macro{
    char name[MAX_LINE_LEN];
    struct line* first_line;
    struct macro *next_macro;
};

struct line{
    char line_content[MAX_LINE_LEN];
    struct line *next_line;
};

#endif // MACRO_H
