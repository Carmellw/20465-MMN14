#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "consts.h"
#include "line_utils.h"
#include "status_codes.h"
#include "second_pass.h"
#include "instruction.h"
#include "path_utils.h"
#include "label_linked_list.h"

enum status_code handle_line2(const char *line, FILE *file_to_write, FILE *entry_file, FILE *extern_file,
                              struct label *labels, int *ic, int *is_entry_found, int *is_extern_found);

enum status_code handle_code_line(const char *line, FILE *file_to_write, FILE *extern_file, struct label *labels,
                                  int *ic);

enum status_code handle_data_line(const char *line, FILE *file_to_write, int *ic);

enum status_code handle_entry_line(const char *line, FILE *file_to_write, const struct label *labels);

enum status_code handle_extern_operand(const char *line, FILE *file_to_write, const int *ic,
                                       const struct label *labels);

enum status_code convert_code_line_to_binary(const char *instruction, const char *src_operand, const char *dst_operand,
                                             unsigned int *command);

enum status_code get_instruction(const char *name, struct instruction *instruction);

enum addressing_type get_addressing_type(const char *operand);

enum status_code get_operand_value(const char *operand, enum addressing_type addressing_type,
                                   const struct label *labels,
                                   int command_address, int *value, int *is_extern);

enum status_code second_pass_file(const char *file_path, struct label *labels, int ic, const int dc) {
    FILE *read_file = fopen(file_path, "r");
    FILE *ob_file;
    FILE *ent_file;
    FILE *ext_file;
    char *ob_file_path;
    char *ent_file_path;
    char *ext_file_path;
    char line[MAX_LINE_LEN];
    int is_file_successful = TRUE;
    enum status_code status_code;
    int is_entry_found = FALSE;
    int is_extern_found = FALSE;

    ob_file_path = get_new_path(file_path, NULL, "ob");
    ent_file_path = get_new_path(file_path, NULL, "ent");
    ext_file_path = get_new_path(file_path, NULL, "ext");

    ob_file = fopen(ob_file_path, "w");
    ent_file = fopen(ent_file_path, "w");
    ext_file = fopen(ext_file_path, "w");

    fprintf(ob_file, "% 7d %d\n", ic - 100, dc);

    ic = 100;

    while (fgets(line, MAX_LINE_LEN, read_file)) {
        status_code = handle_line2(line, ob_file, ent_file, ext_file, labels, &ic, &is_entry_found, &is_extern_found);
        if (status_code != SUCCESS) {
            is_file_successful = FALSE;
            fprintf(stderr, "Error while reading line:\n\"%s\"\n", line);
        }
    }

    fclose(read_file);
    fclose(ob_file);
    fclose(ent_file);
    fclose(ext_file);

    printf("Created files %s", ob_file_path);

    if (is_entry_found) {
        printf(" %s", ent_file_path);
    } else {
        remove(ent_file_path);
    }
    if (is_extern_found) {
        printf(" %s", ext_file_path);
    } else {
        remove(ext_file_path);
    }

    printf("\n");

    free(ob_file_path);
    free(ent_file_path);
    free(ext_file_path);

    if (!is_file_successful) {
        return FILE_FAILED;
    }
    return SUCCESS;
}

enum status_code handle_line2(const char *line, FILE *file_to_write, FILE *entry_file, FILE *extern_file,
                              struct label *labels, int *ic, int *is_entry_found, int *is_extern_found) {
    enum line_type label_type;
    enum status_code status_code;
    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return SUCCESS;
    }

    status_code = get_line_type(line, &label_type);
    if (status_code != SUCCESS) {
        return status_code;
    }

    switch (label_type) {
        case CODE:
            status_code = handle_code_line(line, file_to_write, extern_file, labels, ic);
            if (status_code != SUCCESS) {
                return status_code;
            }
            break;
        case ENTRY:
            status_code = handle_entry_line(line, entry_file, labels);
            if (status_code != SUCCESS) {
                return status_code;
            }
            *is_entry_found = TRUE;
            break;
        case DATA:
            status_code = handle_data_line(line, file_to_write, ic);
            if (status_code != SUCCESS) {
                return status_code;
            }
            break;
        case EXTERN:
            *is_extern_found = TRUE;
            break;
    }

    return SUCCESS;
}

