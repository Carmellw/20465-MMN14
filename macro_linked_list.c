#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "marco_linked_list.h"

void free_lines(struct line *first_line);

void add_macro(const char *name, struct macro **last_macro) {
    struct macro *new_macro = malloc(sizeof(struct macro));

    strcpy(new_macro->name, name);
    new_macro->first_line = NULL;
    new_macro->next_macro = NULL;

    if (*last_macro == NULL) {
        *last_macro = new_macro;
    } else {
        (*last_macro)->next_macro = new_macro;
    }
}

void add_line(const char *line_content, struct line **last_line) {
    struct line *new_line = malloc(sizeof(struct line));

    strcpy(new_line->line_content, line_content);
    new_line->next_line = NULL;

    if (*last_line == NULL) {
        *last_line = new_line;
    } else {
        (*last_line)->next_line = new_line;
    }
}

void add_first_line_to_macro(const char *line_content, struct macro **macro) {
    struct line *new_line = malloc(sizeof(struct line));
    strcpy(new_line->line_content, line_content);
    new_line->next_line = NULL;

    (*macro)->first_line = new_line;
}

void free_macros(struct macro *first_macro) {
    struct macro *temp_macro;
    while (first_macro != NULL) {
        temp_macro = first_macro;
        first_macro = first_macro->next_macro;
        free_lines(temp_macro->first_line);
        free(temp_macro);
    }
}

void free_lines(struct line *first_line) {
    struct line *temp_line;
    while (first_line != NULL) {
        temp_line = first_line;
        first_line = first_line->next_line;
        free(temp_line);
    }
}