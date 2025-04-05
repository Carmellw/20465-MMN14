#include <stdio.h>
#include <string.h>

#include "consts.h"
#include "line_utils.h"

void second_pass_file(const char *file_path, struct label *labels, struct entry *entries, int ic, int dc) {
    FILE *fp = fopen(file_path, "r");
    FILE *fp2 = fopen("/Users/carmellwasserman/Desktop/example4.txt", "w");
    char line[MAX_LINE_LEN];
    struct label *current_label = NULL;
    struct entry *current_entry = NULL;

    fprintf(fp, "%d %d\n", ic-100, dc);

    ic = 100;
    dc = 0;

    while (fgets(line, MAX_LINE_LEN, fp)) {

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

        case ENTRY:

        case DATA:
        case EXTERN:
            break;
    }
}

void handle_code_line(const char* line, FILE *file_to_write, struct label *labels, int *ic) {
    char temp_line[MAX_LINE_LEN];
    char *word;
    char *instruction;
    char *operand1 = NULL;
    char *operand2 = NULL;
    int word_count = 0;

    strcpy(temp_line, line);

    if (strchr(temp_line, ':') != NULL) {
        strtok(temp_line, ":");
        instruction = strtok(NULL, " \n");
    } else {
        instruction = strtok(temp_line, " \n");
    }

    if (!is_instruction(instruction)) {
        return; // should be error prob
    }

    operand1 = strtok(NULL, ", \n");
    operand2 = strtok(NULL, ", \n");


    fprintf(file_to_write, "%d %s\n", *ic, instruction); 

    if (operand1 != NULL) {
        //int val = encode_operand(operand1, labels);
        //fprintf(file_to_write, "%d %d\n", get_next_ic(), val);
        if (operand2 != NULL) {
            //int val = encode_operand(operand2, labels);
            //fprintf(file_to_write, "%d %d\n", get_next_ic(), val);
        }
    }
}

int convert_instruction_to_int(char* instruction, char* operand1, char* operand2) {

}

int get_opcode(const char *command) {
    int i;
    for (i = 0; i < 16; i++) {
        /*if (strcmp(command, instructions[i].name) == 0) {
            return instructions[i].opcode;
        }*/
    }
    return -1;
}
