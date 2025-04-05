#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "first_pass.h"
#include "label_linked_list.h"
#include "label.h"
#include "entry.h"
#include "entry_linked_list.h"
#include "line_utils.h"

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
    enum line_type line_type;
    int is_label_exist;
    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return;
    }

    get_line_type(line, &line_type);

    is_label_exist = get_label_name_if_exist(line, line_type, label);

    switch (line_type) {
        case CODE:
            if (is_label_exist) {
                add_label(label, line_type, *ic, current_label);
                if ((*current_label)->next_label != NULL) {
                    *current_label = (*current_label)->next_label;
                }
            }
            update_ic(line, ic);
            break;
        case DATA:
            if (is_label_exist) {
                add_label(label, line_type, *dc, current_label);
                if ((*current_label)->next_label != NULL) {
                    *current_label = (*current_label)->next_label;
                }
            }
            update_dc(line, dc);
            break;
        case EXTERN:
            if (is_label_exist) {
                add_label(label, line_type, 0, current_label);
                if ((*current_label)->next_label != NULL) {
                    *current_label = (*current_label)->next_label;
                }
            }
            break;
        case ENTRY:
            if (is_label_exist) {
                add_entry(label, current_entry);
                if ((*current_entry)->next_entry != NULL) {
                    *current_entry = (*current_entry)->next_entry;
                }
            }
            break;
    }
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
        if (is_register(word)) {
            if (is_register_found) {
                count--;
            }
            is_register_found = TRUE;
        }
        word = strtok(NULL, " ,");
    }

    *ic += ++count;
}

int is_register(const char *str) {
    return str[0] == 'r' && str[1] >= '0' && str[1] <= '7' && str[2] == '\0';
}