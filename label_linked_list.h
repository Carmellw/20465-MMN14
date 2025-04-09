#ifndef LABEL_LINKED_LIST_H
#define LABEL_LINKED_LIST_H

#include "label.h"
#include "status_codes.h"

void add_label(const char *name, const enum line_type type, const int address, struct label **last_label);

void free_labels(struct label *first_line);

enum status_code get_label(const char *name, const struct label *labels, struct label *label);

int is_label_exists(const char *name, const struct label *labels);

#endif
