#include <stdio.h>

#include "consts.h"
#include "first_pass.h"
#include "label_linked_list.h"
#include "label.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void first_pass_file(const char* file_path) {
    FILE *fp = fopen(file_path, "r");
    FILE *fp2 = fopen("/Users/carmellwasserman/Desktop/example4.txt", "w");
    char line[MAX_LINE_LEN];
    struct label *first_label = NULL;
    struct label *current_label = NULL;
    int ic = 100;
    int dc = 0;

    while (fgets(line, MAX_LINE_LEN, fp)) {
        handle_line(line, fp2, &current_label);
        if (first_label == NULL) {
            first_label = current_label;
        }
    }

    fclose(fp);
    fclose(fp2);
}

void handle_line(const char* line, FILE* file_to_write, struct label **current_label, int *ic, int *dc) {
    const char label[MAX_LABEL_LEN];
    enum label_type label_type;

    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return;
    }

    get_label_type(line, &label_type);

    get_label_name(line, label_type, label);

    switch (label_type) {
        case CODE_TYPE:
            add_label(label, label_type, *ic, current_label);
        case DATA_TYPE:
            add_label(label, label_type, *dc, current_label);
            handle_data_count(line, dc);
        case EXTERN_TYPE:
            add_label(label, label_type, 0, current_label);
            break;
        case ENTRY_TYPE:
            // entry list
            break;
    }
}

int get_label_name(const char* line, const enum label_type type, char* label_name) {
    char temp_line[MAX_LINE_LEN];
    char *temp_label;
    int i = 0;

    strcpy(temp_line, line);

    switch (type) {
        case CODE_TYPE:
        case DATA_TYPE:
            if (strchr(line, ':') == NULL) {
                return FALSE;
            }
            strcpy(temp_line, line);
            temp_label = strtok(temp_line, ":");
            break;
        case EXTERN_TYPE:
        case ENTRY_TYPE:
            temp_label = strtok(temp_line, " ");
            temp_label = strtok(NULL, " ");
            if (temp_label == NULL) {
                return FALSE;
            }
        default:
            return FALSE;
    }

    while (strlen(temp_label) > 0) {
        if (!isspace(*temp_label)) {
            break;
        }
        temp_label++;
    }

    while (strlen(temp_label) > i) {
        if (!isalnum(temp_label[i])) {
            return FALSE; // should be error
        }
        i++;
    }

    strcpy(label_name, temp_label);
    return TRUE;
}

int get_label_type(const char *line, enum label_type *type) {
    char temp_line[MAX_LINE_LEN];
    char *word;

    strcpy(temp_line, line);

    word = strtok(temp_line, ":");
    if (strchr(line, ':') != NULL) {
        word = strtok(NULL, " ");
    }

    if (word == NULL) {
        return FALSE;
    }

    while (strlen(word) > 0) {
        if (!isspace(*word)) {
            break;
        }
        word++;
    }

    if (strncmp(word, ".data", 5) == 0 || strncmp(word, ".string", 7) == 0) {
        *type = DATA_TYPE;
    } else if (strncmp(word, ".extern", 7) == 0) {
        *type = EXTERN_TYPE;
    } else if (strncmp(word, ".entry", 6) == 0) {
        *type = ENTRY_TYPE;
    } else if (is_instruction(word)) {
        *type = CODE_TYPE;
    } else {
        return FALSE;
    }

    return TRUE;
}

int is_instruction(const char *word) {
    const char *instructions[] = {"mov", "cmp", "add", "sub","not", "clr","lea", "inc","dec", "jmp", "bne","red","prn", "jsr" , "rts", "stop"};
    int i;

    for (i = 0; i < sizeof(instructions)/3 ; i++) {
        if (strcmp(word, instructions[i]) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

void handle_data_count(const char *line, int *dc) {
    char temp_line[MAX_LINE_LEN];
    char *word;

    strcpy(temp_line, line);

    if (strstr(line, ".data")) {
        word = strtok(NULL, ",");
        while (word != NULL) {
            (*dc)++;
            word = strtok(NULL, ",");
        }
    }
    else if (strstr(line, ".string")) {
        word = strtok(NULL, "\"");
        while (*word != '\"') {
            (*dc)++;
            word++;
        }
        (*dc)++;
    }
}


