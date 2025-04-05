#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "macro_expander.h"
#include "consts.h"
#include "macro.h"
#include "marco_linked_list.h"
#include "line_utils.h"

void expand_macros(const char *file_path, const char **result_file_path) {
    FILE *fp = fopen(file_path, "r"); // TODO: change those names
    FILE *fp2 = fopen("/Users/carmellwasserman/Desktop/example2.txt", "w"); // TODO: change this to temps or something
    struct macro *first_macro = NULL;


    separate_macros_from_file(fp, fp2, &first_macro);

    fclose(fp);
    fclose(fp2);

    fp = fopen("/Users/carmellwasserman/Desktop/example2.txt", "r");
    fp2 = fopen("/Users/carmellwasserman/Desktop/example3.txt", "w");

    replace_macros(fp, fp2, first_macro);

    fclose(fp);
    fclose(fp2);

    *result_file_path = malloc(strlen("/Users/carmellwasserman/Desktop/example3.txt") + 1);
    *result_file_path = "/Users/carmellwasserman/Desktop/example3.txt";
}

void replace_macros(FILE* file_to_read, FILE* file_to_write, struct macro *macros) {
    struct macro *current_macro = macros;
    struct line *current_line;
    char line[MAX_LINE_LEN];
    char* line_to_compare;
    while (fgets(line, MAX_LINE_LEN, file_to_read)) {
        remove_whitespaces_from_string(line, &line_to_compare);
        while (current_macro != NULL) {
            if (compare_strings_until_null_terminator(line_to_compare, current_macro->name) == TRUE) {
                current_line = current_macro->first_line;
                while (current_line != NULL) {
                    fprintf(file_to_write, "%s", current_line->line_content);
                    current_line = current_line->next_line;
                }
            }
            else {
                fprintf(file_to_write, "%s", line);
            }
            current_macro = current_macro->next_macro;
        }
        current_macro = macros;
    }
}

void separate_macros_from_file(FILE* file_to_read, FILE* file_to_write, struct macro **macros) {
    char line[MAX_LINE_LEN];
    char *trimmed_line;
    int is_in_macro = FALSE;
    struct macro *first_macro = NULL;
    struct macro *current_macro = NULL;
    struct line *current_line = NULL;

    while (fgets(line, MAX_LINE_LEN, file_to_read)) {
        trimmed_line = trim_whitespaces_from_start(line);
        if (FALSE == is_in_macro && strncmp(trimmed_line, MACRO_START, strlen(MACRO_START)) == 0) {
            is_in_macro = TRUE;
            add_macro(get_macro_name(trimmed_line), &current_macro);
            if (first_macro == NULL) {
                first_macro = current_macro;
            }
        }
        else if (TRUE == is_in_macro && strncmp(trimmed_line, MACRO_END, strlen(MACRO_END)) == 0) {
            is_in_macro = FALSE;
        }
        else if (TRUE == is_in_macro) {
            if (current_macro->first_line == NULL) {
                add_first_line_to_macro(trimmed_line, &current_macro);
                current_line = current_macro->first_line;
            }
            else {
            add_line(trimmed_line, &current_line);
            }
        }
        else {
            fprintf(file_to_write, "%s", trimmed_line);
        }
    }
    *macros = first_macro;
}

char *get_macro_name(char *line) {
    char *name;
    strtok(line, " ");
    name = strtok(NULL, " ");
    if (name[strlen(name)-1] == '\n') {
        name[strlen(name)-1] = '\0';
    }
    return name;
}

void remove_whitespaces_from_string(char *str, char **result) {
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
