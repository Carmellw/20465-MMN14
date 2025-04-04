#ifndef FIRST_PASS_H
#define FIRST_PASS_H

void first_pass_file(const char* file_path);

void handle_line(const char* line, FILE* file_to_write);

int get_label_if_exist(const char* line, char* label);

#endif //FIRST_PASS_H
