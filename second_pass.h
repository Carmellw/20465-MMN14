//
// Created by Carmell Wasserman on 05/04/2025.
//

#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "intstruction.h"
#include "status_codes.h"
#include "label.h"
#include "entry.h"

enum status_code convert_code_line_to_binary(const char* instruction, const char* src_operand, const char* dst_operand,
    unsigned int *command);

enum status_code get_instruction(const char *name, struct instruction *instruction);

enum addressing_type get_addressing_type(const char *operand);

enum status_code handle_code_line(const char* line, FILE *file_to_write, struct label *labels, int *ic);

void handle_line2(const char* line, FILE *file_to_write, struct label *labels, struct entry *entries, int *ic, int *dc);

void second_pass_file(const char *file_path, struct label *labels, struct entry *entries, int ic, int dc);

#endif //SECOND_PASS_H
