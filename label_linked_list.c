#include <stdlib.h>
#include <string.h>

#include "label.h"
#include "label_linked_list.h"

void add_label(const char *name, const enum line_type type, const int address, struct label **last_label) {
    struct label *new_label = malloc(sizeof(struct label));

    strcpy(new_label->name, name);
    new_label->type = type;
    new_label->address = address;
    new_label->next_label = NULL;

    if (*last_label == NULL) {
        *last_label = new_label;
    } else {
        (*last_label)->next_label = new_label;
    }
}

void free_labels(struct label *first_line) {
    struct label *temp_label;
    while (first_line != NULL) {
        temp_label = first_line;
        first_line = first_line->next_label;
        free(temp_label);
    }
}
