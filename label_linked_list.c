#include <stdlib.h>
#include <string.h>

#include "label.h"
#include "label_linked_list.h"
#include "status_codes.h"

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

void free_labels(struct label *first_label) {
    struct label *temp_label;
    while (first_label != NULL) {
        temp_label = first_label;
        first_label = first_label->next_label;
        free(temp_label);
    }
}

enum status_code get_label(const char *name, const struct label *labels, struct label *label) {
    const struct label *current_label = labels;

    while (current_label != NULL) {
        if (strcmp(name, current_label->name) == 0) {
            *label = *current_label;
            return SUCCESS;
        }
        current_label = current_label->next_label;
    }

    return LABEL_NOT_FOUND;
}

int is_label_exists(const char *name, const struct label *labels) {
    const struct label *current_label = labels;

    while (current_label != NULL) {
        if (strcmp(name, current_label->name) == 0) {
            return TRUE;
        }
        current_label = current_label->next_label;
    }

    return FALSE;
}
