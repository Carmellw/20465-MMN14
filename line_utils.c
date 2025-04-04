#include <ctype.h>
#include <string.h>

#include "consts.h"
#include "label.h"
#include "line_utils.h"

int get_label_name_if_exist(const char* line, const enum line_type type, char* label_name) {
    char temp_line[MAX_LINE_LEN];
    char *temp_label;
    int i = 0;

    strcpy(temp_line, line);

    switch (type) {
        case CODE:
        case DATA:
            if (strchr(line, ':') == NULL) {
                return FALSE;
            }

        temp_label = strtok(temp_line, ":");
        break;
        case EXTERN:
        case ENTRY:
            temp_label = strtok(temp_line, " \n");
        temp_label = strtok(NULL, " \n");
        if (temp_label == NULL) {
            return FALSE;
        }
        break;
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

int get_line_type(const char *line, enum line_type *type) {
    char temp_line[MAX_LINE_LEN];
    char *word;

    strcpy(temp_line, line);

    if (strchr(line, ':') != NULL) {
        word = strtok(temp_line, ":");
        word = strtok(NULL, " \n");
    }
    else {
        word = strtok(temp_line, " \n");
    }

    if (word == NULL) {
        word = strtok(NULL, " ");
    }

    while (word != NULL && strlen(word) > 0) {
        if (!isspace(*word)) {
            break;
        }
        word++;
    }

    if (word == NULL || is_instruction(word)) {
        *type = CODE;
    }
    else if (strncmp(word, ".data", 5) == 0 || strncmp(word, ".string", 7) == 0) {
        *type = DATA;
    }
    else if (strncmp(word, ".extern", 7) == 0) {
        *type = EXTERN;
    }
    else if (strncmp(word, ".entry", 6) == 0) {
        *type = ENTRY;
    }
    else {
        return FALSE;
    }

    return TRUE;
}

int is_instruction(const char *word) {
    const char *instructions[] = {"mov", "cmp", "add", "sub","not", "clr","lea", "inc","dec", "jmp", "bne","red","prn", "jsr" , "rts", "stop"};
    int i;

    for (i = 0; i < sizeof(instructions)/sizeof(instructions[0]) ; i++) {
        if (strcmp(word, instructions[i]) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

char *trim_whitespaces_from_start(const char *line) {
    while (isspace(*line)) {
        line++;
    }
    return line;
}