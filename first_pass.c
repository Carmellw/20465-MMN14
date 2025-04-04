#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "first_pass.h"
#include "label_linked_list.h"
#include "label.h"
#include "entry.h"
#include "entry_linked_list.h"

void first_pass_file(const char* file_path) {
    FILE *fp = fopen(file_path, "r");
    FILE *fp2 = fopen("/Users/carmellwasserman/Desktop/example4.txt", "w");
    char line[MAX_LINE_LEN];
    struct label *first_label = NULL;
    struct label *current_label = NULL;
    struct entry *first_entry = NULL;
    struct entry *current_entry = NULL;
    int ic = 100;
    int dc = 0;

    while (fgets(line, MAX_LINE_LEN, fp)) {
        handle_line(line, fp2, &current_label, &current_entry, &ic, &dc);
        if (first_label == NULL) {
            first_label = current_label;
        }
        if (first_entry == NULL) {
            first_entry = current_entry;
        }
    }

    fclose(fp);
    fclose(fp2);
}

void handle_line(const char* line, FILE* file_to_write, struct label **current_label, struct entry **current_entry, int *ic, int *dc) {
    const char label[MAX_LABEL_LEN];
    enum label_type label_type;
    int is_label_exist;
    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return;
    }

    get_label_type(line, &label_type);

    is_label_exist = get_label_name(line, label_type, label);

    switch (label_type) {
        case CODE_TYPE:
            if (is_label_exist) {
                add_label(label, label_type, *ic, current_label);
                if ((*current_label)->next_label != NULL) {
                    *current_label = (*current_label)->next_label;
                }
            }
            update_ic(line, ic);
            break;
        case DATA_TYPE:
            if (is_label_exist) {
                add_label(label, label_type, *dc, current_label);
                if ((*current_label)->next_label != NULL) {
                    *current_label = (*current_label)->next_label;
                }
            }
            update_dc(line, dc);
            break;
        case EXTERN_TYPE:
            if (is_label_exist) {
                add_label(label, label_type, 0, current_label);
                if ((*current_label)->next_label != NULL) {
                    *current_label = (*current_label)->next_label;
                }
            }
            break;
        case ENTRY_TYPE:
            if (is_label_exist) {
                add_entry(label, current_entry);
                if ((*current_entry)->next_entry != NULL) {
                    *current_entry = (*current_entry)->next_entry;
                }
            }
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

            temp_label = strtok(temp_line, ":");
            break;
        case EXTERN_TYPE:
        case ENTRY_TYPE:
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

int get_label_type(const char *line, enum label_type *type) {
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
        *type = CODE_TYPE;
    }
    else if (strncmp(word, ".data", 5) == 0 || strncmp(word, ".string", 7) == 0) {
        *type = DATA_TYPE;
    }
    else if (strncmp(word, ".extern", 7) == 0) {
        *type = EXTERN_TYPE;
    }
    else if (strncmp(word, ".entry", 6) == 0) {
        *type = ENTRY_TYPE;
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

void update_dc(const char *line, int *dc) {
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
        word = strtok(NULL, " \"");
        word = strtok(NULL, " \"");
        while (strlen(word) > 0) {
            (*dc)++;
            word++;
        }
        (*dc)++;
    }
}

void update_ic(const char *line, int *ic) {
    char temp_line[MAX_LINE_LEN];
    char *word;
    int count = 0;
    int is_register_found = FALSE;

    strcpy(temp_line, line);

    if (strchr(temp_line, ':')) {
        strtok(temp_line, ":");
        word = strtok(NULL, " \n");
    }
    else {
        word = strtok(temp_line, " \n");
    }

    if (word == NULL) {
        return;
    }

    word = strtok(NULL, " ,");

    while (word != NULL) {
        count++;
        if (word[0] == '@') {
            if (is_register_found) {
                count--;
            }
            is_register_found = TRUE;
        }
        word = strtok(NULL, " ,");
    }

    *ic += ++count;
}


