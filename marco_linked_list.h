#ifndef MARCO_LINKED_LIST_H
#define MARCO_LINKED_LIST_H

void add_macro(const char* name, struct macro** last_macro);

void add_line(const char* line_content, struct line **last_line);

void add_first_line_to_macro(const char* line_content, struct macro** macro);

#endif //MARCO_LINKED_LIST_H
