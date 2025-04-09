#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "macro_expander.h"
#include "consts.h"
#include "macro.h"
#include "macro_linked_list.h"
#include "line_utils.h"
#include "status_codes.h"
#include "path_utils.h"

void separate_macros_from_file(FILE *file_to_read, FILE *file_to_write, struct macro **macros);

char *get_macro_name(char *line);

void remove_whitespaces_from_string(const char *str, char **result);

int compare_strings_until_null_terminator(const char *str1, const char *str2);

enum status_code expand_macros(const char *file_path, const char **result_file_path) {
    FILE *read_file;
    FILE *write_file;
    char *temp_file_path;
    struct macro *first_macro = NULL;

    read_file = fopen(file_path, "r");
    if (read_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", file_path);
        return FAILED_OPENING_FILE;
    }
    temp_file_path = get_new_path(file_path, "-temp", "txt");
    write_file = fopen(temp_file_path, "w");
    if (write_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", temp_file_path);
        return FAILED_OPENING_FILE;
    }

    separate_macros_from_file(read_file, write_file, &first_macro);

    fclose(read_file);
    fclose(write_file);

    read_file = fopen(temp_file_path, "r");
    if (read_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", temp_file_path);
        return FAILED_OPENING_FILE;
    }
    free(temp_file_path);
    temp_file_path = get_new_path(file_path, NULL, "am");
    write_file = fopen(temp_file_path, "w");
    if (write_file == NULL) {
        fprintf(stderr, "Error opening file %s\n", temp_file_path);
        return FAILED_OPENING_FILE;
    }

    replace_macros(read_file, write_file, first_macro);

    fclose(read_file);
    fclose(write_file);

    *result_file_path = temp_file_path;

    free_macros(first_macro);

    return SUCCESS;
}

void replace_macros(FILE *file_to_read, FILE *file_to_write, struct macro *macros) {
    struct macro *current_macro = macros;
    struct line *current_line;
    char line[MAX_LINE_LEN];
    char *line_to_compare;
    while (fgets(line, MAX_LINE_LEN, file_to_read)) {
        remove_whitespaces_from_string(line, &line_to_compare);
        if (current_macro == NULL) {
            fprintf(file_to_write, "%s", line);
        }
        while (current_macro != NULL) {
            if (compare_strings_until_null_terminator(line_to_compare, current_macro->name) == TRUE) {
                current_line = current_macro->first_line;
                while (current_line != NULL) {
                    fprintf(file_to_write, "%s", current_line->line_content);
                    current_line = current_line->next_line;
                }
            } else {
                fprintf(file_to_write, "%s", line);
            }
            current_macro = current_macro->next_macro;
        }
        current_macro = macros;
        free(line_to_compare);
    }
}

void separate_macros_from_file(FILE *file_to_read, FILE *file_to_write, struct macro **macros) {
    char line[MAX_LINE_LEN];
    int is_in_macro = FALSE;
    struct macro *first_macro = NULL;
    struct macro *current_macro = NULL;
    struct line *current_line = NULL;

    while (fgets(line, MAX_LINE_LEN, file_to_read)) {
        trim_whitespaces_from_start(line);
        if (FALSE == is_in_macro && strncmp(line, MACRO_START, strlen(MACRO_START)) == 0) {
            is_in_macro = TRUE;
            add_macro(get_macro_name(line), &current_macro);
            if (first_macro == NULL) {
                first_macro = current_macro;
            }
        } else if (TRUE == is_in_macro && strncmp(line, MACRO_END, strlen(MACRO_END)) == 0) {
            is_in_macro = FALSE;
        } else if (TRUE == is_in_macro) {
            if (current_macro->first_line == NULL) {
                add_first_line_to_macro(line, &current_macro);
                current_line = current_macro->first_line;
            } else {
                add_line(line, &current_line);
            }
        } else {
            fprintf(file_to_write, "%s", line);
        }
    }
    *macros = first_macro;
}

char *get_macro_name(char *line) {
    char *name;
    strtok(line, " ");
    name = strtok(NULL, " ");
    if (name[strlen(name) - 1] == '\n') {
        name[strlen(name) - 1] = '\0';
    }
    return name;
}

void remove_whitespaces_from_string(const char *str, char **result) {
    char *new = malloc(strlen(str) + 1);
    char *current_char = new;

    while (*str != '\0') {
        if (!isspace(*str)) {
            *current_char = *str;
            current_char++;
        }
        str++;
    }
    *current_char = '\0';
    *result = new;
}

int compare_strings_until_null_terminator(const char *str1, const char *str2) {
    while (*str1 != '\0' || *str2 != '\0') {
        if (*str1 != *str2) {
            return FALSE;
        }
        if (*str1 == '\0' || *str2 == '\0') {
            return FALSE;
        }
        str1++;
        str2++;
    }
    return TRUE;
}
