//
// Created by Carmell Wasserman on 05/04/2025.
//

#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "intstruction.h"
#include "status_codes.h"
#include "label.h"
#include "extern_struct.h"

enum status_code convert_code_line_to_binary(const char* instruction, const char* src_operand, const char* dst_operand,
                                             unsigned int *command);

enum status_code get_instruction(const char *name, struct instruction *instruction);

enum addressing_type get_addressing_type(const char *operand);

enum status_code handle_code_line(const char* line, FILE *file_to_write, FILE *extern_file, struct label *labels, int *ic);

void handle_line2(const char* line, FILE *file_to_write, FILE *extern_file, FILE *entry_file, struct label *labels,
    struct extern_struct *entries, int *ic, int *dc);

void second_pass_file(const char *file_path, struct label *labels, struct extern_struct *entries, int ic, int dc);

enum status_code get_label(const char *name, const struct label *labels, struct label *label);

enum status_code get_operand_value(const char *operand, enum addressing_type addressing_type, struct label *labels,
    const int command_address, int* value, int* is_extern);

enum status_code handle_data_line(const char *line, FILE *file_to_write, int *ic);

enum status_code handle_entry_line(const char *line, FILE *file_to_write, struct label *labels);

#endif //SECOND_PASS_H
