#ifndef MACRO_EXPANDER_H
#define MACRO_EXPANDER_H

#include <stdio.h>

#include "macro_expander.h"
#include "macro.h"

void expand_macros(const char *file_path);

void separate_macros_from_file(FILE* file_to_read, FILE* file_to_write, struct macro **macros);

char *get_macro_name(char *line);

void remove_whitespaces_from_string(char *str, char **result);

int compare_strings_until_null_terminator(const char *str1, const char *str2);

#endif //MACRO_EXPANDER_H
