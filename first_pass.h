#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "label.h"
#include "extern_struct.h"

void first_pass_file(const char* file_path, struct label **labels, struct extern_struct **entries, int *ic, int *dc);

void handle_line(const char* line, FILE* file_to_write, struct label **current_label, struct extern_struct **current_entry, int *ic, int *dc, int* address_counter);

void update_dc(const char *line, int *dc, int* address_counter);

void update_ic(const char *line, int *ic, int *address_counter);

#endif //FIRST_PASS_H
