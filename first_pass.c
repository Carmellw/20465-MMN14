#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "first_pass.h"
#include "label_linked_list.h"
#include "label.h"
#include "line_utils.h"
#include "status_codes.h"

enum status_code handle_line(const char *line, const struct label *first_label, struct label **current_label, int *ic,
                             int *dc, int *address_counter);

void update_dc(const char *line, int *dc, int *address_counter);

void update_ic(const char *line, int *ic, int *address_counter);

enum status_code first_pass_file(const char *file_path, struct label **labels, int *ic, int *dc) {
    FILE *read_file = fopen(file_path, "r");
    char line[MAX_LINE_LEN];
    struct label *first_label = NULL;
    struct label *current_label = NULL;
    *ic = 100;
    *dc = 0;
    int address_counter = 100;
    enum status_code status_code;

    if (read_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", file_path);
        return FAILED_OPENING_FILE;
    }

    while (fgets(line, MAX_LINE_LEN, read_file)) {
        status_code = handle_line(line, first_label, &current_label, ic, dc, &address_counter);
        if (status_code != SUCCESS && status_code != LABEL_ALREADY_EXISTS) {
            return status_code;
        }
        if (first_label == NULL) {
            first_label = current_label;
        }
    }

    *labels = first_label;

    fclose(read_file);

    return SUCCESS;
}

enum status_code handle_line(const char *line, const struct label *first_label, struct label **current_label, int *ic,
                             int *dc, int *address_counter) {
    const char label[MAX_LABEL_LEN];
    enum line_type line_type;
    int is_label_in_line;
    if (line[0] == '\0' || line[0] == '\n' || line[0] == ';') {
        return SUCCESS;
    }

    get_line_type(line, &line_type);

    is_label_in_line = get_label_name_if_exist(line, line_type, label);

    switch (line_type) {
        case CODE:
            if (is_label_in_line) {
                if (!is_label_exists(label, first_label)) {
                    add_label(label, line_type, *address_counter, current_label);
                    if ((*current_label)->next_label != NULL) {
                        *current_label = (*current_label)->next_label;
                    }
                } else {
                    fprintf(
                        stderr, "Error: label '%s' already exists, you can't have multiple labels with the same name (ignoring label)\n",
                        label);
                    return LABEL_ALREADY_EXISTS;
                }
            }
            update_ic(line, ic, address_counter);
            break;
        case DATA:
            if (is_label_in_line) {
                if (!is_label_exists(label, first_label)) {
                    add_label(label, line_type, *address_counter, current_label);
                    if ((*current_label)->next_label != NULL) {
                        *current_label = (*current_label)->next_label;
                    }
                } else {
                    fprintf(
                        stderr, "Error: label '%s' already exists, you can't have multiple labels with the same name (ignoring label)\n",
                        label);
                    return LABEL_ALREADY_EXISTS;
                }
            }
            update_dc(line, dc, address_counter);
            break;
        case EXTERN:
            if (is_label_in_line) {
                if (!is_label_exists(label, first_label)) {
                    add_label(label, line_type, 0, current_label);
                    if ((*current_label)->next_label != NULL) {
                        *current_label = (*current_label)->next_label;
                    }
                } else {
                    fprintf(
                        stderr, "Error: label '%s' already exists, you can't have multiple labels with the same name (ignoring label)\n",
                        label);
                    return LABEL_ALREADY_EXISTS;
                }
            }
            break;
        case ENTRY:
            break;
    }

    return SUCCESS;
}

void update_dc(const char *line, int *dc, int *address_counter) {
    char temp_line[MAX_LINE_LEN];
    char *word;

    strcpy(temp_line, line);

    if (strstr(line, ".data")) {
        word = strtok(NULL, ",");
        while (word != NULL) {
            (*dc)++;
            (*address_counter)++;
            word = strtok(NULL, ",");
        }
    } else if (strstr(line, ".string")) {
        strtok(NULL, " \"");
        word = strtok(NULL, " \"");
        while (strlen(word) > 0) {
            (*dc)++;
            (*address_counter)++;
            word++;
        }
        (*dc)++;
        (*address_counter)++;
    }
}

void update_ic(const char *line, int *ic, int *address_counter) {
    char temp_line[MAX_LINE_LEN];
    char *word;
    int count = 0;

    strcpy(temp_line, line);

    if (strchr(temp_line, ':')) {
        strtok(temp_line, ":");
        word = strtok(NULL, " \n");
    } else {
        word = strtok(temp_line, " \n");
    }

    if (word == NULL) {
        return;
    }

    count++;

    word = strtok(NULL, " ,");

    while (word != NULL) {
        if (!is_register(word)) {
            count++;
        }
        word = strtok(NULL, " ,");
    }

    *ic += count;
    *address_counter += count;
}
