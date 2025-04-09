#ifndef MARCO_LINKED_LIST_H
#define MARCO_LINKED_LIST_H
#include <stdio.h>

void replace_macros(FILE *file_to_read, FILE *file_to_write, struct macro *macros);

void add_macro(const char *name, struct macro **last_macro);

void add_line(const char *line_content, struct line **last_line);

void add_first_line_to_macro(const char *line_content, struct macro **macro);

void free_macros(struct macro *first_macro);

#endif
