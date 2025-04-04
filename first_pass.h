#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "label.h"

void first_pass_file(const char* file_path);

void handle_line(const char* line, FILE* file_to_write, struct label **current_label, int *ic, int *dc);

int get_label_name(const char* line, const enum label_type type, char* label_name);

int get_label_type(const char *line, enum label_type *type);

int is_instruction(const char *word);

void update_dc(const char *line, int *dc);

void update_ic(const char *line, int *ic);

#endif //FIRST_PASS_H