enum status_code handle_code_line(const char *line, FILE *file_to_write, FILE *extern_file, struct label *labels,
                                  int *ic) {
    char temp_line[MAX_LINE_LEN];
    char *instruction;
    char *operand1 = NULL;
    char *operand2 = NULL;
    enum status_code status_code;
    unsigned int command = 0;
    int operand_value = 0;
    enum addressing_type addressing_type;
    int command_address;
    int is_extern;

    strcpy(temp_line, line);

    if (strchr(temp_line, ':') != NULL) {
        strtok(temp_line, ":");
        instruction = strtok(NULL, " \n\t");
    } else {
        instruction = strtok(temp_line, " \n\t");
    }

    if (!is_instruction(instruction)) {
        return UNKNOWN_ERROR;
    }

    operand1 = strtok(NULL, ", \n\t");
    operand2 = strtok(NULL, ", \n\t");

    if (operand2 == NULL) {
        operand2 = operand1;
        operand1 = NULL;
    }

    status_code = convert_code_line_to_binary(instruction, operand1, operand2, &command);
    if (status_code != SUCCESS) {
        return status_code;
    }

    fprintf(file_to_write, "%07d %06x\n", *ic, command);
    command_address = (*ic)++;

    if (operand1 != NULL) {
        addressing_type = get_addressing_type(operand1);
        if (addressing_type != REGISTER) {
            status_code = get_operand_value(operand1, addressing_type, labels, command_address, &operand_value,
                                            &is_extern);
            if (status_code != SUCCESS) {
                return status_code;
            }
            fprintf(file_to_write, "%07d %06x\n", *ic, operand_value);
            if (is_extern) {
                fprintf(extern_file, "%s %07d\n", operand1, *ic);
            }
            (*ic)++;
        }
    }
    if (operand2 != NULL) {
        addressing_type = get_addressing_type(operand2);
        if (addressing_type != REGISTER) {
            status_code = get_operand_value(operand2, addressing_type, labels, command_address, &operand_value,
                                            &is_extern);
            if (status_code != SUCCESS) {
                return status_code;
            }
            fprintf(file_to_write, "%07d %06x\n", *ic, operand_value);
            if (is_extern) {
                fprintf(extern_file, "%s %07d\n", operand2, *ic);
            }
            (*ic)++;
        }
    }

    return SUCCESS;
}

enum status_code handle_data_line(const char *line, FILE *file_to_write, int *ic) {
    char temp_line[MAX_LINE_LEN];
    char *data_type_str;
    enum status_code status_code;
    enum data_type data_type;
    char *data;
    int data_value;

    strcpy(temp_line, line);

    if (strchr(temp_line, ':') != NULL) {
        strtok(temp_line, ":");
        data_type_str = strtok(NULL, " \n\t");
    } else {
        data_type_str = strtok(temp_line, " \n\t");
    }

    status_code = get_data_type(data_type_str, &data_type);
    if (status_code != SUCCESS) {
        return status_code;
    }

    data = strtok(NULL, " \n\t");

    switch (data_type) {
        case DEFAULT:
            while (data != NULL) {
                data_value = atoi(data) & 0xFFFFFF;
                fprintf(file_to_write, "%07d %06x\n", *ic, data_value);
                data = strtok(NULL, ", \n\t");
                (*ic)++;
            }
            break;
        case STRING:
            data = strtok(data, "\"");
            while (TRUE) {
                fprintf(file_to_write, "%07d %06x\n", *ic, *data & 0xFFFFFF);
                (*ic)++;
                if (*data == '\0') {
                    break;
                }
                data++;
            }
            break;
    }
    return SUCCESS;
}

enum status_code handle_entry_line(const char *line, FILE *file_to_write, const struct label *labels) {
    char temp_line[MAX_LINE_LEN];
    char *label_name;
    enum status_code status_code;
    struct label label;

    strcpy(temp_line, line);

    strtok(temp_line, " \n\t");
    label_name = strtok(NULL, " \n\t");

    status_code = get_label(label_name, labels, &label);
    if (status_code != SUCCESS) {
        return status_code;
    }

    fprintf(file_to_write, "%s %07d\n", label.name, label.address);

