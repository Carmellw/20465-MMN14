#ifndef FIRST_PASS_H
#define FIRST_PASS_H

void first_pass_file(const char* file_path);

void handle_line(const char* line, FILE* file_to_write, struct label **current_label);

int get_label_name(const char* line, const enum label_type type, char* label_name);

int get_label_type(const char *line, enum label_type *type);

int is_instruction(const char *word);

void handle_data_count(const char *line, int *dc);

#endif //FIRST_PASS_H
