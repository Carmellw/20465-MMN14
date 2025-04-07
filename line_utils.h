//
// Created by Carmell Wasserman on 05/04/2025.
//

#ifndef LINE_UTILS_H
#define LINE_UTILS_H

#include "label.h"

int get_label_name_if_exist(const char* line, const enum line_type type, char* label_name);

int get_line_type(const char *line, enum line_type *type);

int is_instruction(const char *word);

char *trim_whitespaces_from_start(const char *line);

int is_register(const char *str);

#endif //LINE_UTILS_H
