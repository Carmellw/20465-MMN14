#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "label.h"
#include "entry.h"

void first_pass_file(const char* file_path, struct label* labels, struct entry* entries, int *ic, int *dc);

void handle_line(const char* line, FILE* file_to_write, struct label **current_label, struct entry **current_entry, int *ic, int *dc);

void update_dc(const char *line, int *dc);

void update_ic(const char *line, int *ic);

#endif //FIRST_PASS_H
