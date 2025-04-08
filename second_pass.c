#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "line_utils.h"
#include "status_codes.h"
#include "second_pass.h"

#include "first_pass.h"
#include "intstruction.h"

void second_pass_file(const char *file_path, struct label *labels, struct entry *entries, int ic, int dc) {
    FILE *fp = fopen(file_path, "r");
    FILE *fp2 = fopen("/Users/carmellwasserman/Desktop/example4.txt", "w");
    char line[MAX_LINE_LEN];
    struct label *current_label = NULL;
    struct entry *current_entry = NULL;

    fprintf(fp2, "%d %d\n", ic-100, dc);

    ic = 100;
    dc = 0;

    while (fgets(line, MAX_LINE_LEN, fp)) {
        handle_line2(line, fp2, labels, entries, &ic, &dc);
    }

    fclose(fp);
    fclose(fp2);
}

void handle_line2(const char* line, FILE *file_to_write, struct label *labels, struct entry *entries, int *ic, int *dc) {
    const char label[MAX_LABEL_LEN];
    enum line_type label_type;
    int is_label_exist;
    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return;
    }

    get_line_type(line, &label_type);

    switch (label_type) {
        case CODE:
            handle_code_line(line, file_to_write, labels, ic);
        case ENTRY:
        case DATA:
        case EXTERN:
            break;
    }
}

enum status_code handle_code_line(const char* line, FILE *file_to_write, struct label *labels, int *ic) {
    char temp_line[MAX_LINE_LEN];
    char *word;
    char *instruction;
    char *operand1 = NULL;
    char *operand2 = NULL;
    int word_count = 0;
    enum status_code status_code;
    unsigned int command = 0;

    strcpy(temp_line, line);

    if (strchr(temp_line, ':') != NULL) {
        strtok(temp_line, ":");
        instruction = strtok(NULL, " \n");
    } else {
        instruction = strtok(temp_line, " \n");
    }

    if (!is_instruction(instruction)) {
        return UNKNOWN_ERROR;
    }

    operand1 = strtok(NULL, ", \n");
    operand2 = strtok(NULL, ", \n");

    if (operand2 == NULL) {
        operand2 = operand1;
        operand1 = NULL;
    }

    status_code = convert_code_line_to_binary(instruction, operand1, operand2, &command);
    if (status_code != SUCCESS) {
        return status_code;
    }

    fprintf(file_to_write, "%d %06X %s\n", *ic, command, instruction);

    if (operand1 != NULL) {
        //int val = encode_operand(operand1, labels);
        //fprintf(file_to_write, "%d %d\n", get_next_ic(), val);
        if (operand2 != NULL) {
            //int val = encode_operand(operand2, labels);
            //fprintf(file_to_write, "%d %d\n", get_next_ic(), val);
        }
    }

    return SUCCESS;
}

enum status_code convert_code_line_to_binary(const char* instruction, const char* src_operand, const char* dst_operand,
    unsigned int *command){

    enum status_code status_code;
    struct instruction instruction_struct;
    int src_reg = 0;
    int dst_reg = 0;
    enum addressing_type src_addressing_type = 0;
    enum addressing_type dst_addressing_type = 0;

    status_code = get_instruction(instruction, &instruction_struct);
    if (status_code != SUCCESS) {
        return status_code;
    }

    if (src_operand != NULL) {
        src_addressing_type = get_addressing_type(src_operand);
        if (src_addressing_type == REGISTER) {
            src_reg = src_operand[1] - 48;
        }
    }

    if (dst_operand != NULL) {
        dst_addressing_type = get_addressing_type(dst_operand);
        if (dst_addressing_type == REGISTER) {
            dst_reg = (int)dst_operand[1];
        }
    }

    *command = 0;
    *command |= (instruction_struct.opcode & 0x3F) << 18;
    *command |= (src_addressing_type & 0x3) << 16;
    *command |= (src_reg & 0x7) << 13;
    *command |= (dst_addressing_type & 0x3) << 11;
    *command |= (dst_reg & 0x7) << 8;
    *command |= (instruction_struct.funct & 0x1F) << 3;
    *command |= 1 << 2;
    *command |= 0 << 1;
    *command |= 0;

    return SUCCESS;
}

enum status_code get_instruction(const char *name, struct instruction *instruction) {
    int i;
    for (i = 0; i < 16; i++) {
        if (strcmp(name, instructions[i].name) == 0) {
            *instruction = instructions[i];
            return SUCCESS;
        }
    }
    return UNKNOWN_ERROR;
}

enum addressing_type get_addressing_type(const char *operand) {
    if (operand[0] == '#') {
        return IMMEDIATE;
    }
    if (operand[0] == '&') {
        return RELATIVE;
    }
    if (is_register(operand)) {
        return REGISTER;
    }
    return DIRECT;
}