    return SUCCESS;
}

enum status_code handle_extern_operand(const char *line, FILE *file_to_write, const int *ic,
                                       const struct label *labels) {
    char temp_line[MAX_LINE_LEN];
    char *label_name;
    enum status_code status_code;
    struct label label;

    strcpy(temp_line, line);

    strtok(temp_line, " \n\t");
    label_name = strtok(NULL, " \n\t");

    status_code = get_label(label_name, labels, &label);
    if (status_code != SUCCESS) {
        return status_code;
    }

    if (label.type != EXTERN) {
        return UNKNOWN_ERROR;
    }

    fprintf(file_to_write, "%s %07d\n", label.name, *ic);
    return SUCCESS;
}

enum status_code convert_code_line_to_binary(const char *instruction, const char *src_operand, const char *dst_operand,
                                             unsigned int *command) {
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
        if (src_addressing_type == ILLEGAL) {
            fprintf(stderr, "operand \"%s\" is illegal (skipping line)\n", src_operand);
            return ILLEGAL_OPERAND;
        }
        if (src_addressing_type == REGISTER) {
            src_reg = src_operand[1] - 48;
        }
    }

    if (dst_operand != NULL) {
        dst_addressing_type = get_addressing_type(dst_operand);
        if (dst_addressing_type == ILLEGAL) {
            fprintf(stderr, "operand \"%s\" is illegal (skipping line)\n", dst_operand);
            return ILLEGAL_OPERAND;
        }
        if (dst_addressing_type == REGISTER) {
            dst_reg = (int) dst_operand[1];
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
    for (i = 0; i < instructions_count; i++) {
        if (strcmp(name, instructions[i].name) == 0) {
            *instruction = instructions[i];
            return SUCCESS;
        }
    }
    return UNKNOWN_ERROR;
}

enum addressing_type get_addressing_type(const char *operand) {
    if (operand[0] == '#') {
        if (is_number(operand + 1)) {
            return IMMEDIATE;
        }
    } else if (operand[0] == '&') {
        if (is_legal_label(operand + 1)) {
            return RELATIVE;
        }
    } else if (is_register(operand)) {
        return REGISTER;
    } else if (is_legal_label(operand)) {
        return DIRECT;
    }
    return ILLEGAL;
}

enum status_code get_operand_value(const char *operand, const enum addressing_type addressing_type,
                                   const struct label *labels,
                                   const int command_address, int *value, int *is_extern) {
    enum status_code status_code;
    char *endptr;
    struct label label;
    int temp_value = 0;

    *value = 0;
    *is_extern = FALSE;

    switch (addressing_type) {
        case REGISTER:
            *value = 0;
            return SUCCESS;
        case IMMEDIATE:
            temp_value = (int) strtol(operand + 1, &endptr, 10);
            if (*endptr != '\0') {
                return UNKNOWN_ERROR;
            }
            *value |= (temp_value & 0x1FFFFF) << 3;
            *value |= 1 << 2;
            *value |= 0 << 1;
            *value |= 0;
            return SUCCESS;
        case RELATIVE:
            operand++;
            status_code = get_label(operand, labels, &label);
            if (status_code != SUCCESS) {
                return status_code;
            }
            *value |= ((label.address - command_address) & 0x1FFFFF) << 3;
            *value |= 1 << 2;
            *value |= 0 << 1;
            *value |= 0;

            if (label.type == EXTERN) {
                *is_extern = TRUE;
            }

            return SUCCESS;
        case DIRECT:
            status_code = get_label(operand, labels, &label);
            if (status_code != SUCCESS) {
                return status_code;
            }
            *value |= (label.address & 0x1FFFFF) << 3;
            if (label.type == EXTERN) {
                *value |= 0 << 2;
                *value |= 0 << 1;
                *value |= 1;
            } else {
                *value |= 0 << 2;
                *value |= 1 << 1;
                *value |= 0;
            }

            if (label.type == EXTERN) {
                *is_extern = TRUE;
            }
            return SUCCESS;
        case ILLEGAL:
            fprintf(stderr, "operand \"%s\" is illegal (skipping line)\n", operand);
            return ILLEGAL_OPERAND;
    }
    return UNKNOWN_ERROR;
}
